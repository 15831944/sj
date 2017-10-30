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

shared_ptr<CType> NIf::transpile(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* output, TrFunction* function, stringstream& line) {
	auto type = getType(compiler, result, thisFunction, thisVar);
	string ifResultName;

	if (type != compiler->typeVoid) {
		auto index = 0;
		do {
			index++;
			stringstream ss;
			ss << "ifResult" << index;
			ifResultName = ss.str();
		} while (function->variables.find(ifResultName) != function->variables.end());
		function->variables[ifResultName] = type->name;
	}

	stringstream ifLine;
	ifLine << "if (";
	condition->transpile(compiler, result, thisFunction, thisVar, output, function, ifLine);
	ifLine << ") {";
	function->statements.push_back(ifLine.str());

	if (ifBlock) {
		stringstream empty;
		ifBlock->transpile(compiler, result, thisFunction, thisVar, output, function, empty);
		assert(empty.str().size() == 0);

		if (type != compiler->typeVoid) {
			auto lastLine = function->statements.back();
			lastLine = ifResultName + " = " + lastLine;
			function->statements.pop_back();
			function->statements.push_back(lastLine);
		}
	}

	if (elseBlock) {
		function->statements.push_back("} else {");
		stringstream empty;
		elseBlock->transpile(compiler, result, thisFunction, thisVar, output, function, empty);
		assert(empty.str().size() == 0);

		if (type != compiler->typeVoid) {
			auto lastLine = function->statements.back();
			lastLine = ifResultName + " = " + lastLine;
			function->statements.pop_back();
			function->statements.push_back(lastLine);
		}
	}

	function->statements.push_back("}");
	if (type != compiler->typeVoid) {
		function->statements.push_back(ifResultName);
	}
	return type;
}
