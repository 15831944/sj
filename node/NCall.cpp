#include "Node.h"

shared_ptr<CCallVar> CCallVar::create(Compiler* compiler, CResult& result, CLoc loc_, const string& name_, shared_ptr<NodeList> arguments_, shared_ptr<CBaseFunction> thisFunction_, weak_ptr<CVar> dotVar_, shared_ptr<CBaseFunction> callee_) {
    assert(callee_);

    auto c = make_shared<CCallVar>();
    c->name = name_;
    c->mode = Var_Local;
    c->isMutable = true;
    c->nassignment = nullptr;
    c->loc = loc_;
    c->arguments = arguments_;
    c->thisFunction = thisFunction_;
    c->dotVar = dotVar_;
    c->callee = callee_;
    c->isHeapVar = false;
    c->isInGetHeapVar = false;
    
    auto onHasParent = [callee_, thisFunction_](Compiler* compiler, CResult& result) {
        if (callee_ == thisFunction_) {
            callee_->setHasParent(compiler, result);
        } else {
            auto temp = static_pointer_cast<CBaseFunction>(thisFunction_);
            while (temp && temp != callee_->parent.lock()) {
                temp->setHasParent(compiler, result);
                temp = temp->parent.lock();
            }
        }
    };
    
    if (callee_->getHasParent(compiler, result)) {
        onHasParent(compiler, result);
    } else {
        callee_->onHasParent(onHasParent);
    }
    
    return c;
}

shared_ptr<CVar> CCallVar::getThisVar(Compiler* compiler, CResult& result) {
    if (!calleeVar) {
        callee->createThisVar(compiler, result, calleeVar);
    }
    return calleeVar;
}

shared_ptr<CType> CCallVar::getType(Compiler* compiler, CResult& result) {
    return callee->getReturnType(compiler, result, getThisVar(compiler, result));
}

bool CCallVar::getParameters(Compiler* compiler, CResult& result, vector<shared_ptr<NBase>>& parameters) {
    auto argIndex = (size_t)0;
    auto hasSetByName = false;
    for (auto it : *arguments) {
        if (it->nodeType == NodeType_Assignment) {
            auto parameterAssignment = static_pointer_cast<NAssignment>(it);
            assert(parameterAssignment->inFunctionDeclaration);
            auto index = callee->getThisIndex(parameterAssignment->name);
            if (index < 0) {
                result.addError(loc, CErrorCode::ParameterDoesNotExist, "cannot find parameter '%s'", parameterAssignment->name.c_str());
                return false;
            }
            
            if (parameters[index] != nullptr) {
                result.addError(loc, CErrorCode::ParameterRedefined, "defined parameter '%s' twice", parameterAssignment->name.c_str());
                return false;
            }
            
            parameters[index] = parameterAssignment->rightSide;
            hasSetByName = true;
        } else {
            if (hasSetByName) {
                result.addError(loc, CErrorCode::ParameterByIndexAfterByName, "all named parameters must be after the un-named parameters");
                return false;
            }
            
            if (parameters[argIndex] != nullptr) {
                result.addError(loc, CErrorCode::Internal, "re-defining the same parameters which should be impossible for un-named parameters");
                return false;
            }
            
            parameters[argIndex] = it;
        }
        argIndex++;
    }
    
    argIndex = 0;
    for (auto it : callee->argDefaultValues) {
        if (argIndex < parameters.size() && parameters[argIndex] == nullptr) {
            if (it == nullptr) {
                result.addError(loc, CErrorCode::ParameterRequired, "parameter %d is required", argIndex);
                return false;
            }
            parameters[argIndex] = it;
        }
        argIndex++;
    }
    
    return true;
}

