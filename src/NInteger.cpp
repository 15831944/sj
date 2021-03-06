#include <sjc.h>

NInteger::NInteger(CLoc loc, const char* value_) : NVariableBase(NodeType_Integer, loc), strValue(value_), hasValue(false), strBase(10) {
    if (strValue.size() > 2 && strValue[0] == '0' && strValue[1] == 'x') {
        strBase = 16;
        strValue = strValue.substr(2, strValue.size() - 2);
    }

    if (strValue.back() == 'i') {
        type = NIT_I32;
        strValue = strValue.substr(0, strValue.size() - 1);
    }
    else if (strValue.back() == 'u') {
        type = NIT_U32;
        strValue = strValue.substr(0, strValue.size() - 1);
    }
    else if (strValue.back() == 'v') {
        type = NIT_U64;
        strValue = strValue.substr(0, strValue.size() - 1);
    }
    else if (strValue.back() == 'l') {
        type = NIT_I64;
        strValue = strValue.substr(0, strValue.size() - 1);
    }
    else {
        type = NIT_I32;
    }
}

NInteger::NInteger(CLoc loc, const char* value_, shared_ptr<CType> overrideType) : NVariableBase(NodeType_Integer, loc), strValue(value_), hasValue(false), strBase(10), overrideType(overrideType) {
    type = NIT_I32;
}

shared_ptr<CVar> NInteger::getVarImpl(Compiler* compiler, shared_ptr<CScope> scope, shared_ptr<CVar> dotVar, shared_ptr<CType> returnType, CTypeMode returnMode) {
    if (strValue.size() > 0) {
        if (type == NIT_I32) {
            char* e;
            errno = 0;
            auto v = strtol(strValue.c_str(), &e, strBase);
            if (ERANGE == errno || v < INT32_MIN || v > INT32_MAX) {
                compiler->addError(loc, CErrorCode::InvalidNumber, "i32 '%s' is out range", strValue.c_str());
                return nullptr;
            }

            if (*e != '\0') {
                compiler->addError(loc, CErrorCode::InvalidNumber, "not a valid i32 '%s'", strValue.c_str());
                return nullptr;
            }

            stringstream line;
            if (v == INT32_MIN) {
                line << "(" << v + 1 << " - 1)";
            }
            else {
                line << v;
            }

            if (overrideType) {
                return make_shared<CConstantVar>(loc, scope, overrideType, line.str());
            }
            else {
                return make_shared<CConstantVar>(loc, scope, compiler->typeI32, line.str());
            }
        }
        else if (type == NIT_U32) {
            char* e;
            errno = 0;
            auto v = strtoul(strValue.c_str(), &e, strBase);
            if (ERANGE == errno || v > UINT32_MAX) {
                compiler->addError(loc, CErrorCode::InvalidNumber, "u32 '%s' is out range", strValue.c_str());
                return nullptr;
            }

            if (*e != '\0') {
                compiler->addError(loc, CErrorCode::InvalidNumber, "not a valid u32 '%s'", strValue.c_str());
                return nullptr;
            }

            stringstream line;
            line << v << "u";
            return make_shared<CConstantVar>(loc, scope, compiler->typeU32, "(uint32_t)" + line.str());
        }
        else if (type == NIT_I64) {
            char* e;
            errno = 0;
            auto v = strtoll(strValue.c_str(), &e, strBase);
            if (ERANGE == errno) {
                compiler->addError(loc, CErrorCode::InvalidNumber, "i64 '%s' is out range", strValue.c_str());
                return nullptr;
            }

            if (*e != '\0') {
                compiler->addError(loc, CErrorCode::InvalidNumber, "not a valid i64 '%s'", strValue.c_str());
                return nullptr;
            }

            stringstream line;
            if (v == INT64_MIN) {
                line << "(" << v + 1 << "ll" << " - 1ll)";
            }
            else {
                line << v << "ll";
            }
            return make_shared<CConstantVar>(loc, scope, compiler->typeI64, line.str());
        }
        else if (type == NIT_U64) {
            char* e;
            errno = 0;
            auto v = strtoull(strValue.c_str(), &e, strBase);
            if (ERANGE == errno) {
                compiler->addError(loc, CErrorCode::InvalidNumber, "u64 '%s' is out range", strValue.c_str());
                return nullptr;
            }

            if (*e != '\0') {
                compiler->addError(loc, CErrorCode::InvalidNumber, "not a valid u64 '%s'", strValue.c_str());
                return nullptr;
            }

            stringstream line;
            line << v << "ull";
            return make_shared<CConstantVar>(loc, scope, compiler->typeU64, line.str());
        }
        else {
            assert(false);
            return nullptr;
        }
    } else if (hasValue) {
        stringstream line;
        line << value;
        return make_shared<CConstantVar>(loc, scope, compiler->typeI32, line.str());
    }
    return nullptr;
}

