#include <lib/sj-lib-common/common.h>

struct {
    int refcount;
    int size;
    int count;
    char data[0];
} g_empty = { 1, 0, 0 };
#define sjs_hash_type_bool_typeId 15
#define sjs_log_typeId 20
#define sjs_array_char_typeId 23
#define sjs_string_typeId 21
#define sjs_fancymath_typeId 27

typedef struct td_sjs_hash_type_bool sjs_hash_type_bool;
typedef struct td_sjs_log sjs_log;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_string sjs_string;
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

struct td_sjs_array_char {
    int _refCount;
    void* v;
};

struct td_sjs_string {
    int _refCount;
    int32_t offset;
    int32_t count;
    sjs_array_char data;
    bool _isnullterminated;
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
char* string_char(sjs_string* str);
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
sjs_fancymath sjt_funcold2 = { -1 };
sjs_fancymath sjt_funcold3 = { -1 };
sjs_fancymath sjt_funcold4 = { -1 };
sjs_fancymath sjt_funcold5 = { -1 };
sjs_fancymath sjt_funcold6 = { -1 };
sjs_fancymath sjt_funcold7 = { -1 };
sjs_fancymath* sjt_functionParam10 = 0;
sjs_fancymath* sjt_functionParam11 = 0;
sjs_fancymath* sjt_functionParam12 = 0;
int32_t sjt_functionParam13;
int32_t sjt_functionParam14;
sjs_fancymath* sjt_functionParam4 = 0;
sjs_fancymath* sjt_functionParam5 = 0;
sjs_fancymath* sjt_functionParam6 = 0;
sjs_fancymath* sjt_functionParam7 = 0;
sjs_fancymath* sjt_functionParam8 = 0;
sjs_fancymath* sjt_functionParam9 = 0;
sjs_fancymath* sjt_parent12 = 0;
sjs_fancymath* sjt_parent15 = 0;
sjs_fancymath* sjt_parent18 = 0;
sjs_fancymath* sjt_parent19 = 0;
sjs_fancymath* sjt_parent20 = 0;
sjs_fancymath* sjt_parent21 = 0;
sjs_fancymath* sjt_parent22 = 0;
sjs_fancymath* sjt_parent23 = 0;
sjs_fancymath* sjt_parent24 = 0;
sjs_fancymath* sjt_parent25 = 0;
sjs_fancymath* sjt_parent26 = 0;
sjs_fancymath* sjt_parent27 = 0;
sjs_fancymath* sjt_parent6 = 0;
sjs_fancymath* sjt_parent9 = 0;
sjs_hash_type_bool sjt_value1 = { -1 };

void sjf_array_char(sjs_array_char* _this);
void sjf_array_char_clone(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char* _return);
void sjf_array_char_clone_heap(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char** _return);
void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_array_char_getcount(sjs_array_char* _parent, int32_t* _return);
void sjf_array_char_gettotalcount(sjs_array_char* _parent, int32_t* _return);
void sjf_array_char_heap(sjs_array_char* _this);
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
void sjf_string_nullterminate(sjs_string* _parent);
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
char* string_char(sjs_string* str) {
    sjf_string_nullterminate(str);
    return ((sjs_array*)str->data.v)->data + str->offset;
}
#include <lib/sj-lib-common/common.cpp>
void sjf_array_char(sjs_array_char* _this) {
#line 363 "lib/sj-lib-common/array.sj"
    if (_this->v == 0) {
#line 364
        _this->v = &g_empty;
#line 365
    }
#line 366
    sjs_array* arr = (sjs_array*)_this->v;
#line 367
    arr->refcount++;
}

void sjf_array_char_clone(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char* _return) {
    void* newv;

#line 169 "lib/sj-lib-common/array.sj"
    newv = 0;
#line 171
    sjs_array* arr = (sjs_array*)_parent->v;
#line 172
    if (offset + count > arr->count) {
#line 173
        halt("grow: offset %d count %d out of bounds %d\n", offset, count, arr->count);
#line 174
    }
#line 176
    if (count > arr->count - offset) {
#line 177
        halt("grow: new count larger than old count %d:%d\n", count, arr->count - offset);
#line 178
    }
#line 180
    sjs_array* newArr = createarray(sizeof(char), newsize);
#line 181
    if (!newArr) {
#line 182
        halt("grow: out of memory\n");
#line 183
    }
#line 185
    newv = newArr;
#line 186
    char* p = (char*)arr->data + offset;
#line 187
    char* newp = (char*)newArr->data;
#line 189
    newArr->size = newsize;
#line 190
    newArr->count = count;
#line 192
    #if true
#line 193
    memcpy(newp, p, sizeof(char) * count);
#line 194
    #else
#line 195
    for (int i = 0; i < count; i++) {
#line 196
        #line 170 "lib/sj-lib-common/array.sj"
newp[i] = p[i];
;
#line 197
    }
#line 198
    #endif
#line 198
    _return->_refCount = 1;
#line 200
    _return->v = newv;
#line 200
    sjf_array_char(_return);
}

void sjf_array_char_clone_heap(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char** _return) {
    void* newv;

#line 169 "lib/sj-lib-common/array.sj"
    newv = 0;
#line 171
    sjs_array* arr = (sjs_array*)_parent->v;
#line 172
    if (offset + count > arr->count) {
#line 173
        halt("grow: offset %d count %d out of bounds %d\n", offset, count, arr->count);
#line 174
    }
#line 176
    if (count > arr->count - offset) {
#line 177
        halt("grow: new count larger than old count %d:%d\n", count, arr->count - offset);
#line 178
    }
#line 180
    sjs_array* newArr = createarray(sizeof(char), newsize);
#line 181
    if (!newArr) {
#line 182
        halt("grow: out of memory\n");
#line 183
    }
#line 185
    newv = newArr;
#line 186
    char* p = (char*)arr->data + offset;
#line 187
    char* newp = (char*)newArr->data;
#line 189
    newArr->size = newsize;
#line 190
    newArr->count = count;
#line 192
    #if true
#line 193
    memcpy(newp, p, sizeof(char) * count);
#line 194
    #else
#line 195
    for (int i = 0; i < count; i++) {
#line 196
        #line 170 "lib/sj-lib-common/array.sj"
newp[i] = p[i];
;
#line 197
    }
#line 198
    #endif
#line 198
    (*_return) = (sjs_array_char*)malloc(sizeof(sjs_array_char));
#line 198
    (*_return)->_refCount = 1;
#line 200
    (*_return)->v = newv;
#line 200
    sjf_array_char_heap((*_return));
}

void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from) {
#line 26 "lib/sj-lib-common/array.sj"
    _this->v = _from->v;
#line 372
    sjs_array* arr = (sjs_array*)_this->v;
#line 373
    arr->refcount++;
}

