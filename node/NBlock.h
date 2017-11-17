//
//  NBlock.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NBlock_h
#define NBlock_h

#include "NVariable.h"

class CBlockVar : public CVar {
public:
    CBlockVar(CLoc loc, vector<shared_ptr<CVar>> statements) : loc(loc), statements(statements) { }
    shared_ptr<CType> getType(Compiler* compiler, CResult& result, CTypeReturnMode returnMode);
    shared_ptr<ReturnValue> transpileGet(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* trOutput, TrBlock* trBlock, CTypeReturnMode returnMode, shared_ptr<ReturnValue> dotValue, const char* thisName);
    void transpileSet(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<ReturnValue> dotValue, shared_ptr<ReturnValue> returnValue, const char* thisName);
    void dump(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, CTypeReturnMode returnMode, shared_ptr<CVar> dotVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, stringstream& dotSS, int level);
    
private:
    CLoc loc;
    vector<shared_ptr<CVar>> statements;
};

class NBlock : public NVariableBase {
public:
    NBlock(CLoc loc) : NVariableBase(NodeType_Block, loc) { }
    NBlock(CLoc loc, NodeList statements) : NVariableBase(NodeType_Block, loc), statements(statements) { }
    void defineImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunctionDefinition> thisFunction);
    shared_ptr<CVar> getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, CTypeReturnMode returnMode);
    
    NodeList statements;
};

#endif /* NBlock_h */
