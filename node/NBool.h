//
//  NBool.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NBool_h
#define NBool_h

class NBool : public NVariableBase {
public:
    bool value;
    
    NBool(CLoc loc, bool value) : NVariableBase(NodeType_Bool, loc), value(value) { }

    void defineImpl(Compiler* compiler, vector<vector<string>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) { }
    shared_ptr<CVar> getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode);
};

#endif /* NBool_h */