void sjf_array_char_destroy(sjs_array_char* _this) {
#line 377 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_this->v;
#line 378
    arr->refcount--;
#line 379
    if (arr->refcount == 0) {
#line 380
        #if !true && !false
#line 381
        char* p = (char*)arr->data;
#line 382
        for (int i = 0; i < arr->count; i++) {
#line 383
            ;
#line 384
        }
#line 385
        #endif
#line 386
        free(arr);
#line 387
    }
}

void sjf_array_char_getcount(sjs_array_char* _parent, int32_t* _return) {
#line 31 "lib/sj-lib-common/array.sj"
    #line 30 "lib/sj-lib-common/array.sj"
(*_return) = ((sjs_array*)_parent->v)->count;
return;;
}

void sjf_array_char_gettotalcount(sjs_array_char* _parent, int32_t* _return) {
#line 37 "lib/sj-lib-common/array.sj"
    #line 36 "lib/sj-lib-common/array.sj"
(*_return) = ((sjs_array*)_parent->v)->size;
return;;
}

void sjf_array_char_heap(sjs_array_char* _this) {
#line 363 "lib/sj-lib-common/array.sj"
    if (_this->v == 0) {
#line 364
        _this->v = &g_empty;
#line 365
    }
#line 366
    sjs_array* arr = (sjs_array*)_this->v;
#line 367
    arr->refcount++;
}

void sjf_fancymath(sjs_fancymath* _this) {
}

void sjf_fancymath_add(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return) {
    int32_t sjt_capture3;
    sjs_fancymath* sjt_parent4 = 0;

    _return->_refCount = 1;
#line 4 "operator.sj"
    sjt_parent4 = num;
#line 4
    sjf_fancymath_getx(sjt_parent4, &sjt_capture3);
#line 5
    _return->x = (_parent->x + sjt_capture3) + 1;
#line 5
    sjf_fancymath(_return);
}

