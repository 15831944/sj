//
//  Compiler.cpp
//  sj
//
//  Created by Mann, Justin on 12/25/16.
//  Copyright © 2016 Mann, Justin. All rights reserved.
//

#include "../node/Node.h"

AssignOp AssignOp::create(bool isFirstAssignment, bool isMutable, bool isCopy, CTypeMode typeMode) {
    AssignOp op;
    op.isFirstAssignment = isFirstAssignment;
    op.isMutable = isMutable;
    op.isCopy = isCopy;
    op.typeMode = typeMode;
    return op;
}

AssignOp AssignOp::immutableCreate = AssignOp::create(true, false, false, CTM_Undefined);
AssignOp AssignOp::mutableCreate = AssignOp::create(true, true, false, CTM_Undefined);
AssignOp AssignOp::mutableUpdate = AssignOp::create(false, true, false, CTM_Undefined);

shared_ptr<CTypes> CType::create(vector<string>& packageNamespace, string valueName, string cname, string defaultValue, string cnameOption, string defaultValueOption) {
    assert(valueName.find("stack ") != 0);
    assert(valueName.find("heap ") != 0);
    assert(valueName.find("local ") != 0);
    assert(valueName.find("#") == string::npos);
    assert(valueName.back() != '?');

    auto stackValueType = make_shared<CType>();
    auto stackOptionType = make_shared<CType>();
    auto localValueType = stackValueType;
    auto localOptionType = stackOptionType;

    stackValueType->isOption = false;
    stackValueType->typeMode = CTM_Value;
    stackValueType->category = CTC_Value;
    stackValueType->packageNamespace = packageNamespace;
    stackValueType->valueName = valueName;
    stackValueType->fullName = valueName;
    stackValueType->cname = cname;
    stackValueType->safeName = valueName;
    stackValueType->_defaultValue = defaultValue;
    stackValueType->stackValueType = stackValueType;
    stackValueType->stackOptionType = stackOptionType;
    stackValueType->localValueType = localValueType;
    stackValueType->localOptionType = localOptionType;

    stackOptionType->isOption = true;
    stackOptionType->typeMode = CTM_Value;
    stackOptionType->category = CTC_Value;
    stackOptionType->packageNamespace = packageNamespace;
    stackOptionType->valueName = valueName;
    stackOptionType->fullName = valueName + "?";
    stackOptionType->cname = cnameOption;
    stackOptionType->safeName = valueName + "_option";
    stackOptionType->_defaultValue = defaultValueOption;
    stackOptionType->stackValueType = stackValueType;
    stackOptionType->stackOptionType = stackOptionType;
    stackOptionType->localValueType = localValueType;
    stackOptionType->localOptionType = localOptionType;

    return make_shared<CTypes>(stackValueType, stackOptionType, nullptr, nullptr, nullptr, nullptr);
}

