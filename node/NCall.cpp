#include "Node.h"

NCall::NCall(CLoc loc, const char* name, StringList templateTypes, NodeList arguments) : templateTypes(templateTypes), arguments(arguments), NBase(loc) {
    istringstream f(name);
    string s;
    while (getline(f, s, '.')) {
        dotNames.push_back(s);
    }
    functionName = dotNames.back();
    dotNames.pop_back();

    for (auto it : arguments) {
        if (it->getNodeType() == NodeType_Assignment) {
            auto parameterAssignment = static_pointer_cast<NAssignment>(it);
            parameterAssignment->inFunctionDeclaration = true;
        }
    }
}

NodeType NCall::getNodeType() const {
    return NodeType_Call;
}

void NCall::define(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    for (auto it : arguments) {
        if (it->getNodeType() == NodeType_Assignment) {
            auto parameterAssignment = static_pointer_cast<NAssignment>(it);
            parameterAssignment->define(compiler, result, thisFunction);
        } else {
            it->define(compiler, result, thisFunction);
        }
    }
}

void NCall::fixVar(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction) {    
    assert(compiler->state == CompilerState::FixVar);
    
    // Must call this, so any local vars used outside of the function can be promoted to function vars
    if (dotNames.size() > 0) {
        NVariable::getParentValue(compiler, result, loc, thisFunction, nullptr, nullptr, dotNames, VT_LOAD, nullptr);
    }

    for (auto it : arguments) {
        if (it->getNodeType() == NodeType_Assignment) {
            auto parameterAssignment = static_pointer_cast<NAssignment>(it);
            assert(parameterAssignment->inFunctionDeclaration);
            parameterAssignment->fixVar(compiler, result, thisFunction);
        } else {
            it->fixVar(compiler, result, thisFunction);
        }
    }
}

shared_ptr<CFunction> NCall::getCFunction(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, Value* thisValue, IRBuilder<>* builder) const {
    assert(compiler->state >= CompilerState::FixVar);

    // parentFunction will be specified if the NCall is used as the default NAssignment for a NFunction
    auto cfunction = thisFunction;
    
    // If more than one name in the list, then we need to iterate down to correct function
    if (dotNames.size() > 0) {
        auto cvar = NVariable::getParentValue(compiler, result, loc, thisFunction, thisValue, builder, dotNames, VT_LOAD, nullptr);
        if (!cvar) {
            result.addError(loc, CErrorCode::UnknownFunction, "function '%s' does not exist", dotNames.back().c_str());
            return nullptr;
        }
        
        cfunction = cvar->getCFunctionForValue(compiler, result);

        if (!cfunction) {
            result.addError(loc, CErrorCode::UnknownFunction, "function '%s' does not exist", dotNames.back().c_str());
            return nullptr;
        }
    }
    
    // Handle last name in list
    auto callee = cfunction->getCFunction(functionName);    
    if (!callee) {
        // If we are still using "this" then we can check to see if it is a function on parent
        if (cfunction == thisFunction) {
            while (cfunction && !cfunction->parent.expired() && !callee) {
                cfunction = shared_ptr<CFunction>(cfunction->parent);
                if (cfunction) {
                    callee = cfunction->getCFunction(functionName);
                }
            }
        }
    }
    
    if (!callee) {
        result.addError(loc, CErrorCode::UnknownFunction, "function '%s' does not exist", functionName.c_str());
        return nullptr;
    }
    
    return callee;
}

shared_ptr<CType> NCall::getReturnType(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction) const {
    assert(compiler->state >= CompilerState::FixVar);
    auto callee = getCFunction(compiler, result, thisFunction, nullptr, nullptr);
    if (!callee) {
        return nullptr;
    }
    
    auto type = callee->getReturnType(compiler, result);
    
    return type;
}

