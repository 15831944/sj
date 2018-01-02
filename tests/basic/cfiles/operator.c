#include <lib/common/common.h>

#define sjs_hash_type_bool_typeId 15
#define sjs_log_typeId 20
#define sjs_fancymath_typeId 21

typedef struct td_sjs_hash_type_bool sjs_hash_type_bool;
typedef struct td_sjs_log sjs_log;
typedef struct td_sjs_fancymath sjs_fancymath;

struct td_sjs_hash_type_bool {
    int _refCount;
    void* _hash;
};

struct td_sjs_log {
    int _refCount;
    int32_t minlevel;
    sjs_hash_type_bool traceincludes;
    sjs_hash_type_bool debugincludes;
    sjs_hash_type_bool infoincludes;
    sjs_hash_type_bool warnincludes;
    sjs_hash_type_bool errorincludes;
    sjs_hash_type_bool fatalincludes;
};

struct td_sjs_fancymath {
    int _refCount;
    int32_t x;
};

#ifndef type_bool_hash_typedef
#define type_bool_hash_typedef
KHASH_INIT_TYPEDEF(type_bool_hash_type, int32_t, bool)
#endif
#ifndef type_bool_hash_typedef
#define type_bool_hash_typedef
KHASH_INIT_TYPEDEF(type_bool_hash_type, int32_t, bool)
#endif
int32_t g_loglevel_debug;
int32_t g_loglevel_error;
int32_t g_loglevel_fatal;
int32_t g_loglevel_info;
int32_t g_loglevel_trace;
int32_t g_loglevel_warn;

sjs_fancymath g_a = { -1 };
sjs_fancymath g_b = { -1 };
sjs_fancymath g_c = { -1 };
int32_t g_clocks_per_sec;
sjs_fancymath g_d = { -1 };
sjs_fancymath g_e = { -1 };
void* g_emptystringdata;
sjs_fancymath g_f = { -1 };
float g_f32_pi;
sjs_fancymath g_g = { -1 };
int32_t g_i;
int32_t g_i32_maxvalue;
int32_t g_i32_minvalue;
int32_t g_ii;
int32_t g_j;
sjs_fancymath g_k = { -1 };
sjs_log g_log = { -1 };
sjs_hash_type_bool g_log_excludeall = { -1 };
sjs_hash_type_bool g_log_includeall = { -1 };
uint32_t g_u32_maxvalue;
int32_t result1;
sjs_fancymath sjt_funcold1 = { -1 };
sjs_fancymath sjt_funcold2 = { -1 };
sjs_fancymath sjt_funcold3 = { -1 };
sjs_fancymath sjt_funcold4 = { -1 };
sjs_fancymath sjt_funcold5 = { -1 };
sjs_fancymath sjt_funcold6 = { -1 };
sjs_fancymath* sjt_functionParam1 = 0;
int32_t sjt_functionParam10;
int32_t sjt_functionParam11;
sjs_fancymath* sjt_functionParam2 = 0;
sjs_fancymath* sjt_functionParam3 = 0;
sjs_fancymath* sjt_functionParam4 = 0;
sjs_fancymath* sjt_functionParam5 = 0;
sjs_fancymath* sjt_functionParam6 = 0;
sjs_fancymath* sjt_functionParam7 = 0;
sjs_fancymath* sjt_functionParam8 = 0;
sjs_fancymath* sjt_functionParam9 = 0;
sjs_fancymath* sjt_parent12 = 0;
sjs_fancymath* sjt_parent15 = 0;
sjs_fancymath* sjt_parent16 = 0;
sjs_fancymath* sjt_parent17 = 0;
sjs_fancymath* sjt_parent18 = 0;
sjs_fancymath* sjt_parent19 = 0;
sjs_fancymath* sjt_parent20 = 0;
sjs_fancymath* sjt_parent21 = 0;
sjs_fancymath* sjt_parent22 = 0;
sjs_fancymath* sjt_parent23 = 0;
sjs_fancymath* sjt_parent24 = 0;
sjs_fancymath* sjt_parent3 = 0;
sjs_fancymath* sjt_parent6 = 0;
sjs_fancymath* sjt_parent9 = 0;
sjs_hash_type_bool sjt_value1 = { -1 };

