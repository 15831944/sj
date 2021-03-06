//
//  NAssignment.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NAssignment_h
#define NAssignment_h

#include "NBase.h"
#include "NVariable.h"

class CCallVar;

class CAssignVar : public CVar {
public:
    CAssignVar(CLoc loc, shared_ptr<CScope> scope, AssignOp op,shared_ptr<CStoreVar> leftVar, shared_ptr<CVar> rightVar) : CVar(loc, scope, "INVALID", "INVALID", op.isMutable), op(op), leftVar(leftVar), rightVar(rightVar) { }
    bool getReturnThis();
    shared_ptr<CType> getType(Compiler* compiler);
    void transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue);
    void dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level);
    
private:
    AssignOp op;
    shared_ptr<CStoreVar> leftVar;
    shared_ptr<CVar> rightVar;
};

class NAssignment : public NBase {
public:
    NAssignment(CLoc loc, shared_ptr<NVariableBase> var, shared_ptr<CTypeName> typeName, const char* name, shared_ptr<NBase> rightSide, AssignOp op);
    void initFunctionsImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction);
    void initVarsImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode);
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CType> returnType, CTypeMode returnMode);
    shared_ptr<CType> getType(Compiler* compiler, shared_ptr<CScope> scope, CVarType varType, CTypeMode returnMode);
    
    shared_ptr<NVariableBase> var;
    shared_ptr<CTypeName> typeName;
    string name;
    bool inFunctionDeclaration;
    shared_ptr<NBase> rightSide;
    shared_ptr<NFunction> nfunction;
    AssignOp op;

private:
    shared_ptr<CVar> _assignVar;
    shared_ptr<NAssignment> shared_from_this();
    shared_ptr<CCallVar> _callVar;
    vector<string> packageNamespace;
};

#endif /* NAssignment_h */
