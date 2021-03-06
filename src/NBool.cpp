#include <sjc.h>


shared_ptr<CVar> NBool::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, shared_ptr<CType> returnType, CTypeMode returnMode) {
    return make_shared<CConstantVar>(loc, scope, compiler->typeBool, bool_to_str(value));
}
