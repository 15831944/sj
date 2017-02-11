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

class CDotVar : public CVar {
public:
    static shared_ptr<CDotVar> create(shared_ptr<CVar> leftVar_, shared_ptr<CVar> rightVar_);
    virtual shared_ptr<CType> getType(Compiler* compiler, CResult& result);
    virtual shared_ptr<ReturnValue> getLoadValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB);
    virtual Value* getStoreValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB);
    string fullName();
    virtual void dump(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, shared_ptr<CVar> thisVar, map<shared_ptr<CFunction>, string>& functions, stringstream& ss, int level);

    shared_ptr<CVar> leftVar;
    shared_ptr<CVar> rightVar;
};

class NDot : public NVariableBase {
public:
    shared_ptr<NVariableBase> left;
    shared_ptr<NVariableBase> right;
    
    NDot(CLoc loc, shared_ptr<NVariableBase> left, shared_ptr<NVariableBase> right) : left(left), right(right), NVariableBase(NodeType_Dot, loc) {}

protected:
    virtual void defineImpl(Compiler* compiler, CResult& result, shared_ptr<CFunctionDefinition> thisFunction);
    virtual shared_ptr<CVar> getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar);
    virtual int setHeapVarImpl(Compiler *compiler, CResult &result, shared_ptr<CFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, bool isHeapVar);
};

#endif /* NDot_h */
