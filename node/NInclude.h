//
//  NInclude.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NInclude_h
#define NInclude_h

class NInclude : public NBase {
public:
    string fileName;
    
    NInclude(CLoc loc, const char* fileName) : fileName(fileName), NBase(loc) { }
    virtual NodeType getNodeType() const;
    virtual void define(Compiler* compiler, CResult& result, shared_ptr<CFunctionDefinition> thisFunction);
    virtual void fixVar(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction);
    virtual shared_ptr<CType> getReturnType(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction) const;
    virtual Value* compile(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, Value* thisValue, IRBuilder<>* builder, BasicBlock* catchBB) const;
    virtual void dump(Compiler* compiler, int level) const;
};

#endif /* NInclude_h */