#include "Node.h"

bool COrVar::getReturnThis() {
    return false;
}

shared_ptr<CType> COrVar::getType(Compiler* compiler) {
    return compiler->typeBool;
}

void COrVar::transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue) {
    auto leftValue = trBlock->createTempStoreVariable(loc, nullptr, compiler->typeBool, "or");
    auto rightValue = trBlock->createTempStoreVariable(loc, nullptr, compiler->typeBool, "or");
    leftVar->transpile(compiler, trOutput, trBlock, thisValue, leftValue);
    rightVar->transpile(compiler, trOutput, trBlock, thisValue, rightValue);

    stringstream line;
    line << leftValue->getName(trBlock) << " || " << rightValue->getName(trBlock);

    auto resultValue = make_shared<TrValue>(nullptr, compiler->typeBool, line.str(), false);
    storeValue->retainValue(compiler, loc, trBlock, resultValue);
}

void COrVar::dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level) {
    leftVar->dump(compiler, functions, ss, level);
    ss << " && ";
    rightVar->dump(compiler, functions, ss, level);
}

void NOr::defineImpl(Compiler* compiler, shared_ptr<CBaseFunctionDefinition> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    left->define(compiler, thisFunction);
    right->define(compiler, thisFunction);
}

shared_ptr<CVar> NOr::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode) {
    auto leftVar = left->getVar(compiler, scope, nullptr, CTM_Undefined);
    if (!leftVar) {
        return nullptr;
    }
    auto rightVar = right->getVar(compiler, scope, nullptr, CTM_Undefined);
    if (!rightVar) {
        return nullptr;
    }
    return make_shared<COrVar>(loc, scope, leftVar, rightVar);
}