Value* NCall::compile(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, Value* thisValue, IRBuilder<>* builder, BasicBlock* catchBB) const {
    assert(compiler->state == CompilerState::Compile);
    compiler->emitLocation(this);
    
    auto callee = getCFunction(compiler, result, thisFunction, thisValue, builder);
    if (!callee) {
        return nullptr;
    }
    
    if (arguments.size() > callee->node->assignments.size()) {
        result.addError(loc, CErrorCode::TooManyParameters, "passing %d, but expecting max of %d", arguments.size(), callee->node->assignments.size());
        return nullptr;
    }
    
    // Fill in parameters
    vector<shared_ptr<NBase>> parameters(callee->node->assignments.size());
    auto argIndex = 0;
    auto hasSetByName = false;
    for (auto it : arguments) {
        if (it->getNodeType() == NodeType_Assignment) {
            auto parameterAssignment = static_pointer_cast<NAssignment>(it);
            assert(parameterAssignment->inFunctionDeclaration);
            auto index = callee->getThisIndex(parameterAssignment->names[0]);
            if (index == -1) {
                result.addError(loc, CErrorCode::ParameterDoesNotExist, "cannot find parameter '%s'", parameterAssignment->fullName.c_str());
                return nullptr;
            }
            
            if (parameters[index] != nullptr) {
                result.addError(loc, CErrorCode::ParameterRedefined, "defined parameter '%s' twice", parameterAssignment->fullName.c_str());
                return nullptr;
            }
            
            parameters[index] = parameterAssignment->rightSide;
            hasSetByName = true;
        } else {
            if (hasSetByName) {
                result.addError(loc, CErrorCode::ParameterByIndexAfterByName, "all named parameters must be after the un-named parameters");
                return nullptr;
            }
            
            if (parameters[argIndex] != nullptr) {
                result.addError(loc, CErrorCode::Internal, "re-defining the same parameters which should be impossible for un-named parameters");
                return nullptr;
            }
            
            parameters[argIndex] = it;
        }
        argIndex++;
    }
    
    argIndex = 0;
    for (auto it : callee->node->assignments) {
        if (parameters[argIndex] == nullptr) {
            auto defaultAssignment = static_pointer_cast<NAssignment>(it);
            assert(defaultAssignment->inFunctionDeclaration);
            if (!defaultAssignment->rightSide) {
                result.addError(loc, CErrorCode::ParameterRequired, "must assign value to parameter '%s'", it->fullName.c_str());
                return nullptr;
            }
            parameters[argIndex] = defaultAssignment->rightSide;
        }
        argIndex++;
    }
    
    if (callee->type == FT_Extern) {
        vector<Value *> argsV;
        auto func = callee->getFunction(compiler, result);

        // Fill in "this" with normal arguments
        argIndex = 0;
        for (auto defaultAssignment : callee->node->assignments) {
            assert(defaultAssignment->inFunctionDeclaration);
            auto argType = defaultAssignment->getReturnType(compiler, result, callee);
            auto isDefaultAssignment = parameters[argIndex] == defaultAssignment->rightSide;
            Value* value;
            if (isDefaultAssignment) {
                value = parameters[argIndex]->compile(compiler, result, callee, nullptr, builder, catchBB);
            } else {
                value = parameters[argIndex]->compile(compiler, result, thisFunction, thisValue, builder, catchBB);
            }
            
            if (!value) {
                result.addError(CLoc::undefined, CErrorCode::TypeMismatch, "value is empty");
                return nullptr;
            }
            
            if (value->getType() != argType->llvmRefType(compiler, result)) {
                result.addError(CLoc::undefined, CErrorCode::TypeMismatch, "value does not match");
                return nullptr;
            }
            
            argsV.push_back(value);
            
            argIndex++;
        }
        
        return builder->CreateCall(func, argsV);
    } else {
        // Create this on stack, and get a pointer
        auto newType = callee->getThisType(compiler, result);
        auto entryBuilder = getEntryBuilder(builder);
        auto newValue = entryBuilder.CreateAlloca(newType->llvmAllocType(compiler, result), 0, newType->name.c_str());
        
        // Fill in "this" with normal arguments
        argIndex = 0;
        for (auto defaultAssignment : callee->node->assignments) {
            assert(defaultAssignment->inFunctionDeclaration);
            auto argType = defaultAssignment->getReturnType(compiler, result, callee);
            auto isDefaultAssignment = parameters[argIndex] == defaultAssignment->rightSide;
            Value* value;
            if (isDefaultAssignment) {
                value = parameters[argIndex]->compile(compiler, result, callee, newValue, builder, catchBB);
            } else {
                value = parameters[argIndex]->compile(compiler, result, thisFunction, thisValue, builder, catchBB);
            }
            
            if (!value) {
                result.addError(CLoc::undefined, CErrorCode::TypeMismatch, "value is empty");
                return nullptr;
            }
            
            if (value->getType() != argType->llvmRefType(compiler, result)) {
                result.addError(CLoc::undefined, CErrorCode::TypeMismatch, "value does not match");
                return nullptr;
            }

            vector<Value*> v;
            v.push_back(ConstantInt::get(compiler->context, APInt(32, 0)));
            v.push_back(ConstantInt::get(compiler->context, APInt(32, argIndex)));
            auto paramPtr = builder->CreateInBoundsGEP(newType->llvmAllocType(compiler, result), newValue, ArrayRef<Value *>(v), defaultAssignment->fullName.c_str());
            
            builder->CreateStore(value, paramPtr);

            argIndex++;
        }
        
        // Add "parent" to "this"
        argIndex = callee->getThisIndex("parent");
        if (argIndex != -1) {
            Value* parentValue = thisValue;
            if (dotNames.size() > 0) {
                NVariable::getParentValue(compiler, result, loc, thisFunction, thisValue, builder, dotNames, VT_LOAD, &parentValue);
            } else {
                // if recursively calling ourselves then re-use parent
                if (callee == thisFunction) {
                    auto parentIndex = thisFunction->getThisIndex("parent");
                    vector<Value*> v;
                    v.push_back(ConstantInt::get(compiler->context, APInt(32, 0)));
                    v.push_back(ConstantInt::get(compiler->context, APInt(32, parentIndex)));
                    auto ptr = builder->CreateInBoundsGEP(thisFunction->getThisType(compiler, result)->llvmAllocType(compiler, result), parentValue, ArrayRef<Value *>(v), "parent");
                    parentValue = builder->CreateLoad(ptr, "parent");
                } else {
                    auto temp = thisFunction;
                    while (temp && temp != callee->parent.lock()) {
                        auto parentIndex = temp->getThisIndex("parent");
                        vector<Value*> v;
                        v.push_back(ConstantInt::get(compiler->context, APInt(32, 0)));
                        v.push_back(ConstantInt::get(compiler->context, APInt(32, parentIndex)));
                        auto ptr = builder->CreateInBoundsGEP(temp->getThisType(compiler, result)->llvmAllocType(compiler, result), parentValue, ArrayRef<Value *>(v), "parent");
                        parentValue = builder->CreateLoad(ptr, "parent");
                        
                        temp = temp->parent.lock();
                    }
                }
            }
            
            vector<Value*> v;
            v.push_back(ConstantInt::get(compiler->context, APInt(32, 0)));
            v.push_back(ConstantInt::get(compiler->context, APInt(32, argIndex)));
            auto paramPtr = builder->CreateInBoundsGEP(newType->llvmAllocType(compiler, result), newValue, ArrayRef<Value *>(v), "parent");
            
            builder->CreateStore(parentValue, paramPtr, "parent");
        }

        vector<Value *> argsV;
        argsV.push_back(newValue);
        auto func = callee->getFunction(compiler, result);

        Value* returnValue = nullptr;
        
        if (catchBB) {
            auto continueBB = BasicBlock::Create(compiler->context);
            returnValue = builder->CreateInvoke(func, continueBB, catchBB, argsV);
            
            Function *function = builder->GetInsertBlock()->getParent();
            function->getBasicBlockList().push_back(continueBB);
            builder->SetInsertPoint(continueBB);
        } else {
            returnValue = builder->CreateCall(func, argsV);
        }
        
        return returnValue;
    }
}

void NCall::dump(Compiler* compiler, int level) const {
    dumpf(level, "type: 'NCall'");
    dumpf(level, "functionName: '%s'", functionName.c_str());

    if (arguments.size() > 0) {
        dumpf(level, "arguments: {");
        auto argIndex = 0;
        for (auto it : arguments) {
            if (it->getNodeType() == NodeType_Assignment) {
                auto parameterAssignment = static_pointer_cast<NAssignment>(it);
                assert(parameterAssignment->inFunctionDeclaration);
                dumpf(level + 1, "%s: {", parameterAssignment->fullName.c_str());
                parameterAssignment->dump(compiler, level + 2);
                dumpf(level + 1, "}");
            } else {
                dumpf(level + 1, "'%d': {", argIndex);
                it->dump(compiler, level + 2);
                dumpf(level + 1, "}");
            }
            argIndex ++;
        }
        dumpf(level, "}");
    }
}

