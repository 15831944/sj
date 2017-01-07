//
//  NVariable.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NVariable_h
#define NVariable_h

class NVariable : public NBase {
public:
    vector<string> names;
    
    NVariable(CLoc loc, const char* name);
    virtual NodeType getNodeType() const;
    virtual void define(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction) { }
    virtual void fixVar(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction);
    virtual shared_ptr<CType> getReturnType(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction) const;
    virtual Value* compile(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, Value* thisValue, IRBuilder<>* builder) const;
    virtual void dump(Compiler* compiler, int level) const;
  
    static shared_ptr<CType> getParentValue(Compiler* compiler, CResult& result, const CLoc& loc, shared_ptr<CFunction> thisFunction, Value* thisValue, IRBuilder<>* builder, const vector<string>& names, Value** value);

};

#endif /* NVariable_h */
