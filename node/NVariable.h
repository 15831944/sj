//
//  NVariable.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NVariable_h
#define NVariable_h

#include "NBase.h"

enum ValueType {
    VT_STORE,
    VT_LOAD
};

class NVariableBase : public NBase {
public:
    NVariableBase(NodeType nodeType, CLoc loc) : NBase(nodeType, loc) { }
    shared_ptr<CVar> getVar(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CThisVar> thisVar, shared_ptr<CVar> dotVar, CTypeMode returnMode);
    shared_ptr<CVar> getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CThisVar> thisVar, CTypeMode returnMode) {
        return getVarImpl(compiler, result, thisFunction, thisVar, nullptr, returnMode);
    }

    virtual shared_ptr<CVar> getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CThisVar> thisVar, shared_ptr<CVar> dotVar, CTypeMode returnMode) = 0;
};

class CParentDotVar : public CVar {
public:
    CParentDotVar(CLoc loc, shared_ptr<CBaseFunction> scope) : CVar(loc, scope, "", false) {}
    static shared_ptr<CParentDotVar> create(CLoc loc, Compiler *compiler, CResult &result, shared_ptr<CFunction> parentFunction_, shared_ptr<CVar> childVar_);
    virtual shared_ptr<CType> getType(Compiler* compiler, CResult& result);
    virtual shared_ptr<ReturnValue> transpileGet(Compiler* compiler, CResult& result, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<ReturnValue> dotValue, shared_ptr<ReturnValue> thisValue);
    virtual void transpileSet(Compiler* compiler, CResult& result, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<ReturnValue> dotValue, shared_ptr<ReturnValue> returnValue, shared_ptr<ReturnValue> thisValue, AssignOp op, bool isFirstAssignment);
    virtual void dump(Compiler* compiler, CResult& result, shared_ptr<CVar> dotVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, stringstream& dotSS, int level);
    
    shared_ptr<CFunction> parentFunction;
    shared_ptr<CVar> childVar;
};

class NVariable : public NVariableBase {
public:
    NVariable(CLoc loc, const char* name);
    void defineImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunctionDefinition> thisFunction) { }
    shared_ptr<CVar> getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CThisVar> thisVar, shared_ptr<CVar> dotVar, CTypeMode returnMode);

private:
    string name;
};

#endif /* NVariable_h */