void sjf_fancymath(sjs_fancymath* _this);
void sjf_fancymath_add(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return);
void sjf_fancymath_add_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return);
void sjf_fancymath_copy(sjs_fancymath* _this, sjs_fancymath* _from);
void sjf_fancymath_destroy(sjs_fancymath* _this);
void sjf_fancymath_divide(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return);
void sjf_fancymath_divide_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return);
void sjf_fancymath_dividei32(sjs_fancymath* _parent, int32_t num, sjs_fancymath* _return);
void sjf_fancymath_dividei32_heap(sjs_fancymath* _parent, int32_t num, sjs_fancymath** _return);
void sjf_fancymath_getx(sjs_fancymath* _parent, int32_t* _return);
void sjf_fancymath_heap(sjs_fancymath* _this);
void sjf_fancymath_increment(sjs_fancymath* _parent, sjs_fancymath* _return);
void sjf_fancymath_increment_heap(sjs_fancymath* _parent, sjs_fancymath** _return);
void sjf_fancymath_modulus(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return);
void sjf_fancymath_modulus_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return);
void sjf_fancymath_multiply(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return);
void sjf_fancymath_multiply_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return);
void sjf_fancymath_setbob(sjs_fancymath* _parent, int32_t i, int32_t* _return);
void sjf_fancymath_subtract(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return);
void sjf_fancymath_subtract_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return);
void sjf_hash_type_bool(sjs_hash_type_bool* _this);
void sjf_hash_type_bool__weakptrremovekey(sjs_hash_type_bool* _parent, int32_t key);
void sjf_hash_type_bool__weakptrremovevalue(sjs_hash_type_bool* _parent, bool val);
void sjf_hash_type_bool_copy(sjs_hash_type_bool* _this, sjs_hash_type_bool* _from);
void sjf_hash_type_bool_destroy(sjs_hash_type_bool* _this);
void sjf_hash_type_bool_heap(sjs_hash_type_bool* _this);
void sjf_log(sjs_log* _this);
void sjf_log_copy(sjs_log* _this, sjs_log* _from);
void sjf_log_destroy(sjs_log* _this);
void sjf_log_heap(sjs_log* _this);
void sjf_type_hash(int32_t val, uint32_t* _return);
void sjf_type_isequal(int32_t l, int32_t r, bool* _return);
void main_destroy(void);

#ifndef type_bool_hash_function
#define type_bool_hash_function
#if false
KHASH_INIT_FUNCTION_DEREF(type_bool_hash_type, int32_t, bool, 1, sjf_type_hash, sjf_type_isequal)
#else
KHASH_INIT_FUNCTION(type_bool_hash_type, int32_t, bool, 1, sjf_type_hash, sjf_type_isequal)
#endif
#endif
#ifndef type_bool_hash_function
#define type_bool_hash_function
#if false
KHASH_INIT_FUNCTION_DEREF(type_bool_hash_type, int32_t, bool, 1, sjf_type_hash, sjf_type_isequal)
#else
KHASH_INIT_FUNCTION(type_bool_hash_type, int32_t, bool, 1, sjf_type_hash, sjf_type_isequal)
#endif
#endif
#include <lib/common/common.c>
void sjf_fancymath(sjs_fancymath* _this) {
}

void sjf_fancymath_add(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return) {
    int32_t sjt_capture1;
    sjs_fancymath* sjt_parent1 = 0;

    _return->_refCount = 1;
#line 4 "operator.sj"
    sjt_parent1 = num;
#line 4
    sjf_fancymath_getx(sjt_parent1, &sjt_capture1);
#line 5
    _return->x = (_parent->x + sjt_capture1) + 1;
#line 5
    sjf_fancymath(_return);
}

void sjf_fancymath_add_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture2;
    sjs_fancymath* sjt_parent2 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 4 "operator.sj"
    sjt_parent2 = num;
