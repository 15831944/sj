#include "Node.h"

bool CThisVar::getReturnThis() {
    return true;
}

shared_ptr<CType> CThisVar::getType(Compiler* compiler) {
    switch (typeMode) {
    case CTM_Stack:
        return types->stackValueType;
    case CTM_Heap:
        return types->heapValueType;
    case CTM_Undefined:
        return types->stackValueType;
    default:
        assert(false);
        return nullptr;
    }
}

void CThisVar::transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> dotValue, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue) {
    storeValue->retainValue(compiler, loc, trBlock, make_shared<TrValue>(nullptr, getType(compiler), "_this", false));
}

void CThisVar::dump(Compiler* compiler, shared_ptr<CVar> dotVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, stringstream& dotSS, int level) {
    ss << "this";
}

void CThisVar::setHasThis() {
    auto function = types->stackValueType->parent.lock();
    function->setHasThis();
}

CTypeMode CThisVar::getTypeMode() {
    if (typeMode == CTM_Undefined) {
        return CTM_Stack;
    }
    return typeMode;
}

shared_ptr<CVar> NThis::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode) {
    if (dotVar) {
        compiler->addError(loc, CErrorCode::InvalidVariable, "this must be the first var in a dot chain");
        return nullptr;
    }

    if (!scope->thisVar) {
        compiler->addError(loc, CErrorCode::InvalidVariable, "function does not have a this value");
        return nullptr;
    }
    
    assert(returnMode != CTM_Value);
    if (returnMode != CTM_Undefined) {
        if (scope->thisVar->typeMode == CTM_Undefined) {
            scope->thisVar->typeMode = returnMode;
        }

        if (returnMode != scope->thisVar->typeMode) {
            compiler->addError(loc, CErrorCode::TypeMismatch, "cannot change this from stack to heap in the same function");
        }
    }

    scope->thisVar->setHasThis();
    return scope->thisVar;
}