void sjf_fancymath_add_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture4;
    sjs_fancymath* sjt_parent5 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 4 "operator.sj"
    sjt_parent5 = num;
#line 4
    sjf_fancymath_getx(sjt_parent5, &sjt_capture4);
#line 5
    (*_return)->x = (_parent->x + sjt_capture4) + 1;
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
    int32_t sjt_capture9;
    sjs_fancymath* sjt_parent13 = 0;

    _return->_refCount = 1;
#line 16 "operator.sj"
    sjt_parent13 = num;
#line 16
    sjf_fancymath_getx(sjt_parent13, &sjt_capture9);
#line 17
    _return->x = (_parent->x / sjt_capture9) + 1;
#line 17
    sjf_fancymath(_return);
}

void sjf_fancymath_divide_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture10;
    sjs_fancymath* sjt_parent14 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 16 "operator.sj"
    sjt_parent14 = num;
#line 16
    sjf_fancymath_getx(sjt_parent14, &sjt_capture10);
#line 17
    (*_return)->x = (_parent->x / sjt_capture10) + 1;
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
    int32_t sjt_capture11;
    sjs_fancymath* sjt_parent16 = 0;

    _return->_refCount = 1;
#line 24 "operator.sj"
    sjt_parent16 = num;
#line 24
    sjf_fancymath_getx(sjt_parent16, &sjt_capture11);
#line 25
    _return->x = (_parent->x % sjt_capture11) + 1;
#line 25
    sjf_fancymath(_return);
}

void sjf_fancymath_modulus_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture12;
    sjs_fancymath* sjt_parent17 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 24 "operator.sj"
    sjt_parent17 = num;
#line 24
    sjf_fancymath_getx(sjt_parent17, &sjt_capture12);
#line 25
    (*_return)->x = (_parent->x % sjt_capture12) + 1;
#line 25
    sjf_fancymath_heap((*_return));
}

void sjf_fancymath_multiply(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath* _return) {
    int32_t sjt_capture7;
    sjs_fancymath* sjt_parent10 = 0;

    _return->_refCount = 1;
#line 12 "operator.sj"
    sjt_parent10 = num;
#line 12
    sjf_fancymath_getx(sjt_parent10, &sjt_capture7);
#line 13
    _return->x = (_parent->x * sjt_capture7) + 1;
#line 13
    sjf_fancymath(_return);
}

void sjf_fancymath_multiply_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture8;
    sjs_fancymath* sjt_parent11 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 12 "operator.sj"
    sjt_parent11 = num;
#line 12
    sjf_fancymath_getx(sjt_parent11, &sjt_capture8);
#line 13
    (*_return)->x = (_parent->x * sjt_capture8) + 1;
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
    int32_t sjt_capture5;
    sjs_fancymath* sjt_parent7 = 0;

    _return->_refCount = 1;
#line 8 "operator.sj"
    sjt_parent7 = num;
#line 8
    sjf_fancymath_getx(sjt_parent7, &sjt_capture5);
#line 9
    _return->x = (_parent->x - sjt_capture5) + 1;
#line 9
    sjf_fancymath(_return);
}

void sjf_fancymath_subtract_heap(sjs_fancymath* _parent, sjs_fancymath* num, sjs_fancymath** _return) {
    int32_t sjt_capture6;
    sjs_fancymath* sjt_parent8 = 0;

    (*_return) = (sjs_fancymath*)malloc(sizeof(sjs_fancymath));
    (*_return)->_refCount = 1;
#line 8 "operator.sj"
    sjt_parent8 = num;
#line 8
    sjf_fancymath_getx(sjt_parent8, &sjt_capture6);
#line 9
    (*_return)->x = (_parent->x - sjt_capture6) + 1;
#line 9
    sjf_fancymath_heap((*_return));
}

void sjf_hash_type_bool(sjs_hash_type_bool* _this) {
#line 233 "lib/sj-lib-common/hash.sj"
    _this->_hash = kh_init(type_bool_hash_type);
}

void sjf_hash_type_bool__weakptrremovekey(sjs_hash_type_bool* _parent, int32_t key) {
#line 188 "lib/sj-lib-common/hash.sj"
    #if false
#line 189
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_parent->_hash;    
#line 190
    khiter_t k = kh_get(type_bool_hash_type, p, key);
#line 191
    if (k != kh_end(p)) {
#line 192
        kh_del(type_bool_hash_type, p, k);
#line 193
    }
#line 194
    #endif
}

