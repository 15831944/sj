//
//  NDot.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NDot_h
#define NDot_h

#include "NVariable.h"
/*
class CDotVar : public CStoreVar {
public:
    CDotVar(CLoc loc, shared_ptr<CScope> scope, shared_ptr<CVar> leftVar, shared_ptr<CVar> rightVar) : CStoreVar(loc, scope, "INVALID", "INVALID", false), leftVar(leftVar), rightVar(rightVar) {}
    bool getReturnThis();
    shared_ptr<CType> getType(Compiler* compiler);
    void transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue);
    bool getCanStoreValue();
    shared_ptr<TrStoreValue> getStoreValue(Compiler* compiler, shared_ptr<CScope> scope, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, AssignOp op);
    void dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level);

private:
    shared_ptr<CVar> leftVar;
    shared_ptr<CVar> rightVar;
};
*/
class NDot : public NVariableBase {
public:
    shared_ptr<NVariableBase> left;
    shared_ptr<NVariableBase> right;
    
    NDot(CLoc loc, shared_ptr<NVariableBase> left, shared_ptr<NVariableBase> right) : NVariableBase(NodeType_Dot, loc), left(left), right(right) {}

    virtual void defineImpl(Compiler* compiler, shared_ptr<CBaseFunctionDefinition> thisFunction);
    virtual shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode);
};

#endif /* NDot_h */
