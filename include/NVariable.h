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
    shared_ptr<CVar> getVar(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, shared_ptr<CType> returnType, CTypeMode returnMode);
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CType> returnType, CTypeMode returnMode) {
        return getVarImpl(compiler, scope, nullptr, returnType, returnMode);
    }

    virtual shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, shared_ptr<CType> returnType, CTypeMode returnMode) = 0;
};

class NVariableStub : public NVariableBase {
public:
    NVariableStub(shared_ptr<NBase> node) : NVariableBase(NodeType_Variable, CLoc::undefined), node(node) {}

    void initFunctionsImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) { 
        node->initFunctions(compiler, importNamespaces, packageNamespace, thisFunction);
    }
    void initVarsImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode) {
        node->initVars(compiler, scope, returnMode);
    }
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, shared_ptr<CType> returnType, CTypeMode returnMode) { assert(dotVar == nullptr); return node->getVar(compiler, scope, returnType, returnMode); }

    shared_ptr<NBase> node;
};

class NVariable : public NVariableBase {
public:
    NVariable(CLoc loc, const char* name, shared_ptr<CTypeNameList> templateTypeNames);
    void initFunctionsImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) { }
    void initVarsImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode) {}
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, shared_ptr<CType> returnType, CTypeMode returnMode);

    string name;
    shared_ptr<CTypeNameList> templateTypeNames;
};

#endif /* NVariable_h */