shared_ptr<CTypes> CType::create(Compiler* compiler, vector<string>& packageNamespace, string valueName, weak_ptr<CFunction> parent) {
    assert(valueName.find("stack ") != 0);
    assert(valueName.find("heap ") != 0);
    assert(valueName.find("local ") != 0);
    assert(valueName.find("#") == string::npos);
    assert(valueName.size() == 0 || valueName.back() != '?');

    auto key = parent.lock()->getCStructName(CTM_Stack);
    auto types = compiler->types[key];
    if (types) {
        return types;
    }

    auto stackValueType = make_shared<CType>();
    auto stackOptionType = make_shared<CType>();
    auto heapValueType = make_shared<CType>();
    auto heapOptionType = make_shared<CType>();
    auto localValueType = make_shared<CType>();
    auto localOptionType = make_shared<CType>();

    stackValueType->isOption = false;
    stackValueType->typeMode = CTM_Stack;
    stackValueType->category = CTC_Value;
    stackValueType->parent = parent;
    stackValueType->packageNamespace = packageNamespace;
    stackValueType->valueName = valueName;
    stackValueType->fullName = "stack " + valueName;
    stackValueType->cname = parent.lock()->getCStructName(CTM_Stack);
    stackValueType->safeName = valueName;
    stackValueType->heapValueType = heapValueType;
    stackValueType->heapOptionType = heapOptionType;
    stackValueType->stackValueType = stackValueType;
    stackValueType->stackOptionType = stackOptionType;
    stackValueType->localValueType = localValueType;
    stackValueType->localOptionType = localOptionType;

    stackOptionType->isOption = true;
    stackOptionType->typeMode = CTM_Stack;
    stackOptionType->category = CTC_Value;
    stackOptionType->parent = parent;
    stackOptionType->packageNamespace = packageNamespace;
    stackOptionType->valueName = valueName;
    stackOptionType->fullName = "stack " + valueName + "?";
    stackOptionType->cname = parent.lock()->getCStructName(CTM_Stack);
    stackOptionType->safeName = valueName + "_option";
    stackOptionType->heapValueType = heapValueType;
    stackOptionType->heapOptionType = heapOptionType;
    stackOptionType->stackValueType = stackValueType;
    stackOptionType->stackOptionType = stackOptionType;
    stackOptionType->localValueType = localValueType;
    stackOptionType->localOptionType = localOptionType;

    heapValueType->isOption = false;
    heapValueType->typeMode = CTM_Heap;
    heapValueType->category = CTC_Value;
    heapValueType->parent = parent;
    heapValueType->packageNamespace = packageNamespace;
    heapValueType->valueName = valueName;
    heapValueType->fullName = "heap " + valueName;
    heapValueType->cname = parent.lock()->getCStructName(CTM_Heap) + "*";
    heapValueType->safeName = "heap_" + valueName;
    heapValueType->heapValueType = heapValueType;
    heapValueType->heapOptionType = heapOptionType;
    heapValueType->stackValueType = stackValueType;
    heapValueType->stackOptionType = stackOptionType;
    heapValueType->localValueType = localValueType;
    heapValueType->localOptionType = localOptionType;

    heapOptionType->isOption = true;
    heapOptionType->typeMode = CTM_Heap;
    heapOptionType->category = CTC_Value;
    heapOptionType->parent = parent;
    heapOptionType->packageNamespace = packageNamespace;
    heapOptionType->valueName = valueName;
    heapOptionType->fullName = "heap " + valueName + "?";
    heapOptionType->cname = parent.lock()->getCStructName(CTM_Heap) + "*";
    heapOptionType->safeName = "heap_" + valueName + "_option";
    heapOptionType->heapValueType = heapValueType;
    heapOptionType->heapOptionType = heapOptionType;
    heapOptionType->stackValueType = stackValueType;
    heapOptionType->stackOptionType = stackOptionType;
    heapOptionType->localValueType = localValueType;
    heapOptionType->localOptionType = localOptionType;

    localValueType->isOption = false;
    localValueType->typeMode = CTM_Local;
    localValueType->category = CTC_Value;
    localValueType->parent = parent;
    localValueType->packageNamespace = packageNamespace;
    localValueType->valueName = valueName;
    localValueType->fullName = "local " + valueName;
    localValueType->cname = parent.lock()->getCStructName(CTM_Stack) + "*";
    localValueType->safeName = "local_" + valueName;
    localValueType->heapValueType = heapValueType;
    localValueType->heapOptionType = heapOptionType;
    localValueType->localValueType = localValueType;
    localValueType->localOptionType = localOptionType;
    localValueType->stackValueType = stackValueType;
    localValueType->stackOptionType = stackOptionType;

    localOptionType->isOption = true;
    localOptionType->typeMode = CTM_Local;
    localOptionType->category = CTC_Value;
    localOptionType->parent = parent;
    localOptionType->packageNamespace = packageNamespace;
    localOptionType->valueName = valueName;
    localOptionType->fullName = "local " + valueName + "?";
    localOptionType->cname = parent.lock()->getCStructName(CTM_Stack) + "*";
    localOptionType->safeName = "local_" + valueName + "_option";
    localOptionType->heapValueType = heapValueType;
    localOptionType->heapOptionType = heapOptionType;
    localOptionType->localValueType = localValueType;
    localOptionType->localOptionType = localOptionType;
    localOptionType->stackValueType = stackValueType;
    localOptionType->stackOptionType = stackOptionType;

    compiler->types[key] = make_shared<CTypes>(stackValueType, stackOptionType, heapValueType, heapOptionType, localValueType, localOptionType);
    return compiler->types[key];
}

