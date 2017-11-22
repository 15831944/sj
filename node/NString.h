//
//  NString.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NString_h
#define NString_h

class NString : public NVariableBase {
public:
    NString(CLoc loc, const string& str) : NVariableBase(NodeType_String, loc), str(str) {}
    void defineImpl(Compiler* compiler, shared_ptr<CBaseFunctionDefinition> thisFunction) {}
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode);

private:
    string str;
};

#endif /* NString_h */