void sjf_hash_type_bool__weakptrremovevalue(sjs_hash_type_bool* _parent, bool val) {
#line 200 "lib/sj-lib-common/hash.sj"
    #if false
#line 201
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_parent->_hash;
#line 202
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 203
        if (kh_exist(p, k)) {
#line 204
            bool t = kh_value(p, k);
#line 205
            if (t == val) {
#line 206
                kh_del(type_bool_hash_type, p, k);
#line 207
            }
#line 208
        }
#line 209
    }
#line 210
    #endif
}

void sjf_hash_type_bool_copy(sjs_hash_type_bool* _this, sjs_hash_type_bool* _from) {
#line 238 "lib/sj-lib-common/hash.sj"
    _this->_hash = _from->_hash;
#line 239
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_this->_hash;
#line 240
    p->refcount++;
}

void sjf_hash_type_bool_destroy(sjs_hash_type_bool* _this) {
#line 244 "lib/sj-lib-common/hash.sj"
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_this->_hash;
#line 245
    p->refcount--;
#line 246
    if (p->refcount == 0) {
#line 247
        for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 248
            if (kh_exist(p, k)) {
#line 250
                #if false
#line 251
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_type_bool__weakptrremovekey };
#line 252
                weakptr_cb_remove(kh_key(p, k), cb);
#line 253
                #else
#line 254
                ;
#line 255
                #endif
#line 257
                #if false
#line 258
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_type_bool__weakptrremovevalue };
#line 259
                weakptr_cb_remove(kh_value(p, k), cb);
#line 260
                #else
#line 261
                ;
#line 262
                #endif
#line 263
            }
#line 264
        }
#line 265
        kh_destroy(type_bool_hash_type, (khash_t(type_bool_hash_type)*)_this->_hash);
#line 266
    }
}

void sjf_hash_type_bool_heap(sjs_hash_type_bool* _this) {
#line 233 "lib/sj-lib-common/hash.sj"
    _this->_hash = kh_init(type_bool_hash_type);
}

void sjf_log(sjs_log* _this) {
}

