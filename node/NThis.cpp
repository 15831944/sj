#include "Node.h"

NThis::NThis(CLoc loc) : NVariableBase(NodeType_This, loc) { }

shared_ptr<ReturnValue> NThis::transpile(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* trOutput, TrBlock* trBlock, CTypeReturnMode returnMode, const char* thisName) {
	return make_shared<ReturnValue>(
        thisVar->getType(compiler, result), 
        "_this");
}

shared_ptr<CVar> NThis::getVarImpl(Compiler *compiler, CResult &result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, CTypeReturnMode returnMode) {
    if (dotVar) {
        result.addError(loc, CErrorCode::InvalidVariable, "this must be the first var in a dot chain");
        return nullptr;
    }
    
    thisVar->parent.lock()->setHasRefCount();    
    return thisVar;
}