#line 4
    sjf_fancymath_getx(sjt_parent2, &sjt_capture2);
#line 5
    (*_return)->x = (_parent->x + sjt_capture2) + 1;
#line 5
    sjf_fancymath_heap((*_return));
}

void sjf_fancymath_copy(sjs_fancymath* _this, sjs_fancymath* _from) {
#line 1 "operator.sj"
    _this->x = _from->x;
}

void sjf_fancymath_destroy(sjs_fancymath* _this) {
}

void sjf_fancymath_divide(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return) {
    int32_t sjt_capture7;
    sjs_fancymath* sjt_parent10 = 0;

    _return->_refCount = 1;
#line 16 "operator.sj"
    sjt_parent10 = num;
#line 16
    sjf_fancymath_getx(sjt_parent10, &sjt_capture7);
#line 17
    _return->x = (_parent->x / sjt_capture7) + 1;
#line 17
    sjf_fancymath(_return);
}

void sjf_fancymath_divide_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture8;
    sjs_fancymath* sjt_parent11 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 16 "operator.sj"
    sjt_parent11 = num;
#line 16
    sjf_fancymath_getx(sjt_parent11, &sjt_capture8);
#line 17
    (*_return)->x = (_parent->x / sjt_capture8) + 1;
#line 17
    sjf_fancymath_heap((*_return));
}

void sjf_fancymath_dividei32(sjs_fancymath* _parent, int32_t num, sjs_fancymath* _return) {
    _return->_refCount = 1;
#line 21 "operator.sj"
    _return->x = (_parent->x / num) + 1;
#line 21
    sjf_fancymath(_return);
}

void sjf_fancymath_dividei32_heap(sjs_fancymath* _parent, int32_t num, sjs_fancymath** _return) {
    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 21 "operator.sj"
    (*_return)->x = (_parent->x / num) + 1;
#line 21
    sjf_fancymath_heap((*_return));
}

void sjf_fancymath_getx(sjs_fancymath* _parent, int32_t* _return) {
#line 36 "operator.sj"
    (*_return) = _parent->x;
}

void sjf_fancymath_heap(sjs_fancymath* _this) {
}

void sjf_fancymath_increment(sjs_fancymath* _parent, sjs_fancymath* _return) {
    _return->_refCount = 1;
#line 29 "operator.sj"
    _return->x = _parent->x + 1;
#line 29
    sjf_fancymath(_return);
}

void sjf_fancymath_increment_heap(sjs_fancymath* _parent, sjs_fancymath** _return) {
    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 29 "operator.sj"
    (*_return)->x = _parent->x + 1;
#line 29
    sjf_fancymath_heap((*_return));
}

void sjf_fancymath_modulus(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return) {
    int32_t sjt_capture9;
    sjs_fancymath* sjt_parent13 = 0;

    _return->_refCount = 1;
#line 24 "operator.sj"
    sjt_parent13 = num;
#line 24
    sjf_fancymath_getx(sjt_parent13, &sjt_capture9);
#line 25
    _return->x = (_parent->x % sjt_capture9) + 1;
#line 25
    sjf_fancymath(_return);
}

void sjf_fancymath_modulus_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture10;
    sjs_fancymath* sjt_parent14 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 24 "operator.sj"
    sjt_parent14 = num;
#line 24
    sjf_fancymath_getx(sjt_parent14, &sjt_capture10);
#line 25
    (*_return)->x = (_parent->x % sjt_capture10) + 1;
#line 25
    sjf_fancymath_heap((*_return));
}

void sjf_fancymath_multiply(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return) {
    int32_t sjt_capture5;
    sjs_fancymath* sjt_parent7 = 0;

    _return->_refCount = 1;
#line 12 "operator.sj"
    sjt_parent7 = num;
#line 12
    sjf_fancymath_getx(sjt_parent7, &sjt_capture5);
#line 13
    _return->x = (_parent->x * sjt_capture5) + 1;
#line 13
    sjf_fancymath(_return);
}

void sjf_fancymath_multiply_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture6;
    sjs_fancymath* sjt_parent8 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 12 "operator.sj"
    sjt_parent8 = num;
