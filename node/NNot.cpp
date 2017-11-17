#include "Node.h"

shared_ptr<CType> CNotVar::getType(Compiler* compiler, CResult& result, CTypeReturnMode returnMode) {
    return compiler->typeBool;
}

shared_ptr<ReturnValue> CNotVar::transpileGet(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* trOutput, TrBlock* trBlock, CTypeReturnMode returnMode, shared_ptr<ReturnValue> dotValue, const char* thisName) {
    auto value = var->transpileGet(compiler, result, thisFunction, thisVar, trOutput, trBlock, CTRM_NoPref, nullptr, thisName);
    auto resultValue = trBlock->createTempVariable(compiler->typeBool, "result");
    stringstream line;
    line << resultValue->name << " = !" << value->name;
    trBlock->statements.push_back(line.str());
    return resultValue;
}

void CNotVar::transpileSet(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<ReturnValue> dotValue, shared_ptr<ReturnValue> returnValue, const char* thisName) {
    assert(false);
}

void CNotVar::dump(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, CTypeReturnMode returnMode, shared_ptr<CVar> dotVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, stringstream& dotSS, int level) {
    ss << "!";
    var->dump(compiler, result, thisFunction, thisVar, CTRM_NoPref, nullptr, functions, ss, dotSS, level);
}

void NNot::defineImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunctionDefinition> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    node->define(compiler, result, thisFunction);
}

shared_ptr<CVar> NNot::getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, CTypeReturnMode returnMode) {
    assert(compiler->state == CompilerState::FixVar);
    auto var = node->getVar(compiler, result, thisFunction, thisVar, returnMode);
    if (!var) {
        return nullptr;
    }
    return make_shared<CNotVar>(loc, var);
}