shared_ptr<CTypes> CType::create(Compiler* compiler, vector<string>& packageNamespace, string valueName, weak_ptr<CInterface> parent) {
    assert(valueName.find("stack ") != 0);
    assert(valueName.find("heap ") != 0);
    assert(valueName.find("local ") != 0);
    assert(valueName.find("#") == string::npos);
    assert(valueName.back() != '?');

    auto key = parent.lock()->getCStructName(CTM_Stack);
    auto types = compiler->types[key];
    if (types) {
        return types;
    }

    auto stackValueType = make_shared<CType>();
    auto heapValueType = make_shared<CType>();
    auto heapOptionType = make_shared<CType>();
    auto localValueType = make_shared<CType>();
    auto localOptionType = make_shared<CType>();

    stackValueType->isOption = false;
    stackValueType->typeMode = CTM_Stack;
    stackValueType->category = CTC_Interface;
    stackValueType->parent = parent;
    stackValueType->packageNamespace = packageNamespace;
    stackValueType->valueName = valueName;
    stackValueType->fullName = "stack #" + valueName;
    stackValueType->cname = parent.lock()->getCStructName(CTM_Stack);
    stackValueType->safeName = valueName;
    stackValueType->heapValueType = heapValueType;
    stackValueType->heapOptionType = heapOptionType;
    stackValueType->stackValueType = stackValueType;
    stackValueType->localValueType = localValueType;
    stackValueType->localOptionType = localOptionType;

    heapValueType->isOption = false;
    heapValueType->typeMode = CTM_Heap;
    heapValueType->category = CTC_Interface;
    heapValueType->parent = parent;
    heapValueType->packageNamespace = packageNamespace;
    heapValueType->valueName = valueName;
    heapValueType->fullName = "heap #" + valueName;
    heapValueType->cname = parent.lock()->getCStructName(CTM_Heap) + "*";
    heapValueType->safeName = "heap_" + valueName;
    heapValueType->heapValueType = heapValueType;
    heapValueType->heapOptionType = heapOptionType;
    heapValueType->stackValueType = stackValueType;
    heapValueType->localValueType = localValueType;
    heapValueType->localOptionType = localOptionType;

    heapOptionType->isOption = true;
    heapOptionType->typeMode = CTM_Heap;
    heapOptionType->category = CTC_Interface;
    heapOptionType->parent = parent;
    heapOptionType->packageNamespace = packageNamespace;
    heapOptionType->valueName = valueName;
    heapOptionType->fullName = "heap #" + valueName + "?";
    heapOptionType->cname = parent.lock()->getCStructName(CTM_Heap) + "*";
    heapOptionType->safeName = "heap_" + valueName + "_option";
    heapOptionType->heapValueType = heapValueType;
    heapOptionType->heapOptionType = heapOptionType;
    heapOptionType->stackValueType = stackValueType;
    heapOptionType->localValueType = localValueType;
    heapOptionType->localOptionType = localOptionType;

    localValueType->isOption = false;
    localValueType->typeMode = CTM_Local;
    localValueType->category = CTC_Interface;
    localValueType->parent = parent;
    localValueType->packageNamespace = packageNamespace;
    localValueType->valueName = valueName;
    localValueType->fullName = "local #" + valueName;
    localValueType->cname = parent.lock()->getCStructName(CTM_Stack) + "*";
    localValueType->safeName = "local_" + valueName;
    localValueType->heapValueType = heapValueType;
    localValueType->heapOptionType = heapOptionType;
    localValueType->stackValueType = stackValueType;
    localValueType->localValueType = localValueType;
    localValueType->localOptionType = localOptionType;

    localOptionType->isOption = true;
    localOptionType->typeMode = CTM_Local;
    localOptionType->category = CTC_Interface;
    localOptionType->parent = parent;
    localOptionType->packageNamespace = packageNamespace;
    localOptionType->valueName = valueName;
    localOptionType->fullName = "local #" + valueName + "?";
    localOptionType->cname = parent.lock()->getCStructName(CTM_Stack) + "*";
    localOptionType->safeName = "local_" + valueName + "_option";
    localOptionType->heapValueType = heapValueType;
    localOptionType->heapOptionType = heapOptionType;
    localOptionType->stackValueType = stackValueType;
    localOptionType->localValueType = localValueType;
    localOptionType->localOptionType = localOptionType;

    compiler->types[key] = make_shared<CTypes>(stackValueType, nullptr, heapValueType, heapOptionType, localValueType, localOptionType);
    return compiler->types[key];
}