#line 12
    sjf_fancymath_getx(sjt_parent8, &sjt_capture6);
#line 13
    (*_return)->x = (_parent->x * sjt_capture6) + 1;
#line 13
    sjf_fancymath_heap((*_return));
}

void sjf_fancymath_setbob(sjs_fancymath* _parent, int32_t i, int32_t* _return) {
#line 40 "operator.sj"
    _parent->x = i;
#line 41
    (*_return) = _parent->x;
}

void sjf_fancymath_subtract(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return) {
    int32_t sjt_capture3;
    sjs_fancymath* sjt_parent4 = 0;

    _return->_refCount = 1;
#line 8 "operator.sj"
    sjt_parent4 = num;
#line 8
    sjf_fancymath_getx(sjt_parent4, &sjt_capture3);
#line 9
    _return->x = (_parent->x - sjt_capture3) + 1;
#line 9
    sjf_fancymath(_return);
}

void sjf_fancymath_subtract_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture4;
    sjs_fancymath* sjt_parent5 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 8 "operator.sj"
    sjt_parent5 = num;
#line 8
    sjf_fancymath_getx(sjt_parent5, &sjt_capture4);
#line 9
    (*_return)->x = (_parent->x - sjt_capture4) + 1;
#line 9
    sjf_fancymath_heap((*_return));
}

void sjf_hash_type_bool(sjs_hash_type_bool* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(type_bool_hash_type);
}

void sjf_hash_type_bool__weakptrremovekey(sjs_hash_type_bool* _parent, int32_t key) {
#line 180 "lib/common/hash.sj"
    #if false
#line 181
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_parent->_hash;    
#line 182
    khiter_t k = kh_get(type_bool_hash_type, p, key);
#line 183
    if (k != kh_end(p)) {
#line 184
        kh_del(type_bool_hash_type, p, k);
#line 185
    }
#line 186
    #endif
}

void sjf_hash_type_bool__weakptrremovevalue(sjs_hash_type_bool* _parent, bool val) {
#line 192 "lib/common/hash.sj"
    #if false
#line 193
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_parent->_hash;
#line 194
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 195
        if (kh_exist(p, k)) {
#line 196
            bool t = kh_value(p, k);
#line 197
            if (t == val) {
#line 198
                kh_del(type_bool_hash_type, p, k);
#line 199
            }
#line 200
        }
#line 201
    }
#line 202
    #endif
}

void sjf_hash_type_bool_copy(sjs_hash_type_bool* _this, sjs_hash_type_bool* _from) {
#line 230 "lib/common/hash.sj"
    _this->_hash = _from->_hash;
#line 231
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_this->_hash;
#line 232
    p->refcount++;
}

void sjf_hash_type_bool_destroy(sjs_hash_type_bool* _this) {
#line 236 "lib/common/hash.sj"
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_this->_hash;
#line 237
    p->refcount--;
#line 238
    if (p->refcount == 0) {
#line 239
        for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 240
            if (kh_exist(p, k)) {
#line 242
                #if false
#line 243
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_type_bool__weakptrremovekey };
#line 244
                weakptr_cb_remove(kh_key(p, k), cb);
#line 245
                #else
#line 246
                ;
#line 247
                #endif
#line 249
                #if false
#line 250
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_type_bool__weakptrremovevalue };
#line 251
                weakptr_cb_remove(kh_value(p, k), cb);
#line 252
                #else
#line 253
                ;
#line 254
                #endif
#line 255
            }
#line 256
        }
#line 257
        kh_destroy(type_bool_hash_type, _this->_hash);
#line 258
    }
}

void sjf_hash_type_bool_heap(sjs_hash_type_bool* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(type_bool_hash_type);
}

void sjf_log(sjs_log* _this) {
}

