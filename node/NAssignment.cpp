#include "Node.h"

NAssignment::NAssignment(CLoc loc, shared_ptr<NVariableBase> var, const char* typeName, const char* name, shared_ptr<NBase> rightSide_, bool isMutable) : var(var), typeName(typeName), name(name), rightSide(rightSide_), isMutable(isMutable), inFunctionDeclaration(false), NBase(NodeType_Assignment, loc) {
    // If we are assigning a function to a var then we will call the function to get its value
    if (rightSide && rightSide->nodeType == NodeType_Function) {
        nfunction = static_pointer_cast<NFunction>(rightSide);
        rightSide = make_shared<NCall>(loc, nfunction->name.c_str(), nullptr, nullptr);
    }
}

void NAssignment::defineImpl(Compiler* compiler, CResult& result, shared_ptr<CFunctionDefinition> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    
    if (var) {
        var->define(compiler, result, thisFunction);
    }
    
    if (nfunction) {
        nfunction->define(compiler, result, thisFunction);
    }
    
    if (rightSide) {
        rightSide->define(compiler, result, thisFunction);
    }
}

shared_ptr<CVar> NAssignment::getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction) {
    assert(compiler->state == CompilerState::FixVar);

    // function vars are not created here, this is only for local vars
    if (!inFunctionDeclaration) {
        // We need to see if var already exists, if not create a new local var
        auto cfunction = thisFunction;
        shared_ptr<CVar> parentVar = nullptr;
        if (var) {
            parentVar = var->getVar(compiler, result, thisFunction, nullptr);
            if (!parentVar) {
                return nullptr;
            }
            cfunction = parentVar->getCFunctionForValue(compiler, result);
            if (!cfunction) {
                result.addError(loc, CErrorCode::InvalidVariable, "var must be a function: '%s'", parentVar->fullName().c_str());
                return nullptr;
            }
        }
        
        _assignVar = cfunction->getCVar(compiler, result, loc, name);
        if (_assignVar) {
            if (!isMutable) {
                result.addError(loc, CErrorCode::ImmutableAssignment, "immutable assignment to existing var");
                return nullptr;
            } else if (!_assignVar->isMutable) {
                result.addError(loc, CErrorCode::ImmutableAssignment, "immutable assignment to existing var");
                return nullptr;
            }
        } else {
            if (!var) {
                auto iter = cfunction->localVarsByName.find(name);
                if (iter != cfunction->localVarsByName.end()) {
                    result.addError(loc, CErrorCode::Internal, "the previous search on NVariable should find a local value with same name");
                    return nullptr;
                }
                _assignVar = CNormalVar::createLocalVar(loc, name, thisFunction, shared_from_this());
                cfunction->localVarsByName[name] = _assignVar;
            }
        }
        
        if (var) {
            _assignVar = CDotVar::create(parentVar, _assignVar);
        }
    }
    
    if (nfunction) {
        nfunction->getVar(compiler, result, thisFunction);
    }
    
    if (rightSide) {
        return rightSide->getVar(compiler, result, thisFunction);
    }
    
    return nullptr;
}

shared_ptr<CType> NAssignment::getTypeImpl(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction) {
    assert(compiler->state >= CompilerState::FixVar);

    if (typeName.size() > 0) {
        auto valueType = thisFunction->getVarType(compiler, result, loc, typeName, nullptr);
        if (!valueType) {
            result.addError(loc, CErrorCode::InvalidType, "explicit type does not exist");
            return nullptr;
        }
        return valueType;
    }
    
    if (!rightSide) {
        result.addError(loc, CErrorCode::Internal, "only required assignment should not have a right side, and they must have typeName");
        return nullptr;
    }
    
    return rightSide->getType(compiler, result, thisFunction);
}

int NAssignment::setHeapVarImpl(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, bool isHeapVar) {
    if (_assignVar != nullptr && _assignVar->mode != Local) {
        // TODO: does not need to be a heap var if parent is a local var
        isHeapVar = true;
    }
    
    if (rightSide) {
        return rightSide->setHeapVar(compiler, result, thisFunction, isHeapVar);
    }
    return 0;
}

Value* NAssignment::compileImpl(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, Value* thisValue, IRBuilder<>* builder, BasicBlock* catchBB, bool isReturnRetained) {
    assert(compiler->state == CompilerState::Compile);
    compiler->emitLocation(this);
    
    if (!rightSide) {
        result.addError(loc, CErrorCode::Internal, "only required assignment should not have a right side, and they should not be compiled");
        return nullptr;
    }

    if (!inFunctionDeclaration && nfunction) {
        nfunction->compile(compiler, result, thisFunction, thisValue, builder, catchBB, false);
    }
    
    // Compute value
    // TODO: retain value
    Value *value = rightSide->compile(compiler, result, thisFunction, thisValue, builder, catchBB, true);

    if (!value) {
        result.addError(loc, CErrorCode::ExpressionEmpty, "trying to assign an empty value");
        return nullptr;
    }
    
    if (typeName.size() > 0) {
        shared_ptr<CType> valueType = compiler->getType(typeName.c_str());
        if (!valueType) {
            result.addError(loc, CErrorCode::InvalidType, "explicit type does not exist");
            return nullptr;
        }

        if (value->getType() != valueType->llvmRefType(compiler, result)) {
            result.addError(loc, CErrorCode::TypeMismatch, "returned type '%s' does not match explicit type '%s'", Type_print(value->getType()).c_str(), Type_print(valueType->llvmRefType(compiler, result)).c_str());
            return nullptr;
        }
    }
    
    // Get place to store data
    auto alloca = _assignVar->getStoreValue(compiler, result, thisValue, thisValue, builder, catchBB);
    if (!alloca) {
        result.addError(loc, CErrorCode::InvalidVariable, "var cannot be assigned '%s'", name.c_str());
        return nullptr;
    }
    
    // Store value
    builder->CreateStore(value, alloca);
    return value;
}

void NAssignment::dump(Compiler* compiler, int level) const {
    dumpf(level, "type: 'NAssignment'");
    dumpf(level, "name: %s", name.c_str());
    dumpf(level, "typeName: %s", typeName.c_str());
    dumpf(level, "isMutable: %s", bool_to_str(isMutable));
    
    if (nfunction) {
        dumpf(level, "function: {");
        nfunction->dump(compiler, level + 1);
        dumpf(level, "}");
    }
    
    dumpf(level, "rightSide: {");
    rightSide->dump(compiler, level + 1);
    dumpf(level, "}");
}

shared_ptr<NAssignment> NAssignment::shared_from_this() {
    return static_pointer_cast<NAssignment>(NBase::shared_from_this());
}