shared_ptr<CTypes> CType::create(vector<shared_ptr<CType>> argTypes, shared_ptr<CType> stackReturnType, shared_ptr<CType> heapReturnType, weak_ptr<CCallback> callback) {
    auto stackValueType = make_shared<CType>();
    auto stackOptionType = make_shared<CType>();
    auto heapValueType = make_shared<CType>();
    auto heapOptionType = make_shared<CType>();
    auto localValueType = make_shared<CType>();
    auto localOptionType = make_shared<CType>();

    stringstream valueStream;
    stringstream safeStream;

    safeStream << "cb";
    bool isFirst = true;
    valueStream << "(";
    for (auto argType : argTypes) {
        safeStream << "_";
        if (isFirst) {
            isFirst = false;
        }
        else {
            valueStream << ", ";
        }
        valueStream << ":" << argType->fullName;
        safeStream << argType->safeName;
    }
    valueStream << ")";
    if (stackReturnType) {
        valueStream << stackReturnType->fullName;
    }
    else if (heapReturnType) {
        valueStream << heapReturnType->fullName;
    }
    if (stackReturnType) {
        safeStream << "_";
        safeStream << stackReturnType->safeName;
    }
    if (heapReturnType) {
        safeStream << "_";
        safeStream << heapReturnType->safeName;
    }

    auto valueName = valueStream.str();
    auto safeName = safeStream.str();

    stackValueType->isOption = false;
    stackValueType->typeMode = CTM_Stack;
    stackValueType->category = CTC_Function;
    stackValueType->callback = callback;
    stackValueType->argTypes = argTypes;
    stackValueType->stackReturnType = stackReturnType;
    stackValueType->heapReturnType = heapReturnType;
    stackValueType->valueName = valueName;
    stackValueType->fullName = "stack " + valueName;
    stackValueType->cname = callback.lock()->getCName(CTM_Stack, false);
    stackValueType->safeName = "stack_" + safeName;
    stackValueType->heapValueType = heapValueType;
    stackValueType->heapOptionType = heapOptionType;
    stackValueType->stackValueType = stackValueType;
    stackValueType->stackOptionType = stackOptionType;
    stackValueType->localValueType = localValueType;
    stackValueType->localOptionType = localOptionType;

    stackOptionType->isOption = true;
    stackOptionType->typeMode = CTM_Stack;
    stackOptionType->category = CTC_Function;
    stackOptionType->callback = callback;
    stackOptionType->argTypes = argTypes;
    stackOptionType->stackReturnType = stackReturnType;
    stackOptionType->heapReturnType = heapReturnType;
    stackOptionType->valueName = valueName;
    stackOptionType->fullName = "stack " + valueName + "?";
    stackOptionType->cname = callback.lock()->getCName(CTM_Stack, true);
    stackOptionType->safeName = "stack_" + safeName + "_option";
    stackOptionType->heapValueType = heapValueType;
    stackOptionType->heapOptionType = heapOptionType;
    stackOptionType->stackValueType = stackValueType;
    stackOptionType->stackOptionType = stackOptionType;
    stackOptionType->localValueType = localValueType;
    stackOptionType->localOptionType = localOptionType;

    heapValueType->isOption = false;
    heapValueType->typeMode = CTM_Heap;
    heapValueType->category = CTC_Function;
    heapValueType->callback = callback;
    heapValueType->argTypes = argTypes;
    heapValueType->stackReturnType = stackReturnType;
    heapValueType->heapReturnType = heapReturnType;
    heapValueType->valueName = valueName;
    heapValueType->fullName = "heap " + valueName;
    heapValueType->cname = callback.lock()->getCName(CTM_Heap, false);
    heapValueType->safeName = "heap_" + safeName;
    heapValueType->heapValueType = heapValueType;
    heapValueType->heapOptionType = heapOptionType;
    heapValueType->stackValueType = stackValueType;
    heapValueType->stackOptionType = stackOptionType;
    heapValueType->localValueType = localValueType;
    heapValueType->localOptionType = localOptionType;

    heapOptionType->isOption = true;
    heapOptionType->typeMode = CTM_Heap;
    heapOptionType->category = CTC_Function;
    heapOptionType->callback = callback;
    heapOptionType->argTypes = argTypes;
    heapOptionType->stackReturnType = stackReturnType;
    heapOptionType->heapReturnType = heapReturnType;
    heapOptionType->valueName = valueName;
    heapOptionType->fullName = "heap " + valueName + "?";
    heapOptionType->cname = callback.lock()->getCName(CTM_Heap, true);
    heapOptionType->safeName = "heap_" + safeName + "_option";
    heapOptionType->heapValueType = heapValueType;
    heapOptionType->heapOptionType = heapOptionType;
    heapOptionType->stackValueType = stackValueType;
    heapOptionType->stackOptionType = stackOptionType;
    heapOptionType->localValueType = localValueType;
    heapOptionType->localOptionType = localOptionType;

    localValueType->isOption = false;
    localValueType->typeMode = CTM_Local;
    localValueType->category = CTC_Function;
    localValueType->callback = callback;
    localValueType->argTypes = argTypes;
    localValueType->stackReturnType = stackReturnType;
    localValueType->heapReturnType = heapReturnType;
    localValueType->valueName = valueName;
    localValueType->fullName = "local " + valueName;
    localValueType->cname = callback.lock()->getCName(CTM_Local, false);
    localValueType->safeName = "local_" + safeName;
    localValueType->heapValueType = heapValueType;
    localValueType->heapOptionType = heapOptionType;
    localValueType->stackValueType = stackValueType;
    localValueType->stackOptionType = stackOptionType;
    localValueType->localValueType = localValueType;
    localValueType->localOptionType = localOptionType;

    localOptionType->isOption = true;
    localOptionType->typeMode = CTM_Local;
    localOptionType->category = CTC_Function;
    localOptionType->callback = callback;
    localOptionType->argTypes = argTypes;
    localOptionType->stackReturnType = stackReturnType;
    localOptionType->heapReturnType = heapReturnType;
    localOptionType->valueName = valueName;
    localOptionType->fullName = "local " + valueName + "?";
    localOptionType->cname = callback.lock()->getCName(CTM_Local, true);
    localOptionType->safeName = "local_" + safeName + "_option";
    localOptionType->heapValueType = heapValueType;
    localOptionType->heapOptionType = heapOptionType;
    localOptionType->stackValueType = stackValueType;
    localOptionType->stackOptionType = stackOptionType;
    localOptionType->localValueType = localValueType;
    localOptionType->localOptionType = localOptionType;

    return make_shared<CTypes>(stackValueType, stackOptionType, heapValueType, heapOptionType, localValueType, localOptionType);
}

