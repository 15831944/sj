//
//  NCall.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NCall_h
#define NCall_h

#include "NVariable.h"

class NCall;

class CCallVar : public CVar {
public:
    static shared_ptr<CCallVar> create(Compiler* compiler, CResult& result, CLoc loc_, const string& name_, shared_ptr<NodeList> arguments_, shared_ptr<CBaseFunction> thisFunction_, weak_ptr<CVar> dotVar_, shared_ptr<CBaseFunction> callee_);
    shared_ptr<CVar> getThisVar(Compiler* compiler, CResult& result);
    virtual shared_ptr<CType> getType(Compiler* compiler, CResult& result);
    bool getParameters(Compiler* compiler, CResult& result, vector<shared_ptr<NBase>>& parameters);
    //virtual shared_ptr<ReturnValue> getLoadValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, bool dotInEntry, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB, ReturnRefType returnRefType);
    //virtual Value* getStoreValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, bool dotInEntry, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB);
    string fullName();
    virtual bool getHeapVar(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar);
    virtual int setHeapVar(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar);
    virtual shared_ptr<CType> transpile(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* output, TrFunction* function, stringstream& line);
	virtual void dump(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, stringstream& dotSS, int level);

    CLoc loc;
    shared_ptr<NodeList> arguments;
    shared_ptr<CBaseFunction> thisFunction;
    weak_ptr<CVar> dotVar;
    shared_ptr<CBaseFunction> callee;
    shared_ptr<CVar> calleeVar;
    
private:
    bool isHeapVar;
    bool isInGetHeapVar;
};

class NCall : public NVariableBase {
public:
    shared_ptr<NBase> thisNode;
    string name;
    shared_ptr<CTypeNameList> templateTypeNames;
    shared_ptr<NodeList> arguments;
    
    NCall(CLoc loc, const char* name, shared_ptr<CTypeNameList> templateTypeNames, shared_ptr<NodeList> arguments);

protected:
    virtual void defineImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunctionDefinition> thisFunction);
    virtual shared_ptr<CVar> getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar);
    shared_ptr<CBaseFunction> getCFunction(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> dotVar);
    virtual int setHeapVarImpl(Compiler *compiler, CResult &result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, bool isHeapVar);

private:
    shared_ptr<NCall> shared_from_this() { return static_pointer_cast<NCall>(NBase::shared_from_this()); };
    
    shared_ptr<CCallVar> _callVar;
};

#endif /* NCall_h */