void sjf_log_copy(sjs_log* _this, sjs_log* _from) {
#line 13 "lib/common/log.sj"
    _this->minlevel = _from->minlevel;
#line 13
    sjs_hash_type_bool* copyoption2 = (_from->traceincludes._refCount != -1 ? &_from->traceincludes : 0);
    if (copyoption2 != 0) {
        _this->traceincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->traceincludes, copyoption2);
    } else {
        _this->traceincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption3 = (_from->debugincludes._refCount != -1 ? &_from->debugincludes : 0);
    if (copyoption3 != 0) {
        _this->debugincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->debugincludes, copyoption3);
    } else {
        _this->debugincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption4 = (_from->infoincludes._refCount != -1 ? &_from->infoincludes : 0);
    if (copyoption4 != 0) {
        _this->infoincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->infoincludes, copyoption4);
    } else {
        _this->infoincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption5 = (_from->warnincludes._refCount != -1 ? &_from->warnincludes : 0);
    if (copyoption5 != 0) {
        _this->warnincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->warnincludes, copyoption5);
    } else {
        _this->warnincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption6 = (_from->errorincludes._refCount != -1 ? &_from->errorincludes : 0);
    if (copyoption6 != 0) {
        _this->errorincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->errorincludes, copyoption6);
    } else {
        _this->errorincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption7 = (_from->fatalincludes._refCount != -1 ? &_from->fatalincludes : 0);
    if (copyoption7 != 0) {
        _this->fatalincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&_this->fatalincludes, copyoption7);
    } else {
        _this->fatalincludes._refCount = -1;
    }
}

void sjf_log_destroy(sjs_log* _this) {
    if (_this->traceincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->traceincludes); }
;
    if (_this->debugincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->debugincludes); }
;
    if (_this->infoincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->infoincludes); }
;
    if (_this->warnincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->warnincludes); }
;
    if (_this->errorincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->errorincludes); }
;
    if (_this->fatalincludes._refCount == 1) { sjf_hash_type_bool_destroy(&_this->fatalincludes); }
;
}

void sjf_log_heap(sjs_log* _this) {
}

void sjf_type_hash(int32_t val, uint32_t* _return) {
    int32_t sjt_cast1;

#line 5 "lib/common/type.sj"
    sjt_cast1 = val;
#line 6
    (*_return) = (uint32_t)sjt_cast1;
}

void sjf_type_isequal(int32_t l, int32_t r, bool* _return) {
#line 10 "lib/common/type.sj"
    (*_return) = l == r;
}

int main(int argc, char** argv) {
#line 1 "lib/common/log.sj"
    g_loglevel_trace = 0;
#line 1
    g_loglevel_debug = 1;
#line 1
    g_loglevel_info = 2;
#line 1
    g_loglevel_warn = 3;
#line 1
    g_loglevel_error = 4;
#line 1
    g_loglevel_fatal = 5;
#line 1 "lib/common/f32.sj"
    g_f32_pi = 3.14159265358979323846f;
#line 1 "lib/common/i32.sj"
    g_u32_maxvalue = (uint32_t)4294967295u;
#line 3
    result1 = -1;
#line 3
    g_i32_maxvalue = result1 - 2147483647;
#line 4
    g_i32_minvalue = 2147483647;
#line 10 "lib/common/log.sj"
    g_log_includeall._refCount = -1;
#line 10
    sjt_value1._refCount = 1;
#line 10
    sjf_hash_type_bool(&sjt_value1);
#line 11
    sjs_hash_type_bool* copyoption1 = &sjt_value1;
    if (copyoption1 != 0) {
        g_log_excludeall._refCount = 1;
#line 11 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log_excludeall, copyoption1);
    } else {
        g_log_excludeall._refCount = -1;
    }

#line 11
    g_log._refCount = 1;
#line 13
    g_log.minlevel = g_loglevel_warn;
#line 13
    sjs_hash_type_bool* copyoption8 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption8 != 0) {
        g_log.traceincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.traceincludes, copyoption8);
    } else {
        g_log.traceincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption9 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption9 != 0) {
        g_log.debugincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.debugincludes, copyoption9);
    } else {
        g_log.debugincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption10 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption10 != 0) {
        g_log.infoincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.infoincludes, copyoption10);
    } else {
        g_log.infoincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption11 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption11 != 0) {
        g_log.warnincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.warnincludes, copyoption11);
    } else {
        g_log.warnincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption12 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption12 != 0) {
        g_log.errorincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.errorincludes, copyoption12);
    } else {
        g_log.errorincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption13 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption13 != 0) {
        g_log.fatalincludes._refCount = 1;
#line 13 "lib/common/log.sj"
        sjf_hash_type_bool_copy(&g_log.fatalincludes, copyoption13);
    } else {
        g_log.fatalincludes._refCount = -1;
    }