void CType::transpileDefaultValue(Compiler* compiler, CLoc loc, TrBlock* trBlock, shared_ptr<TrStoreValue> storeValue) {
    if (category == CTC_Value && parent.expired()) {
        auto temp = make_shared<TrValue>(nullptr, shared_from_this(), _defaultValue, false);
        storeValue->retainValue(compiler, loc, trBlock, temp);
    }
    else if (isOption) {
        if (!parent.expired()) {
            if (storeValue->type->typeMode == CTM_Stack) {
                if (storeValue->isReturnValue) {
                    trBlock->statements.push_back(TrStatement(loc, storeValue->getName(trBlock) + "->_refCount = -1"));
                }
                else {
                    trBlock->statements.push_back(TrStatement(loc, storeValue->getName(trBlock) + "._refCount = -1"));
                }
                storeValue->hasSetValue = true;
            }
            else {
                auto temp = make_shared<TrValue>(nullptr, storeValue->type, "0", false);
                storeValue->retainValue(compiler, loc, trBlock, temp);
            }
        }
        else if (category == CTC_Function) {
            trBlock->statements.push_back(TrStatement(loc, storeValue->getName(trBlock) + "._parent = 0"));
            storeValue->hasSetValue = true;
        }
    }
    else {
        compiler->addError(loc, CErrorCode::InvalidType, "no default value for type '%s'", valueName.c_str());
    }
}

bool CType::isSameExceptMode(shared_ptr<CType> l, shared_ptr<CType> r) {
    return l->category == r->category && l->stackValueType.lock()->cname == r->stackValueType.lock()->cname && l->isOption == r->isOption;
}


shared_ptr<CType> CType::getValueType() {
    assert(isOption);
    return (heapOptionType.lock().get() == this) ? heapValueType.lock() : ((stackOptionType.lock().get() == this) ? stackValueType.lock() : localValueType.lock());
}

shared_ptr<CType> CType::getOptionType() {
    assert(!isOption);
    return (heapValueType.lock().get() == this) ? heapOptionType.lock() : ((stackValueType.lock().get() == this) ? stackOptionType.lock() : localOptionType.lock());
}

shared_ptr<CType> CType::getHeapType() {
    return isOption ? heapOptionType.lock() : heapValueType.lock();
}

shared_ptr<CType> CType::getHeapValueType() {
    assert(heapValueType.lock().get() != this);
    return heapValueType.lock();
}

shared_ptr<CType> CType::getHeapOptionType() {
    assert(heapOptionType.lock().get() != this);
    return heapOptionType.lock();
}

shared_ptr<CType> CType::getStackType() {
    return isOption ? stackOptionType.lock() : stackValueType.lock();
}

shared_ptr<CType> CType::getStackValueType() {
    assert(stackValueType.lock().get() != this);
    return stackValueType.lock();
}

shared_ptr<CType> CType::getLocalType() {
    return isOption ? localOptionType.lock() : localValueType.lock();
}

shared_ptr<CType> CType::getLocalValueType() {
    return localValueType.lock();
}

shared_ptr<CType> CType::getLocalOptionType() {
    return localOptionType.lock();
}