//shared_ptr<ReturnValue> CCallVar::getLoadValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, bool dotInEntry, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB, ReturnRefType returnRefType) {
//    assert(compiler->state == CompilerState::Compile);
//    // compiler->emitLocation(builder, call.get());
//    
//    if (arguments->size() > callee->argDefaultValues.size()) {
//        result.addError(loc, CErrorCode::TooManyParameters, "passing %d, but expecting max of %d", arguments->size(), callee->argDefaultValues.size());
//        return nullptr;
//    }
//    
//    // Fill in parameters
//    vector<shared_ptr<NBase>> parameters(callee->argDefaultValues.size());
//    if (!getParameters(compiler, result, parameters)) {
//        return nullptr;
//    }
//    
//    compiler->emitLocation(builder, &loc);
//    
//    return callee->call(compiler, result, thisFunction, thisVar, thisValue, getThisVar(compiler, result), dotVar.lock(), builder, catchBB, parameters, returnRefType);
//    
//}
//
//Value* CCallVar::getStoreValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, bool dotInEntry, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB) {
//    result.addError(loc, CErrorCode::ImmutableAssignment, "cannot assign value to function result");
//    return nullptr;
//}

string CCallVar::fullName() {
    return name + "()";
}

bool CCallVar::getHeapVar(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar) {
    if (isHeapVar) {
        return true;
    }

    if (isInGetHeapVar) {
        result.addError(loc, CErrorCode::TypeLoop, "cycle detected");
        return false;
    }
    
    isInGetHeapVar = true;
    auto returnVar = callee->getReturnVar(compiler, result, calleeVar);
    if (returnVar) {
        isHeapVar = returnVar->getHeapVar(compiler, result, calleeVar);
    }
    isInGetHeapVar = false;
    return isHeapVar;
}

int CCallVar::setHeapVar(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar) {
    if (!isHeapVar) {
        isHeapVar = true;
        auto returnVar = callee->getReturnVar(compiler, result, calleeVar);
        if (returnVar) {
            return returnVar->setHeapVar(compiler, result, calleeVar);
        }
    }
    return 0;
}

shared_ptr<CType> CCallVar::transpile(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* output, TrFunction* function, stringstream& line, shared_ptr<CVar> dotVar) {
    assert(compiler->state == CompilerState::Compile);
    // compiler->emitLocation(builder, call.get());

    if (arguments->size() > callee->argDefaultValues.size()) {
        result.addError(loc, CErrorCode::TooManyParameters, "passing %d, but expecting max of %d", arguments->size(), callee->argDefaultValues.size());
        return nullptr;
    }

    // Fill in parameters
    vector<shared_ptr<NBase>> parameters(callee->argDefaultValues.size());
    if (!getParameters(compiler, result, parameters)) {
        return nullptr;
    }

    return callee->transpile(compiler, result, thisFunction, thisVar, output, function, line, calleeVar, parameters);
}