#line 13
    sjf_log(&g_log);
#line 1 "lib/common/string.sj"
    g_emptystringdata = 0;
#line 3
    g_emptystringdata = "";
#line 2 "lib/common/weakptr.sj"
    ptr_init();
#line 3
    weakptr_init();
#line 7 "lib/common/clock.sj"
    g_clocks_per_sec = 0;
#line 9
    g_clocks_per_sec = CLOCKS_PER_SEC;
#line 9
    g_a._refCount = 1;
#line 45 "operator.sj"
    g_a.x = 1;
#line 45
    sjf_fancymath(&g_a);
#line 45
    g_b._refCount = 1;
#line 46
    g_b.x = 2;
#line 46
    sjf_fancymath(&g_b);
#line 47
    g_ii = 2;
#line 4
    sjt_parent3 = &g_a;
#line 48
    sjt_functionParam1 = &g_b;
#line 48
    sjf_fancymath_add(sjt_parent3, sjt_functionParam1, &g_c);
#line 8
    sjt_parent6 = &g_a;
#line 49
    sjt_functionParam2 = &g_b;
#line 49
    sjf_fancymath_subtract(sjt_parent6, sjt_functionParam2, &g_d);
#line 12
    sjt_parent9 = &g_a;
#line 50
    sjt_functionParam3 = &g_b;
#line 50
    sjf_fancymath_multiply(sjt_parent9, sjt_functionParam3, &g_e);
#line 16
    sjt_parent12 = &g_a;
#line 51
    sjt_functionParam4 = &g_b;
#line 51
    sjf_fancymath_divide(sjt_parent12, sjt_functionParam4, &g_f);
#line 24
    sjt_parent15 = &g_a;
#line 52
    sjt_functionParam5 = &g_b;
#line 52
    sjf_fancymath_modulus(sjt_parent15, sjt_functionParam5, &g_g);
#line 52
    sjt_funcold1._refCount = 1;
#line 4
    sjf_fancymath_copy(&sjt_funcold1, &g_c);
#line 4
    sjt_parent16 = &g_c;
#line 53
    sjt_functionParam6 = &g_c;
#line 53
    sjf_fancymath_add(sjt_parent16, sjt_functionParam6, &sjt_funcold1);
#line 53
    if (g_c._refCount == 1) { sjf_fancymath_destroy(&g_c); }
;
#line 4
    sjf_fancymath_copy(&g_c, &sjt_funcold1);
#line 4
    sjt_funcold2._refCount = 1;
#line 8
    sjf_fancymath_copy(&sjt_funcold2, &g_d);
#line 8
    sjt_parent17 = &g_d;
#line 54
    sjt_functionParam7 = &g_d;
#line 54
    sjf_fancymath_subtract(sjt_parent17, sjt_functionParam7, &sjt_funcold2);
#line 54
    if (g_d._refCount == 1) { sjf_fancymath_destroy(&g_d); }
;
#line 8
    sjf_fancymath_copy(&g_d, &sjt_funcold2);
#line 8
    sjt_funcold3._refCount = 1;
#line 12
    sjf_fancymath_copy(&sjt_funcold3, &g_d);
#line 12
    sjt_parent18 = &g_d;
#line 55
    sjt_functionParam8 = &g_d;
#line 55
    sjf_fancymath_multiply(sjt_parent18, sjt_functionParam8, &sjt_funcold3);
#line 55
    if (g_d._refCount == 1) { sjf_fancymath_destroy(&g_d); }
