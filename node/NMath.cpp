#include "Node.h"

bool CMathVar::getReturnThis() {
    return false;
}

shared_ptr<CType> CMathVar::getType(Compiler* compiler) {
    return leftVar->getType(compiler);
}

void CMathVar::transpile(Compiler* compiler, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<TrValue> thisValue, shared_ptr<TrStoreValue> storeValue) {
    auto leftValue = trBlock->createTempStoreVariable(loc, nullptr, leftVar->getType(compiler), "math");
    auto rightValue = trBlock->createTempStoreVariable(loc, nullptr, leftVar->getType(compiler), "math");
    leftVar->transpile(compiler, trOutput, trBlock, thisValue, leftValue);
    rightVar->transpile(compiler, trOutput, trBlock, thisValue, rightValue);

    stringstream line;
    line << leftValue->getName(trBlock);
    switch (op) {
    case NMathOp::Add:
        line << " + ";
        break;
    case NMathOp::Sub:
        line << " - ";
        break;
    case NMathOp::Mul:
        line << " * ";
        break;
    case NMathOp::Div:
        line << " / ";
        break;
    case NMathOp::Mod:
        line << " % ";
        break;
    }
    line << rightValue->getName(trBlock);

    auto resultValue = make_shared<TrValue>(nullptr, leftVar->getType(compiler), line.str(), false);
    storeValue->retainValue(compiler, loc, trBlock, resultValue);
}

void CMathVar::dump(Compiler* compiler, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, int level) {
    leftVar->dump(compiler, functions, ss, level);
    
    switch (op) {
        case NMathOp::Add:
            ss << " + ";
            break;
        case NMathOp::Sub:
            ss << " - ";
            break;
        case NMathOp::Mul:
            ss << " * ";
            break;
        case NMathOp::Div:
            ss << " / ";
            break;
        case NMathOp::Mod:
            ss << " %% ";
            break;
    }
    
    rightVar->dump(compiler, functions, ss, level);
}

void NMath::defineImpl(Compiler* compiler, vector<pair<string, vector<string>>>& importNamespaces, vector<string>& packageNamespace, shared_ptr<CBaseFunctionDefinition> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    leftSide->define(compiler, importNamespaces, packageNamespace, thisFunction);
    rightSide->define(compiler, importNamespaces, packageNamespace, thisFunction);
}

shared_ptr<CVar> NMath::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, CTypeMode returnMode) {
    auto leftVar = leftSide->getVar(compiler, scope, nullptr, CTM_Undefined);
    auto rightVar = rightSide->getVar(compiler, scope, nullptr, CTM_Undefined);

    if (!leftVar || !rightVar) {
        return nullptr;
    }

    auto leftType = leftVar->getType(compiler);
    auto rightType = rightVar->getType(compiler);
    if (!leftType || !rightType) {
        return nullptr;
    }

    string rightTypeName;
    if (!CType::isSameExceptMode(leftType, rightType)) {
        rightTypeName = rightType->shortName;
    }

    string functionName;
    switch (op) {
    case NMathOp::Add:
        functionName = "add" + rightTypeName;
        break;
    case NMathOp::Sub:
        functionName = "subtract" + rightTypeName;
        break;
    case NMathOp::Div:
        functionName = "divide" + rightTypeName;
        break;
    case NMathOp::Mul:
        functionName = "multiply" + rightTypeName;
        break;
    case NMathOp::Mod:
        functionName = "modulus" + rightTypeName;
        break;
    default:
        assert(false);
        return nullptr;
    }

    // Check to see if we have operator overloading
    bool isHelperFunction;
    auto cfunction = NCall::getCFunction(compiler, loc, scope, leftVar, functionName, nullptr, returnMode, &isHelperFunction);
    if (cfunction) {
        operatorOverloadNode = make_shared<NDot>(loc, leftSide, make_shared<NCall>(loc, functionName, nullptr, make_shared<NodeList>(rightSide)));
        return operatorOverloadNode->getVar(compiler, scope, returnMode);
    } else {
        if (!CType::isSameExceptMode(leftType, rightType)) {
            compiler->addError(loc, CErrorCode::TypeMismatch, "left type '%s' does not match right type '%s' and no helper function '%s'", leftType->fullName.c_str(), rightType->fullName.c_str(), functionName.c_str());
            return nullptr;
        }

        return make_shared<CMathVar>(loc, scope, op, leftVar, rightVar);
    }
}
