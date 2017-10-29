//
//  NMath.h
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#ifndef NMath_h
#define NMath_h

enum NMathOp {
    Add,
    Sub,
    Div,
    Mul,
    Mod
};

class NMath : public NBase {
public:
    NMathOp op;
    const shared_ptr<NBase> leftSide;
    const shared_ptr<NBase> rightSide;
    
    NMath(CLoc loc, shared_ptr<NBase> leftSide, NMathOp op, shared_ptr<NBase> rightSide) : leftSide(leftSide), rightSide(rightSide), op(op), NBase(NodeType_Math, loc) { }
    virtual void dump(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level);

protected:
    virtual void defineImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunctionDefinition> thisFunction);
    virtual shared_ptr<CVar> getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar);
    virtual shared_ptr<CType> getTypeImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar);
    virtual int setHeapVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, bool isHeapVar);
    //virtual shared_ptr<ReturnValue> compileImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, Value* thisValue, IRBuilder<>* builder, BasicBlock* catchBB, ReturnRefType returnRefType);
};

#endif /* NMath_h */