void sjf_log_copy(sjs_log* _this, sjs_log* _from) {
#line 13 "lib/sj-lib-common/log.sj"
    _this->minlevel = _from->minlevel;
#line 13
    sjs_hash_type_bool* copyoption2 = (_from->traceincludes._refCount != -1 ? &_from->traceincludes : 0);
    if (copyoption2 != 0) {
        _this->traceincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&_this->traceincludes, copyoption2);
    } else {
        _this->traceincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption3 = (_from->debugincludes._refCount != -1 ? &_from->debugincludes : 0);
    if (copyoption3 != 0) {
        _this->debugincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&_this->debugincludes, copyoption3);
    } else {
        _this->debugincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption4 = (_from->infoincludes._refCount != -1 ? &_from->infoincludes : 0);
    if (copyoption4 != 0) {
        _this->infoincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&_this->infoincludes, copyoption4);
    } else {
        _this->infoincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption5 = (_from->warnincludes._refCount != -1 ? &_from->warnincludes : 0);
    if (copyoption5 != 0) {
        _this->warnincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&_this->warnincludes, copyoption5);
    } else {
        _this->warnincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption6 = (_from->errorincludes._refCount != -1 ? &_from->errorincludes : 0);
    if (copyoption6 != 0) {
        _this->errorincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&_this->errorincludes, copyoption6);
    } else {
        _this->errorincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption7 = (_from->fatalincludes._refCount != -1 ? &_from->fatalincludes : 0);
    if (copyoption7 != 0) {
        _this->fatalincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
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

void sjf_string_nullterminate(sjs_string* _parent) {
    bool result2;
    sjs_array_char sjt_funcold1 = { -1 };

#line 133 "lib/sj-lib-common/string.sj"
    result2 = !_parent->_isnullterminated;
    if (result2) {
        int32_t sjt_capture1;
        int32_t sjt_capture2;
        sjs_array_char* sjt_parent1 = 0;
        sjs_array_char* sjt_parent2 = 0;

#line 35 "lib/sj-lib-common/array.sj"
        sjt_parent1 = &_parent->data;
#line 35
        sjf_array_char_gettotalcount(sjt_parent1, &sjt_capture1);
#line 29
        sjt_parent2 = &_parent->data;
#line 29
        sjf_array_char_getcount(sjt_parent2, &sjt_capture2);
        if ((((_parent->offset + _parent->count) + 1) > sjt_capture1) || ((_parent->offset + _parent->count) != sjt_capture2)) {
            int32_t sjt_functionParam1;
            int32_t sjt_functionParam2;
            int32_t sjt_functionParam3;
            sjs_array_char* sjt_parent3 = 0;

#line 168 "lib/sj-lib-common/array.sj"
            sjt_parent3 = &_parent->data;
#line 135 "lib/sj-lib-common/string.sj"
            sjt_functionParam1 = _parent->offset;
#line 135
            sjt_functionParam2 = _parent->count;
#line 135
            sjt_functionParam3 = _parent->count + 1;
#line 135
            sjf_array_char_clone(sjt_parent3, sjt_functionParam1, sjt_functionParam2, sjt_functionParam3, &sjt_funcold1);
#line 135
            if (_parent->data._refCount == 1) { sjf_array_char_destroy(&_parent->data); }
;
#line 168 "lib/sj-lib-common/array.sj"
            sjf_array_char_copy(&_parent->data, &sjt_funcold1);
#line 136 "lib/sj-lib-common/string.sj"
            _parent->offset = 0;
        }

#line 139 "lib/sj-lib-common/string.sj"
        ((sjs_array*)_parent->data.v)->data[_parent->offset + _parent->count] = 0;
#line 141
        _parent->_isnullterminated = true;
    }

    if (sjt_funcold1._refCount == 1) { sjf_array_char_destroy(&sjt_funcold1); }
;
}

void sjf_type_hash(int32_t val, uint32_t* _return) {
    int32_t sjt_cast1;

#line 5 "lib/sj-lib-common/type.sj"
    sjt_cast1 = val;
#line 6
    (*_return) = (uint32_t)sjt_cast1;
}

void sjf_type_isequal(int32_t l, int32_t r, bool* _return) {
#line 10 "lib/sj-lib-common/type.sj"
    (*_return) = l == r;
}

int main(int argc, char** argv) {
#line 1 "lib/sj-lib-common/log.sj"
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
#line 1 "lib/sj-lib-common/f32.sj"
    g_f32_pi = 3.14159265358979323846f;
#line 1 "lib/sj-lib-common/i32.sj"
    g_u32_maxvalue = (uint32_t)4294967295u;
#line 3
    result1 = -1;
#line 3
    g_i32_maxvalue = result1 - 2147483647;
#line 4
    g_i32_minvalue = 2147483647;
#line 10 "lib/sj-lib-common/log.sj"
    g_log_includeall._refCount = -1;
#line 10
    sjt_value1._refCount = 1;
#line 10
    sjf_hash_type_bool(&sjt_value1);
#line 11
    sjs_hash_type_bool* copyoption1 = &sjt_value1;
    if (copyoption1 != 0) {
        g_log_excludeall._refCount = 1;
#line 11 "lib/sj-lib-common/log.sj"
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
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&g_log.traceincludes, copyoption8);
    } else {
        g_log.traceincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption9 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption9 != 0) {
        g_log.debugincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&g_log.debugincludes, copyoption9);
    } else {
        g_log.debugincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption10 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption10 != 0) {
        g_log.infoincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&g_log.infoincludes, copyoption10);
    } else {
        g_log.infoincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption11 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption11 != 0) {
        g_log.warnincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&g_log.warnincludes, copyoption11);
    } else {
        g_log.warnincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption12 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption12 != 0) {
        g_log.errorincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&g_log.errorincludes, copyoption12);
    } else {
        g_log.errorincludes._refCount = -1;
    }

#line 13
    sjs_hash_type_bool* copyoption13 = (g_log_includeall._refCount != -1 ? &g_log_includeall : 0);
    if (copyoption13 != 0) {
        g_log.fatalincludes._refCount = 1;
#line 13 "lib/sj-lib-common/log.sj"
        sjf_hash_type_bool_copy(&g_log.fatalincludes, copyoption13);
    } else {
        g_log.fatalincludes._refCount = -1;
    }

#line 13
    sjf_log(&g_log);
#line 2 "lib/sj-lib-common/weakptr.sj"
    ptr_init();
