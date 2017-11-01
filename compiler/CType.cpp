//
//  Compiler.cpp
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#include "../node/Node.h"

#ifdef DWARF_ENABLED
CType::CType(const char* name/*, Type* llvmAllocType, DIType* diType, Value* value*/) : category(CTC_Value), nameVal(name), nameRef(name)/*, _llvmAllocType(llvmAllocType), _llvmRefType(llvmAllocType), _diType(diType), _value(value)*/ {
}
#else
CType::CType(const char* name, Type* llvmAllocType, Value* value) : category(CTC_Value), name(name), _llvmAllocType(llvmAllocType), _llvmRefType(llvmAllocType), _value(value) {
}
#endif

CType::CType(const char* name, weak_ptr<CFunction> parent) : category(CTC_Function), nameVal(name), nameRef(string(name) + "*"), parent(parent)/*, _llvmAllocType(nullptr), _llvmRefType(nullptr), _value(nullptr) */{
//#ifdef DWARF_ENABLED
//    _diType = nullptr;
//#endif
}

CType::CType(const char* name, weak_ptr<CInterface> parent) : category(CTC_Interface), nameVal(name), nameRef(string(name) + "*"), parent(parent)/*, _llvmAllocType(nullptr), _llvmRefType(nullptr), _value(nullptr) */{
//#ifdef DWARF_ENABLED
//    _diType = nullptr;
//#endif
}

//#ifdef DWARF_ENABLED
//DIType* CType::getDIType(Compiler* compiler, CResult& result) {
//    if (_diType) {
//        return _diType;
//    }
//    
//    _diType = compiler->DBuilder->createBasicType("int", 64, 64, dwarf::DW_ATE_signed);
//    // TODO: Actually create a debug type for structs
//    return _diType;
//}
//#endif
//
//Type* CType::llvmAllocType(Compiler* compiler, CResult& result) {
//    if (!_llvmAllocType) {
//        _llvmAllocType = parent.lock()->getStructType(compiler, result);
//    }
//    return _llvmAllocType;
//}
//
//Type* CType::llvmRefType(Compiler* compiler, CResult& result) {
//    if (!_llvmRefType) {
//        auto t = llvmAllocType(compiler, result);
//        if (t) {
//            _llvmRefType = t->getPointerTo();
//        }
//    }
//    return _llvmRefType;
//}

//shared_ptr<ReturnValue> CType::getDefaultValue(Compiler* compiler, CResult& result, shared_ptr<CBaseFunction> thisFunction, shared_ptr<CVar> thisVar, Value* thisValue, IRBuilder<>* builder, BasicBlock* catchBB) {
//    if (parent.expired()) {
//        return _value ? make_shared<ReturnValue>(false, _value) : nullptr;
//    }
//    return nullptr;
//}
