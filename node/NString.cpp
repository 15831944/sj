#include "Node.h"

class CGlobalPtrVar : public CVar {
public:
    CGlobalPtrVar(CLoc loc, shared_ptr<CScope> scope, string varName, string str) : CVar(loc, scope), varName(varName), str(str) { }
    bool getReturnThis();
    shared_ptr<CType> getType(Compiler* compiler);
    void transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue);
    void dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level);
    
private:
    string varName;
    string str;
};

bool CGlobalPtrVar::getReturnThis() {
    return false;
}

shared_ptr<CType> CGlobalPtrVar::getType(Compiler* compiler) {
    return compiler->typePtr;
}

void CGlobalPtrVar::transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue) {
    trOutput->strings[varName] = str;
    auto resultValue = make_shared<TrValue>(nullptr, compiler->typePtr, "(void*)" + varName, false);
    storeValue->retainValue(compiler, loc, trBlock, resultValue);
}

void CGlobalPtrVar::dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level) {
}

class NGlobalPtrVar : public NBase {
public:
    NGlobalPtrVar(CLoc loc, const string& varName, const string& str) : NBase(NodeType_Integer, loc), varName(varName), str(str) {}
    void defineImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) {}
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode);
    
private:
    string varName;
    string str;
};

shared_ptr<CVar> NGlobalPtrVar::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode) {
    return make_shared<CGlobalPtrVar>(loc, scope, varName, str);
}

shared_ptr<CVar> NString::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode) {
    auto varName = TrBlock::nextVarName("sjg_string");

    auto createArray = make_shared<NCall>(
        loc,
        "array",
        make_shared<CTypeNameList>(CTC_Value, CTM_Stack, compiler->typeChar->valueName, false),
        make_shared<NodeList>(
            make_shared<NInteger>(loc, str.size() + 1),
            make_shared<NGlobalPtrVar>(loc, varName, str),
            make_shared<NBool>(loc, true),
            make_shared<NInteger>(loc, str.size() + 1)));

    auto createString = make_shared<NCall>(
        loc,
        "string",
        nullptr,
        make_shared<NodeList>(
            make_shared<NInteger>(loc, str.size()),
            createArray));

    return createString->getVar(compiler, scope, dotVar, returnMode);
}
