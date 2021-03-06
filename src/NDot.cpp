#include <sjc.h>


void NDot::initFunctionsImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) {
    left->initFunctions(compiler, importNamespaces, packageNamespace, thisFunction);
    right->initFunctions(compiler, importNamespaces, packageNamespace, thisFunction);
}

void NDot::initVarsImpl(Compiler* compiler, shared_ptr<CScope> scope, CTypeMode returnMode) {
    left->initVars(compiler, scope, returnMode);
    right->initVars(compiler, scope, returnMode);
}

shared_ptr<CVar> NDot::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, shared_ptr<CType> returnType, CTypeMode returnMode) {
    vector<string> ns;
    if (dotVar == nullptr) {
        auto leftNVar = dynamic_pointer_cast<NVariable>(left);
        if (leftNVar && (leftNVar->templateTypeNames == nullptr || leftNVar->templateTypeNames->size() == 0)) {
            ns = scope->getNamespace(compiler, leftNVar->name);
        }
    }

    if (ns.size() > 0) {
        scope->pushNamespace(compiler, ns);
        auto rightVar = right->getVar(compiler, scope, nullptr, returnType, returnMode);
        scope->popNamespace(compiler, ns);
        if (!rightVar) {
            compiler->addError(loc, CErrorCode::InvalidDot, "right side of dot has no value");
            return nullptr;
        }
        return rightVar;
    }
    else {
        auto leftVar = left->getVar(compiler, scope, dotVar, nullptr, CTM_Undefined);
        if (!leftVar) {
            compiler->addError(loc, CErrorCode::InvalidDot, "left side of dot has no value");
            return nullptr;
        }

        auto leftType = leftVar->getType(compiler);
        if (!leftType) {
            return nullptr;
        }

        if (leftType->isOption) {
            compiler->addError(loc, CErrorCode::InvalidDot, "left side of dot cannot be option");
            return nullptr;
        }

        if (ns.size() > 0) {
            scope->pushNamespace(compiler, ns);
        }
        auto rightVar = right->getVar(compiler, scope, leftVar, leftType, returnMode);
        if (ns.size() > 0) {
            scope->popNamespace(compiler, ns);
        }
        if (!rightVar) {
            compiler->addError(loc, CErrorCode::InvalidDot, "right side of dot has no value");
            return nullptr;
        }
        
        return rightVar;
    }
}