void CCallVar::dump(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, stringstream& dotSS, int level) {
    if (functions.find(callee) == functions.end()) {
        functions[callee] = "";
        stringstream temp;
        callee->dumpBody(compiler, result, calleeVar, functions, temp, 0);
        functions[callee] = temp.str();
    }
    
    auto returnVar = callee->getReturnVar(compiler, result, calleeVar);
    if (returnVar) {
        ss << alloc_mode(compiler, result, thisVar, returnVar);
    }
    ss << callee->fullName(true) << "(";

    vector<shared_ptr<NBase>> parameters(callee->argDefaultValues.size());
    if (!getParameters(compiler, result, parameters)) {
        return;
    }
    
    auto calleeVar = getThisVar(compiler, result);
    if (calleeVar) {
        ss << alloc_mode(compiler, result, thisVar, calleeVar);
        ss << "this" << (calleeVar->isMutable ? " = " : " : ");
        ss << callee->fullName(true) << "(";
        
        if (parameters.size() > 0 || callee->getHasParent(compiler, result)) {
            ss << "\n";
            dumpf(ss, level + 1);
            
            if (callee->getHasParent(compiler, result)) {
                ss << "parent: ";
                auto t = dotSS.str();
                if (t.size() > 0) {
                    ss << alloc_mode(compiler, result, thisVar, dotVar);
                    ss << t;
                } else {
                    ss << alloc_mode(compiler, result, thisVar, thisVar);
                    ss << "this";
                }
                
                if (parameters.size() > 0) {
                    ss << ",\n";
                    dumpf(ss, level + 1);
                }
            }
            
            auto paramIndex = (size_t)0;
            for (auto it : parameters) {
                auto paramVar = callee->argVars[paramIndex];
                ss << alloc_mode(compiler, result, thisVar, paramVar);
                ss << paramVar->name.c_str();
                ss << "'" << paramVar->getType(compiler, result)->nameVal.c_str();
                ss << (paramVar->isMutable ? " = " : " : ");
                it->dump(compiler, result, thisFunction, thisVar, functions, ss, level + 1);
                if (paramIndex != parameters.size() - 1) {
                    ss << ",\n";
                    dumpf(ss, level + 1);
                }
                paramIndex++;
            }
            ss << "\n";
            dumpf(ss, level);
        }
        ss << "))";
    } else {
        if (parameters.size() > 0 || callee->getHasParent(compiler, result)) {
            ss << "\n";
            dumpf(ss, level + 1);
            
            if (callee->getHasParent(compiler, result)) {
                ss << "parent: ";
                auto t = dotSS.str();
                if (t.size() > 0) {
                    ss << alloc_mode(compiler, result, thisVar, dotVar);
                    ss << t;
                } else {
                    ss << alloc_mode(compiler, result, thisVar, thisVar);
                    ss << "this";
                }
                
                if (parameters.size() > 0) {
                    ss << ",\n";
                    dumpf(ss, level + 1);
                }
            }
            
            auto paramIndex = (size_t)0;
            for (auto it : parameters) {
                auto paramVar = callee->argVars[paramIndex];
                ss << alloc_mode(compiler, result, thisVar, paramVar);
                ss << paramVar->name.c_str();
                ss << "'" << paramVar->getType(compiler, result)->nameVal.c_str();
                ss << (paramVar->isMutable ? " = " : " : ");
                it->dump(compiler, result, thisFunction, thisVar, functions, ss, level + 1);
                if (paramIndex != parameters.size() - 1) {
                    ss << ",\n";
                    dumpf(ss, level + 1);
                }
                paramIndex++;
            }
            ss << "\n";
            dumpf(ss, level);
        }
        ss << ")";
    }
}


NCall::NCall(CLoc loc, const char* name, shared_ptr<CTypeNameList> templateTypeNames, shared_ptr<NodeList> arguments) : NVariableBase(NodeType_Call, loc), name(name), templateTypeNames(templateTypeNames), arguments(arguments) {
    if (!this->arguments) {
        this->arguments = make_shared<NodeList>();
    } else {
        for (auto it : *arguments) {
            if (it->nodeType == NodeType_Assignment) {
                auto parameterAssignment = static_pointer_cast<NAssignment>(it);
                parameterAssignment->inFunctionDeclaration = true;
            }
        }
    }
}

void NCall::defineImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunctionDefinition> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    for (auto it : *arguments) {
        if (it->nodeType == NodeType_Assignment) {
            auto parameterAssignment = static_pointer_cast<NAssignment>(it);
            parameterAssignment->define(compiler, result, thisFunction);
        } else {
            it->define(compiler, result, thisFunction);
        }
    }
}



