#include <sjc.h>


bool CAssignVar::getReturnThis() {
    return false;
}

shared_ptr<CType> CAssignVar::getType(Compiler* compiler) {
    return leftVar->getType(compiler);
}

void CAssignVar::transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue) {
    assert(compiler->state == CompilerState::Compile);
   
    auto leftType = leftVar->getType(compiler);
    auto leftStoreValue = leftVar->getStoreValue(compiler, scope.lock(), trOutput, trBlock, thisValue, op);
    if (!leftStoreValue) {
        return;
    }

    leftStoreValue->loc = loc;
    rightVar->transpile(compiler, trOutput, trBlock, thisValue, leftStoreValue);
    if (!leftStoreValue->hasSetValue) {
        compiler->addError(loc, CErrorCode::TypeMismatch, "no return value");
        return;
    }
    
    storeValue->retainValue(compiler, loc, trBlock, leftStoreValue->getValue());
}

void CAssignVar::dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level) {
    auto type = getType(compiler);
    leftVar->dump(compiler, functions, ss, level);
    auto leftType = leftVar->getType(compiler);
    ss << "'" << (leftType ? leftType->fullName.c_str() : "unknown");
    ss << (isMutable ? " = " : " : ");
    if (rightVar) {
        rightVar->dump(compiler, functions, ss, level);
    } else {
        ss << "undefined";
    }
}

NAssignment::NAssignment(CLoc loc, shared_ptr<NVariableBase> var, shared_ptr<CTypeName> typeName, const char* name, shared_ptr<NBase> rightSide_, AssignOp op) : NBase(NodeType_Assignment, loc), var(var), typeName(typeName), name(name), inFunctionDeclaration(false), rightSide(rightSide_), op(op) {
    boost::algorithm::to_lower(this->name);

    // If we are assigning a function to a var then we will call the function to get its value
    if (rightSide && rightSide->nodeType == NodeType_Function) {
        nfunction = static_pointer_cast<NFunction>(rightSide);
        rightSide = make_shared<NCall>(loc, nfunction->name.c_str(), nullptr, nullptr);
    }
}

void NAssignment::initFunctionsImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    
    this->packageNamespace = packageNamespace;

    if (var) {
        var->initFunctions(compiler, importNamespaces, packageNamespace, thisFunction);
    }
    
    if (nfunction) {
        nfunction->initFunctions(compiler, importNamespaces, packageNamespace, thisFunction);
    }
    
    if (rightSide) {
        rightSide->initFunctions(compiler, importNamespaces, packageNamespace, thisFunction);
    }
}

void NAssignment::initVarsImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode) {
    if (var) {
        var->initVars(compiler, scope, returnMode);
    }

    if (nfunction) {
        nfunction->initVars(compiler, scope, returnMode);
    }

    if (rightSide) {
        rightSide->initVars(compiler, scope, returnMode);
    }

    if (!var && !inFunctionDeclaration && op.isFirstAssignment && typeName) {
        auto leftVar = scope->getCVar(compiler, scope, nullptr, name, VSM_LocalThisParent);
        if (leftVar) {
            compiler->addError(loc, CErrorCode::ImmutableAssignment, "var '%s' already exists", name.c_str());
            return;
        }

        auto leftType = scope->getVarType(loc, compiler, typeName, CTM_Undefined);

        string nameNS;
        bool isFirst = true;
        for (auto ns : packageNamespace) {
            if (isFirst) {
                isFirst = false;
            }
            else {
                nameNS += "_";
            }
            nameNS += ns;
        }
        if (!isFirst) {
            nameNS += "_";
        }
        nameNS += name;

        if (name[0] == '_') {
            compiler->addError(loc, CErrorCode::InvalidType, "local var cannot be private '%s'", name.c_str());
            return;
        }

        auto leftStoreVar = make_shared<CNormalVar>(loc, scope, leftType, name, (scope->function->name == "global" ? "g_" : "") + nameNS, op.isMutable, CVarType::Var_Local, nullptr);
        scope->addOrUpdateLocalVar(compiler, packageNamespace, leftStoreVar);
    }
}

