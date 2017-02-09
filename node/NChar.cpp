#include "Node.h"

shared_ptr<CType> NChar::getTypeImpl(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, shared_ptr<CVar> thisVar) {
    assert(compiler->state >= CompilerState::FixVar);
    return compiler->typeChar;
}

shared_ptr<ReturnValue> NChar::compileImpl(Compiler* compiler, CResult& result, shared_ptr<CFunction> thisFunction, shared_ptr<CVar> thisVar, Value* thisValue, IRBuilder<>* builder, BasicBlock* catchBB) {
    assert(compiler->state == CompilerState::Compile);
    compiler->emitLocation(this);    
    return make_shared<ReturnValue>(ConstantInt::get(compiler->context, APInt(8, value)));
}

void NChar::dump(Compiler* compiler, int level) const {
    dumpf(level, "value: %c", value);
}
