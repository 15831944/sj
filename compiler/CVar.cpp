//
//  Compiler.cpp
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#include "../node/Node.h"

string CVar::fullName() {
    return strprintf("%s.%s", parent.lock()->fullName(false).c_str(), name.c_str());
}

shared_ptr<CBaseFunction> CVar::getCFunctionForValue(Compiler* compiler, CResult& result) {
    auto ctype = getType(compiler, result);
    if (ctype && !ctype->parent.expired()) {
        return ctype->parent.lock();
    }
    return nullptr;
}

shared_ptr<CNormalVar> CNormalVar::createThisVar(const CLoc& loc, shared_ptr<CBaseFunction> parent, shared_ptr<CType> type) {
    auto c = make_shared<CNormalVar>();
    c->loc = loc;
    c->mode = CVarType::Var_This;
    c->name = "this";
    c->isMutable = false;
    c->type = type;
    c->parent = parent;
    return c;
}

shared_ptr<CNormalVar> CNormalVar::createLocalVar(const CLoc& loc, const string& name, shared_ptr<CBaseFunction> parent, shared_ptr<NAssignment> nassignment) {
    auto c = make_shared<CNormalVar>();
    c->loc = loc;
    c->mode = CVarType::Var_Local;
    c->name = name;
    c->isMutable = nassignment != nullptr ? nassignment->isMutable : false;
    c->nassignment = nassignment;
    c->parent = parent;
    return c;
}

shared_ptr<CNormalVar> CNormalVar::createFunctionVar(const CLoc& loc, const string& name, shared_ptr<CBaseFunction> parent, int index, shared_ptr<NAssignment> nassignment, shared_ptr<CType> type, shared_ptr<CVar> interfaceMethodArgVar_) {
    auto c = make_shared<CNormalVar>();
    c->loc = loc;
    c->mode = CVarType::Var_Public;
    c->name = name;
    c->isMutable = nassignment != nullptr ? nassignment->isMutable : false;
    c->index = index;
    c->nassignment = nassignment;
    c->parent = parent;
    c->type = type;
    c->isHeapVar = false;
    c->interfaceMethodArgVar = interfaceMethodArgVar_;
    
    if (interfaceMethodArgVar_) {
        auto t = static_pointer_cast<CInterfaceMethodArgVar>(interfaceMethodArgVar_);
        t->functionVars.push_back(c);
    }
    
    assert(type != nullptr || nassignment != nullptr);
    
    return c;
}

void CNormalVar::makeFunctionVar(int index) {
    assert(mode == CVarType::Var_Local);
    mode = CVarType::Var_Public;
    this->index = index;
}

shared_ptr<CType> CNormalVar::getType(Compiler* compiler, CResult& result) {
    if (isInGetType) {
        result.addError(CLoc::undefined, CErrorCode::TypeLoop, "while trying to determine type a cycle was detected");
        return nullptr;
    }
    
    isInGetType = true;
    if (!type) {
        type = nassignment->getType(compiler, result, parent.lock(), nullptr); // TODO:
    }
    isInGetType = false;
    return type;
}

//shared_ptr<ReturnValue> CNormalVar::getLoadValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, bool dotInEntry, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB, ReturnRefType returnRefType) {
//    if (mode == Var_This) {
//        return make_shared<ReturnValue>(parent.lock(), RVR_MustRetain, RVT_HEAP, true, thisValue);
//    } else {
//        // TODO: Can be smarter about whether or not return value is in entry
//        auto value = getStoreValue(compiler, result, thisVar, thisValue, dotInEntry, dotValue, builder, catchBB);
//        return make_shared<ReturnValue>(type->parent.lock(), RVR_MustRetain, RVT_HEAP, false, builder->CreateLoad(value));
//    }
//}
//
//Value* CNormalVar::getStoreValue(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar, Value* thisValue, bool dotInEntry, Value* dotValue, IRBuilder<>* builder, BasicBlock* catchBB) {
//    if (mode == Var_This) {
//        assert(false);
//    } else if (mode == Var_Local) {
//        if (!value) {
//            auto entryBuilder = compiler->getEntryBuilder(getFunctionFromBuilder(builder));
//            auto valueType = getType(compiler, result)->llvmRefType(compiler, result);
//            if (valueType->isVoidTy()) {
//                result.addError(loc, CErrorCode::StoringVoid, "cannot save a void value");
//                return nullptr;
//            }
//            value = entryBuilder->CreateAlloca(valueType, 0, name.c_str());
//        }
//        return value;
//    } else {
//        auto fun = static_pointer_cast<CFunction>(parent.lock());
//        return fun->getArgumentPointer(compiler, result, dotInEntry, dotValue, index, builder);
//    }
//}

bool CNormalVar::getHeapVar(Compiler *compiler, CResult &result, shared_ptr<CVar> thisVar) {
    if (interfaceMethodArgVar) {
        return interfaceMethodArgVar->getHeapVar(compiler, result, thisVar);
    }
    return isHeapVar;
}

int CNormalVar::setHeapVar(Compiler* compiler, CResult& result, shared_ptr<CVar> thisVar) {
    auto count = 0;

    if (interfaceMethodArgVar) {
        count += interfaceMethodArgVar->setHeapVar(compiler, result, thisVar);
    }
    
    if (!isHeapVar) {
        isHeapVar = true;
        
        auto t = getType(compiler, result);
        if (!t->parent.expired()) {
            t->parent.lock()->setHasRefCount();
        }
        
        count += 1;
    }
    
    return count;
}

shared_ptr<CType> CNormalVar::transpile(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, TrOutput* output, TrFunction* function, stringstream& line) {
    assert(false);
}

void CNormalVar::dump(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, shared_ptr<CVar> dotVar, map<shared_ptr<CBaseFunction>, string>& functions, stringstream& ss, stringstream& dotSS, int level) {
    if (dotSS.gcount()) {
        ss << dotSS.str() << ".";
    }
    
    if (mode == Var_Public || mode == Var_Private) {
        ss << "this.";
    }
    
    ss << name;
}


