#include "Node.h"

bool CNegateVar::getReturnThis() {
    return false;
}

shared_ptr<CType> CNegateVar::getType(Compiler* compiler) {
    return var->getType(compiler);
}

void CNegateVar::transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue) {
    auto value = trBlock->createTempStoreVariable(loc, nullptr, var->getType(compiler), "negate");
    var->transpile(compiler, trOutput, trBlock, thisValue, value);
    auto resultValue = trBlock->createTempVariable(nullptr, var->getType(compiler), "result");
    stringstream line;
    line << resultValue->name << " = -" << value->getName(trBlock);
    trBlock->statements.push_back(TrStatement(loc, line.str()));
    storeValue->retainValue(compiler, loc, trBlock, resultValue);
}

void CNegateVar::dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level) {
    ss << "-";
    var->dump(compiler, functions, ss, level);
}

void NNegate::defineImpl(Compiler* compiler, vector<vector<string>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    node->define(compiler, importNamespaces, packageNamespace, thisFunction);
}

shared_ptr<CVar> NNegate::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode) {
    auto var = node->getVar(compiler, scope, CTM_Undefined);
    if (!var) {
        return nullptr;
    }

    auto type = var->getType(compiler);
    if (type->category != CTC_Value || !type->parent.expired()) {
        compiler->addError(loc, CErrorCode::InvalidType, "'-' is only valid for basic types like i32 or f32");
        return nullptr;
    }

    return make_shared<CNegateVar>(loc, scope, var);
}