;
#line 12
    sjf_fancymath_copy(&g_d, &sjt_funcold3);
#line 12
    sjt_funcold4._refCount = 1;
#line 16
    sjf_fancymath_copy(&sjt_funcold4, &g_d);
#line 16
    sjt_parent19 = &g_d;
#line 56
    sjt_functionParam9 = &g_d;
#line 56
    sjf_fancymath_divide(sjt_parent19, sjt_functionParam9, &sjt_funcold4);
#line 56
    if (g_d._refCount == 1) { sjf_fancymath_destroy(&g_d); }
;
#line 16
    sjf_fancymath_copy(&g_d, &sjt_funcold4);
#line 16
    sjt_funcold5._refCount = 1;
#line 28
    sjf_fancymath_copy(&sjt_funcold5, &g_e);
#line 28
    sjt_parent20 = &g_e;
#line 28
    sjf_fancymath_increment(sjt_parent20, &sjt_funcold5);
#line 28
    if (g_e._refCount == 1) { sjf_fancymath_destroy(&g_e); }
;
#line 28
    sjf_fancymath_copy(&g_e, &sjt_funcold5);
#line 28
    sjt_funcold6._refCount = 1;
#line 28
    sjf_fancymath_copy(&sjt_funcold6, &g_f);
#line 28
    sjt_parent21 = &g_f;
#line 28
    sjf_fancymath_increment(sjt_parent21, &sjt_funcold6);
#line 28
    if (g_f._refCount == 1) { sjf_fancymath_destroy(&g_f); }
;
#line 28
    sjf_fancymath_copy(&g_f, &sjt_funcold6);
#line 36
    sjt_parent22 = &g_f;
#line 36
    sjf_fancymath_getx(sjt_parent22, &g_i);
#line 40
    sjt_parent23 = &g_a;
#line 60
    sjt_functionParam10 = 12;
#line 60
    sjf_fancymath_setbob(sjt_parent23, sjt_functionParam10, &g_j);
#line 20
    sjt_parent24 = &g_a;
#line 61
    sjt_functionParam11 = g_ii;
#line 61
    sjf_fancymath_dividei32(sjt_parent24, sjt_functionParam11, &g_k);
    main_destroy();
    return 0;
}

void main_destroy() {

    if (g_a._refCount == 1) { sjf_fancymath_destroy(&g_a); }
;
    if (g_b._refCount == 1) { sjf_fancymath_destroy(&g_b); }
;
    if (g_c._refCount == 1) { sjf_fancymath_destroy(&g_c); }
;
    if (g_d._refCount == 1) { sjf_fancymath_destroy(&g_d); }
;
    if (g_e._refCount == 1) { sjf_fancymath_destroy(&g_e); }
;
    if (g_f._refCount == 1) { sjf_fancymath_destroy(&g_f); }
;
    if (g_g._refCount == 1) { sjf_fancymath_destroy(&g_g); }
;
    if (g_k._refCount == 1) { sjf_fancymath_destroy(&g_k); }
;
    if (g_log._refCount == 1) { sjf_log_destroy(&g_log); }
;
    if (g_log_excludeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_excludeall); }
;
    if (g_log_includeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_includeall); }
;
    if (sjt_funcold1._refCount == 1) { sjf_fancymath_destroy(&sjt_funcold1); }
;
    if (sjt_funcold2._refCount == 1) { sjf_fancymath_destroy(&sjt_funcold2); }
;
    if (sjt_funcold3._refCount == 1) { sjf_fancymath_destroy(&sjt_funcold3); }
;
    if (sjt_funcold4._refCount == 1) { sjf_fancymath_destroy(&sjt_funcold4); }
;
    if (sjt_funcold5._refCount == 1) { sjf_fancymath_destroy(&sjt_funcold5); }
;
    if (sjt_funcold6._refCount == 1) { sjf_fancymath_destroy(&sjt_funcold6); }
;
    if (sjt_value1._refCount == 1) { sjf_hash_type_bool_destroy(&sjt_value1); }
;
}