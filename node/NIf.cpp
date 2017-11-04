#include "Node.h"

shared_ptr<CIfElseVar> CIfElseVar::create(const CLoc& loc_, shared_ptr<NIf> nif_, shared_ptr<CBaseFunction> thisFunction_, shared_ptr<CVar> thisVar_, shared_ptr<NBase> condition_, shared_ptr<NBase> ifBlock_, shared_ptr<NBase> elseBlock_) {
    auto c = make_shared<CIfElseVar>();
    c->name = "";
    c->mode = Var_Private;
    c->isMutable = true;
    c->nassignment = nullptr;
    c->loc = loc_;
    c->nif = nif_;
    c->thisFunction = thisFunction_;
    c->thisVar = thisVar_;
    c->condition = condition_;
    c->ifBlock = ifBlock_;
    c->elseBlock = elseBlock_;
    return c;
}

shared_ptr<CType> CIfElseVar::getType(Compiler* compiler, CResult& result) {
    if (elseBlock) {
        return elseBlock->getType(compiler, result, thisFunction, thisVar);
    }
    
    if (ifBlock) {
        return ifBlock->getType(compiler, result, thisFunction, thisVar);
    }
    
    return nullptr;
}

//shared_ptr<ReturnValue> CIfElseVar::getLoadValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, bool dotInEntry, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB, ReturnRefType returnRefType) {
//    assert(compiler->state == CompilerState::Compile);
//    shared_ptr<CType> returnType = getType(compiler, result);
//    
//    Function *function = builder->GetInsertBlock()->getParent();
//    auto ifBB = BasicBlock::Create(compiler->context);
//    auto elseBB = BasicBlock::Create(compiler->context);
//    auto mergeBB = BasicBlock::Create(compiler->context);
//    
//    // If block
//    function->getBasicBlockList().push_back(ifBB);
//    auto c = condition->compile(compiler, result, thisFunction, thisVar, thisValue, builder, catchBB, RRT_Auto);
//    if (!c) {
//        return nullptr;
//    }
//    assert(c->type == RVT_SIMPLE);
//    builder->CreateCondBr(c->value, ifBB, elseBB);
//    builder->SetInsertPoint(ifBB);
//    auto ifValue = ifBlock->compile(compiler, result, thisFunction, thisVar, thisValue, builder, catchBB, RRT_Auto);
//    if (returnType != compiler->typeVoid && !ifValue) {
//        result.addError(loc, CErrorCode::NoDefaultValue, "type does not have a default value");
//        return nullptr;
//    }
//    auto ifEndBB = builder->GetInsertBlock();
//    builder->CreateBr(mergeBB);
//    
//    // Else block
//    function->getBasicBlockList().push_back(elseBB);
//    builder->SetInsertPoint(elseBB);
//    shared_ptr<ReturnValue> elseValue = nullptr;
//    if (elseBlock) {
//        elseValue = elseBlock->compile(compiler, result, thisFunction, thisVar, thisValue, builder, catchBB, RRT_Auto);
//        if (returnType != compiler->typeVoid && !elseValue) {
//            result.addError(loc, CErrorCode::NoDefaultValue, "type does not have a default value");
//            return nullptr;
//        }
//    } else if (returnType != compiler->typeVoid) {
//        elseValue = returnType->getDefaultValue(compiler, result, thisFunction, thisVar, thisValue, builder, catchBB);
//        if (!elseValue) {
//            result.addError(loc, CErrorCode::NoDefaultValue, "type does not have a default value");
//            return nullptr;
//        }
//    }
//    
//    auto elseEndBB = builder->GetInsertBlock();
//    builder->CreateBr(mergeBB);
//    
//    // Merge block
//    function->getBasicBlockList().push_back(mergeBB);
//    builder->SetInsertPoint(mergeBB);
//    if (returnType == compiler->typeVoid) {
//        return nullptr;
//    }
//    
//    if (ifValue->value->getType() != elseValue->value->getType()) {
//        result.addError(loc, CErrorCode::TypeMismatch, "if and else clause have different return types");
//        return nullptr;
//    }
//    
//    assert(ifValue->type == elseValue->type);
//    assert(ifValue->releaseMode == elseValue->releaseMode);
//    
//    auto varType = getType(compiler, result);
//    auto varFunction = varType->parent.lock();
//    
//    auto phiNode = builder->CreatePHI(returnType->llvmRefType(compiler, result), (unsigned)2, "iftmp");
//    phiNode->addIncoming(ifValue->value, ifEndBB);
//    phiNode->addIncoming(elseValue->value, elseEndBB);
//    return make_shared<ReturnValue>(varFunction, ifValue->releaseMode, ifValue->type, false, phiNode);
//}
//
//Value* CIfElseVar::getStoreValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, bool dotInEntry, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB) {
//    assert(false);
//    return nullptr;
//}

string CIfElseVar::fullName() {
    return "";
}