shared_ptr<CVar> NAssignment::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CType> returnType, CTypeMode returnMode) {
    // function vars are not created here, this is only for local vars
    if (inFunctionDeclaration) {
        return nullptr;
    }
    
    // We need to see if var already exists, if not create a new local var
    auto cfunction = static_pointer_cast<CBaseFunction>(scope->function);
    shared_ptr<CVar> parentVar = nullptr;
    if (var) {
        parentVar = var->getVar(compiler, scope, nullptr, nullptr, returnMode);
        if (!parentVar) {
            return nullptr;
        }

        auto parentType = parentVar->getType(compiler);
        cfunction = parentType->parent.lock();
        if (!cfunction) {
            compiler->addError(loc, CErrorCode::InvalidVariable, "var must be a function");
            return nullptr;
        }
    }
    
    // Check for operator overload first
    string setFunctionName = "set" + name;
    auto setFunction = cfunction->getCFunction(compiler, loc, setFunctionName, scope, nullptr, returnMode);
    if (parentVar && setFunction) {
        if (returnMode != CTM_Heap) {
            returnMode = CTM_Stack;
        }

        auto parameters = CCallVar::getParameters(compiler, loc, scope, setFunction, CallArgument::createList(rightSide->getVar(compiler, scope, nullptr, CTM_Undefined)), false, nullptr, returnMode);
        return make_shared<CCallVar>(loc, scope, parentVar, parameters, setFunction, returnMode);
    }
    else {
        if (!rightSide) {
            compiler->addError(loc, CErrorCode::InvalidVariable, "assignment needs a right side");
            return nullptr;
        }
        
        shared_ptr<CStoreVar> leftStoreVar;
        if (var) {
            auto dotVar = var->getVar(compiler, scope, nullptr, nullptr, CTM_Undefined);
            if (!dotVar) {
                return nullptr;
            }

            auto dotScope = CScope::getScopeForType(compiler, dotVar->getType(compiler));
            auto leftVar = dotScope->getCVar(compiler, scope, dotVar, name, VSM_ThisOnly);
            if (!leftVar) {
                return nullptr;
            }

            if (!op.isMutable) {
                compiler->addError(loc, CErrorCode::ImmutableAssignment, "immutable assignment to existing var '%s'", name.c_str());
                return nullptr;
            }
            else if (!leftVar->isMutable) {
                compiler->addError(loc, CErrorCode::ImmutableAssignment, "immutable assignment to existing var '%s'", name.c_str());
                return nullptr;
            }

            if (op.isFirstAssignment) {
                compiler->addError(loc, CErrorCode::ImmutableAssignment, "use '=' to assign value to class variables instead of ':' or ':='");
                return nullptr;
            }

            leftStoreVar = dynamic_pointer_cast<CStoreVar>(leftVar);
            if (!leftStoreVar) {
                assert(false);
            }
        }
        else {
            if (op.isFirstAssignment) {
                if (typeName) {
                    auto leftVar = scope->getCVar(compiler, scope, nullptr, name, VSM_LocalThisParentGlobal);
                    if (!leftVar) {
                        compiler->addError(loc, CErrorCode::Internal, "var '%s' should have been initialized already", name.c_str());
                        return nullptr;
                    }

                    leftStoreVar = dynamic_pointer_cast<CStoreVar>(leftVar);
                }
                else {
                    auto leftVar = scope->getCVar(compiler, scope, nullptr, name, VSM_LocalThisParent);
                    if (leftVar) {
                        compiler->addError(loc, CErrorCode::ImmutableAssignment, "var '%s' already exists", name.c_str());
                        return nullptr;
                    }

                    auto fun = static_pointer_cast<CFunction>(cfunction);

                    auto leftType = getType(compiler, scope, CVarType::Var_Local, (op.typeMode == CTM_Undefined) ? returnMode : op.typeMode);
                    if (!leftType) {
                        return nullptr;
                    }

                    string nameNS;
                    bool isFirst = true;
                    for (auto ns : packageNamespace) {
                        if (isFirst) {
                            isFirst = false;
                        }
                        else {
                            nameNS += "_";
                        }
                        nameNS += ns;
                    }
                    if (!isFirst) {
                        nameNS += "_";
                    }
                    nameNS += name;

                    if (name[0] == '_') {
                        compiler->addError(loc, CErrorCode::InvalidType, "local var cannot be private '%s'", name.c_str());
                        return nullptr;
                    }

                    leftStoreVar = make_shared<CNormalVar>(loc, scope, leftType, name, (scope->function->name == "global" ? "g_" : "") + nameNS, op.isMutable, CVarType::Var_Local, nullptr);

                    scope->addOrUpdateLocalVar(compiler, packageNamespace, leftStoreVar);
                }
            }
            else {
                auto leftVar = scope->getCVar(compiler, scope, nullptr, name, VSM_LocalThisParentGlobal);
                if (!leftVar) {
                    compiler->addError(loc, CErrorCode::ImmutableAssignment, "var '%s' does not exist", name.c_str());
                    return nullptr;
                }

                leftStoreVar = dynamic_pointer_cast<CStoreVar>(leftVar);
                if (!leftStoreVar) {
                    compiler->addError(loc, CErrorCode::ImmutableAssignment, "cannot assign to var '%s'", name.c_str());
                    return nullptr;
                }

                if (!op.isMutable) {
                    compiler->addError(loc, CErrorCode::ImmutableAssignment, "immutable assignment to existing var '%s'", name.c_str());
                    return nullptr;
                }
                else if (!leftStoreVar->getCanStoreValue()) {
                    compiler->addError(loc, CErrorCode::ImmutableAssignment, "immutable assignment to existing var '%s'", name.c_str());
                    return nullptr;
                }
            }
        }

        auto leftType = leftStoreVar->getType(compiler);
        if (!leftType) {
            return nullptr;
        }

        if (op.typeMode != CTM_Undefined && leftType->typeMode != op.typeMode) {
            compiler->addError(loc, CErrorCode::Internal, "var '%s' was already defined as '%s' cannot convert to %s", name.c_str(), leftType->fullName.c_str(), op.typeMode == CTM_Heap ? "heap" : op.typeMode == CTM_Stack ? "stack" : "local");
            return nullptr;
        }

        auto rightVar = rightSide->getVar(compiler, scope, leftType, leftType->typeMode);
        if (!rightVar) {
            assert(compiler->errors.size() > 0);
            return nullptr;
        }

        return make_shared<CAssignVar>(loc, scope, op, leftStoreVar, rightVar);
    }

    return nullptr;
}

