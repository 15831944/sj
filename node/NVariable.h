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
    shared_ptr<CVar> getVar(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode);
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode) {
        return getVarImpl(compiler, scope, nullptr, returnMode);
    }

    virtual shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode) = 0;
};

class NVariableStub : public NVariableBase {
public:
    NVariableStub(shared_ptr<NBase> node) : NVariableBase(NodeType_Variable, CLoc::undefined), node(node) {}

    void defineImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) { node->define(compiler, importNamespaces, packageNamespace, thisFunction);  }
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode) { assert(dotVar == nullptr); return node->getVar(compiler, scope, returnMode); }

    shared_ptr<NBase> node;
};

class NVariable : public NVariableBase {
public:
    NVariable(CLoc loc, const char* name, shared_ptr<CTypeNameList> templateTypeNames);
    void defineImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) { }
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode);

    string name;
    shared_ptr<CTypeNameList> templateTypeNames;
};

#endif /* NVariable_h */
