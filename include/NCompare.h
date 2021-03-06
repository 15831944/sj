//
//  NCompare.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NCompare_h
#define NCompare_h

enum NCompareOp {
    EQ,
    NE,
    PEQ,
    PNE,
    GT,
    GE,
    LT,
    LE
};

class CCompareVar : public CVar {
public:
    CCompareVar(CLoc loc, shared_ptr<CScope> scope, NCompareOp op, shared_ptr<CVar> leftVar, shared_ptr<CVar> rightVar) : CVar(loc, scope), op(op), leftVar(leftVar), rightVar(rightVar) { }
    bool getReturnThis();
    shared_ptr<CType> getType(Compiler* compiler);
    void transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue);
    void dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level);
    
private:
    NCompareOp op;
    shared_ptr<CVar> leftVar;
    shared_ptr<CVar> rightVar;
};


class NCompare : public NVariableBase {
public:
    NCompare(CLoc loc, shared_ptr<NBase> leftSide, NCompareOp op, shared_ptr<NBase> rightSide) : NVariableBase(NodeType_Compare, loc), op(op), leftSide(leftSide), rightSide(rightSide) { }
    void initFunctionsImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction);
    void initVarsImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode);
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, shared_ptr<CType> returnType, CTypeMode returnMode);
    
private:
    NCompareOp op;
    const shared_ptr<NBase> leftSide;
    const shared_ptr<NBase> rightSide;
    shared_ptr<NBase> operatorOverloadNode;
};

#endif /* NCompare_h */