shared_ptr<CBaseFunction> NCall::getCFunction(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> dotVar) {
    assert(compiler->state >= CompilerState::FixVar);
    
    // parentFunction will be specified if the NCall is used as the default NAssignment for a NFunction
    auto cfunction = static_pointer_cast<CBaseFunction>(thisFunction);
    
    if (dotVar) {
        cfunction = dotVar->getCFunctionForValue(compiler, result);
        if (!cfunction) {
            result.addError(loc, CErrorCode::InvalidVariable, "parent is not a function: '%s'", dotVar->fullName().c_str());
            return nullptr;
        }
    }
    
    // Handle last name in list
    auto callee = cfunction->getCFunction(compiler, result, name, thisFunction, templateTypeNames);
    if (!callee) {
        // If we are still using "this" then we can check to see if it is a function on parent
        if (cfunction == thisFunction) {
            while (cfunction && !cfunction->parent.expired() && !callee) {
                cfunction = cfunction->parent.lock();
                if (cfunction) {
                    callee = cfunction->getCFunction(compiler, result, name, thisFunction, templateTypeNames);
                }
            }
        }
    }
    
    if (!callee) {
        result.addError(loc, CErrorCode::UnknownFunction, "function '%s' does not exist", name.c_str());
        return nullptr;
    }
    
    return callee;
}

shared_ptr<CVar> NCall::getVarImpl(Compiler *compiler, CResult &result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar) {
    auto callee = getCFunction(compiler, result, thisFunction, dotVar);
    if (!callee) {
        return nullptr;
    }
    
    for (auto it : *arguments) {
        if (it->nodeType == NodeType_Assignment) {
            auto parameterAssignment = static_pointer_cast<NAssignment>(it);
            assert(parameterAssignment->inFunctionDeclaration);
            parameterAssignment->getVar(compiler, result, thisFunction, thisVar);
        } else {
            it->getVar(compiler, result, thisFunction, thisVar);
        }
    }
    
    if (!_callVar) {
        _callVar = CCallVar::create(compiler, result, loc, name, arguments, thisFunction, dotVar, callee);
        _callVar->getThisVar(compiler, result);
    }
    return _callVar;
}

int NCall::setHeapVarImpl(Compiler *compiler, CResult &result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, bool isHeapVar) {

    auto callee = getCFunction(compiler, result, thisFunction, dotVar);
    if (!callee) {
        return 0;
    }
    
    if (arguments->size() > callee->argVars.size()) {
        result.addError(loc, CErrorCode::TooManyParameters, "argument count is wrong");
        return 0;
    }
    
    vector<shared_ptr<NBase>> parameters(callee->argVars.size());
    if (!_callVar->getParameters(compiler, result, parameters)) {
        return 0;
    }
    
    auto calleeVar = _callVar->getThisVar(compiler, result);
    auto count = 0;
    auto index = 0;
    for (auto argVar : parameters) {
        auto parameterVar = callee->argVars[index];
        
        if (isHeapVar) {
            parameterVar->setHeapVar(compiler, result, thisVar);
        }
        
        auto parameterType = parameterVar->getType(compiler, result);
        if (!parameterType->parent.expired() && !parameterType->parent.lock()->getHasThis()) {
            parameterType->parent.lock()->setHasRefCount();
        }
        
        auto isDefaultAssignment = argVar == callee->argDefaultValues[index];
        auto parameterHeapVar = parameterVar->getHeapVar(compiler, result, thisVar);
        if (argVar->nodeType == NodeType_Assignment) {
            auto parameterAssignment = static_pointer_cast<NAssignment>(argVar);
            assert(parameterAssignment->inFunctionDeclaration);
            if (isDefaultAssignment) {
                count += parameterAssignment->setHeapVar(compiler, result, callee, calleeVar, parameterHeapVar);
            } else {
                count += parameterAssignment->setHeapVar(compiler, result, thisFunction, thisVar, parameterHeapVar);
            }
        } else {
            if (isDefaultAssignment) {
                count += argVar->setHeapVar(compiler, result, callee, calleeVar, parameterHeapVar);
            } else {
                count += argVar->setHeapVar(compiler, result, thisFunction, thisVar, parameterHeapVar);
            }
        }
        index++;
    }

    if (isHeapVar) {
        auto var = getVar(compiler, result, thisFunction, thisVar, dotVar);
        if (var) {
            count += var->setHeapVar(compiler, result, thisVar);
        }
    }
    return count;
}