shared_ptr<CType> NAssignment::getType(Compiler* compiler, shared_ptr<CScope> scope, CVarType varType, CTypeMode returnMode) {
    if (typeName) {
        auto valueType = scope->getVarType(loc, compiler, typeName, returnMode);
        if (!valueType) {
            compiler->addError(loc, CErrorCode::InvalidType, "explicit type '%s' does not exist", typeName->getFullName().c_str());
            return nullptr;
        }
        return valueType;
    }
    
    if (!rightSide) {
        compiler->addError(loc, CErrorCode::Internal, "only required assignment should not have a right side, and they must have typeName");
        return nullptr;
    }
    
    auto rightVar = rightSide->getVar(compiler, scope, nullptr, returnMode);
    if (!rightVar) {
        compiler->addError(loc, CErrorCode::Internal, "no right side");
        return nullptr;
    }

    auto rightType = rightVar->getType(compiler);
    if (!rightType) {
        compiler->addError(loc, CErrorCode::Internal, "right type is undefined");
        return nullptr;
    }

    if (rightType->typeMode != CTM_Value && op.isCopy) {
        if (returnMode == CTM_Heap) {
            return rightType->getHeapType();
        }
        else {
            return rightType->getStackType();
        }
    }

    if (returnMode != CTM_Undefined && returnMode != rightType->typeMode && rightType->typeMode != CTM_Value) {
        if (returnMode == CTM_Local) {
            return rightType->getTempType();
        }
        else {
            compiler->addError(loc, CErrorCode::TypeMismatch, "cannot convert right side to %s", returnMode == CTM_Heap ? "heap" : "stack");
            return nullptr;
        }
    }
    return rightType;
}

shared_ptr<NAssignment> NAssignment::shared_from_this() {
    return static_pointer_cast<NAssignment>(NBase::shared_from_this());
}