bool CIfElseVar::getHeapVar(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar) {
    if (ifBlock) {
        auto var = ifBlock->getVar(compiler, result, thisFunction, thisVar);
        if (var) {
            return var->getHeapVar(compiler, result, thisVar);
        }
    }
    return false;
}

int CIfElseVar::setHeapVar(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar) {
    return nif->setHeapVar(compiler, result, thisFunction, thisVar, nullptr, true);
}

shared_ptr<ReturnValue> CIfElseVar::transpileGet(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<ReturnValue> dotValue) {
    auto type = getType(compiler, result);
    shared_ptr<ReturnValue> trResultVar;
    if (type != compiler->typeVoid) {
        auto resultHeapVar = getHeapVar(compiler, result, thisVar);
        auto resultFunction = getCFunctionForValue(compiler, result);
        trResultVar = trBlock->createTempVariable("ifResult", type, resultHeapVar, RVR_MustRetain);
    }

    auto conditionReturnValue = condition->transpile(compiler, result, thisFunction, thisVar, trOutput, trBlock);

    stringstream ifLine;
    ifLine << "if (" << conditionReturnValue->name << ")";
    auto trIfBlock = make_shared<TrBlock>();
    trIfBlock->hasThis = trBlock->hasThis;
    trIfBlock->parent = trBlock;
    auto trStatement = TrStatement(ifLine.str(), trIfBlock);

    auto ifReturnValue = ifBlock->transpile(compiler, result, thisFunction, thisVar, trOutput, trIfBlock.get());
    assert(ifReturnValue == nullptr || ifReturnValue->release == RVR_MustRetain);

    if (type != compiler->typeVoid) {
        stringstream resultLine;
        if (type != compiler->typeVoid) {
            resultLine << trResultVar->name + " = " << ifReturnValue->name;
        }

        trIfBlock->statements.push_back(resultLine.str());
    }

    if (elseBlock || type != compiler->typeVoid) {
        shared_ptr<ReturnValue> elseReturnValue;
        auto trElseBlock = make_shared<TrBlock>();
        trElseBlock->parent = trBlock;
        trElseBlock->hasThis = trBlock->hasThis;
        trStatement.elseBlock = trElseBlock;

        if (elseBlock) {
            elseReturnValue = elseBlock->transpile(compiler, result, thisFunction, thisVar, trOutput, trElseBlock.get());
            assert(elseReturnValue == nullptr || elseReturnValue->release == RVR_MustRetain);
        }
        else {
            elseReturnValue = type->transpileDefaultValue(compiler, result, thisFunction, thisVar);
        }

        if (type != compiler->typeVoid) {
            stringstream resultLine;
            if (type != compiler->typeVoid) {
                resultLine << trResultVar->name + " = " << elseReturnValue->name;
            }

            trElseBlock->statements.push_back(resultLine.str());
        }
    }

    trBlock->statements.push_back(trStatement);

    return trResultVar;
}

void CIfElseVar::transpileSet(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* trOutput, TrBlock* trBlock, shared_ptr<ReturnValue> dotValue, shared_ptr<ReturnValue> returnValue) {
    assert(false);
}

void CIfElseVar::dump(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, stringstream& dotSS, int level) {
    ss << "if ";
    condition->dump(compiler, result, thisFunction, thisVar, functions, ss, level);

    if (ifBlock) {
        ss << " ";
        ifBlock->dump(compiler, result, thisFunction, thisVar, functions, ss, level);
    }
    
    if (elseBlock) {
        ss << " else ";
        elseBlock->dump(compiler, result, thisFunction, thisVar, functions, ss, level);
    }
}

void NIf::defineImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunctionDefinition> thisFunction) {
    assert(compiler->state == CompilerState::Define);
    condition->define(compiler, result, thisFunction);

    if (elseBlock) {
        elseBlock->define(compiler, result, thisFunction);
    }
    
    if (ifBlock) {
        ifBlock->define(compiler, result, thisFunction);
    }
}

shared_ptr<CVar> NIf::getVarImpl(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar) {
    assert(compiler->state == CompilerState::FixVar);
    condition->getVar(compiler, result, thisFunction, thisVar);
    
    if (elseBlock) {
        elseBlock->getVar(compiler, result, thisFunction, thisVar);
    }
    
    if (ifBlock) {
        ifBlock->getVar(compiler, result, thisFunction, thisVar);
    }
    
    return CIfElseVar::create(loc, shared_from_this(), thisFunction, thisVar, condition, ifBlock, elseBlock);
}

int NIf::setHeapVarImpl(Compiler *compiler, CResult &result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, bool isHeapVar) {
    auto count = condition->setHeapVar(compiler, result, thisFunction, thisVar, false);
    if (elseBlock) {
        count += elseBlock->setHeapVar(compiler, result, thisFunction, thisVar, isHeapVar);
    }
    
    if (ifBlock) {
        count += ifBlock->setHeapVar(compiler, result, thisFunction, thisVar, isHeapVar);
    }
    
    return count;
}

shared_ptr<NIf> NIf::shared_from_this() {
    return static_pointer_cast<NIf>(NBase::shared_from_this());
}