#line 3
    weakptr_init();
#line 7 "lib/sj-lib-common/clock.sj"
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
    sjt_parent6 = &g_a;
#line 48
    sjt_functionParam4 = &g_b;
#line 48
    sjf_fancymath_add(sjt_parent6, sjt_functionParam4, &g_c);
#line 8
    sjt_parent9 = &g_a;
#line 49
    sjt_functionParam5 = &g_b;
#line 49
    sjf_fancymath_subtract(sjt_parent9, sjt_functionParam5, &g_d);
#line 12
    sjt_parent12 = &g_a;
#line 50
    sjt_functionParam6 = &g_b;
#line 50
    sjf_fancymath_multiply(sjt_parent12, sjt_functionParam6, &g_e);
#line 16
    sjt_parent15 = &g_a;
#line 51
    sjt_functionParam7 = &g_b;
#line 51
    sjf_fancymath_divide(sjt_parent15, sjt_functionParam7, &g_f);
#line 24
    sjt_parent18 = &g_a;
#line 52
    sjt_functionParam8 = &g_b;
#line 52
    sjf_fancymath_modulus(sjt_parent18, sjt_functionParam8, &g_g);
#line 4
    sjt_parent19 = &g_c;
#line 53
    sjt_functionParam9 = &g_c;
#line 53
    sjf_fancymath_add(sjt_parent19, sjt_functionParam9, &sjt_funcold2);
#line 53
    if (g_c._refCount == 1) { sjf_fancymath_destroy(&g_c); }
;
#line 4
    sjf_fancymath_copy(&g_c, &sjt_funcold2);
#line 8
    sjt_parent20 = &g_d;
#line 54
    sjt_functionParam10 = &g_d;
#line 54
    sjf_fancymath_subtract(sjt_parent20, sjt_functionParam10, &sjt_funcold3);
#line 54
    if (g_d._refCount == 1) { sjf_fancymath_destroy(&g_d); }
;
#line 8
    sjf_fancymath_copy(&g_d, &sjt_funcold3);
#line 12
    sjt_parent21 = &g_d;
#line 55
    sjt_functionParam11 = &g_d;
#line 55
    sjf_fancymath_multiply(sjt_parent21, sjt_functionParam11, &sjt_funcold4);
#line 55
    if (g_d._refCount == 1) { sjf_fancymath_destroy(&g_d); }
;
#line 12
    sjf_fancymath_copy(&g_d, &sjt_funcold4);
#line 16
    sjt_parent22 = &g_d;
#line 56
    sjt_functionParam12 = &g_d;
#line 56
    sjf_fancymath_divide(sjt_parent22, sjt_functionParam12, &sjt_funcold5);
#line 56
    if (g_d._refCount == 1) { sjf_fancymath_destroy(&g_d); }
;
#line 16
    sjf_fancymath_copy(&g_d, &sjt_funcold5);
#line 28
    sjt_parent23 = &g_e;
#line 28
    sjf_fancymath_increment(sjt_parent23, &sjt_funcold6);
#line 28
    if (g_e._refCount == 1) { sjf_fancymath_destroy(&g_e); }
;
#line 28
    sjf_fancymath_copy(&g_e, &sjt_funcold6);
#line 28
    sjt_parent24 = &g_f;
#line 28
    sjf_fancymath_increment(sjt_parent24, &sjt_funcold7);
#line 28
    if (g_f._refCount == 1) { sjf_fancymath_destroy(&g_f); }
;
#line 28
    sjf_fancymath_copy(&g_f, &sjt_funcold7);
#line 36
    sjt_parent25 = &g_f;
#line 36
    sjf_fancymath_getx(sjt_parent25, &g_i);
#line 40
    sjt_parent26 = &g_a;
#line 60
    sjt_functionParam13 = 12;
#line 60
    sjf_fancymath_setbob(sjt_parent26, sjt_functionParam13, &g_j);
#line 20
    sjt_parent27 = &g_a;
#line 61
    sjt_functionParam14 = g_ii;
#line 61
    sjf_fancymath_dividei32(sjt_parent27, sjt_functionParam14, &g_k);
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
    if (sjt_funcold7._refCount == 1) { sjf_fancymath_destroy(&sjt_funcold7); }
;
    if (sjt_value1._refCount == 1) { sjf_hash_type_bool_destroy(&sjt_value1); }
;
}
