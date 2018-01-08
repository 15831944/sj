#include <lib/sj-lib-common/common.h>

sjs_array sjg_string1 = { 1, 0, 0, ""};
sjs_array sjg_string10 = { 1, 3, 3, "ptr"};
sjs_array sjg_string11 = { 1, 6, 6, "#iface"};
sjs_array sjg_string12 = { 1, 10, 10, "array!char"};
sjs_array sjg_string13 = { 1, 5, 5, "clone"};
sjs_array sjg_string14 = { 1, 7, 7, "getsize"};
sjs_array sjg_string15 = { 1, 5, 5, "class"};
sjs_array sjg_string16 = { 1, 1, 1, "b"};
sjs_array sjg_string17 = { 1, 9, 9, "writeline"};
sjs_array sjg_string18 = { 1, 6, 6, "global"};
sjs_array sjg_string19 = { 1, 17, 17, "hash![type, bool]"};
sjs_array sjg_string2 = { 1, 4, 4, "bool"};
sjs_array sjg_string20 = { 1, 17, 17, "_weakptrremovekey"};
sjs_array sjg_string21 = { 1, 19, 19, "_weakptrremovevalue"};
sjs_array sjg_string22 = { 1, 3, 3, "log"};
sjs_array sjg_string23 = { 1, 6, 6, "string"};
sjs_array sjg_string24 = { 1, 13, 13, "nullterminate"};
sjs_array sjg_string25 = { 1, 13, 13, "type_asstring"};
sjs_array sjg_string26 = { 1, 9, 9, "type_hash"};
sjs_array sjg_string27 = { 1, 12, 12, "type_isequal"};
sjs_array sjg_string28 = { 1, 4, 4, "type"};
sjs_array sjg_string29 = { 1, 3, 3, "u32"};
sjs_array sjg_string3 = { 1, 5, 5, "()i32"};
sjs_array sjg_string30 = { 1, 3, 3, "u64"};
sjs_array sjg_string31 = { 1, 4, 4, "void"};
sjs_array sjg_string4 = { 1, 4, 4, "char"};
sjs_array sjg_string5 = { 1, 3, 3, "f32"};
sjs_array sjg_string6 = { 1, 3, 3, "f64"};
sjs_array sjg_string7 = { 1, 3, 3, "i32"};
sjs_array sjg_string8 = { 1, 3, 3, "i64"};
sjs_array sjg_string9 = { 1, 8, 8, "loglevel"};

sjs_array g_empty = { 1, 1, 0, "" };
#define sjs_hash_type_bool_typeId 15
#define sjs_log_typeId 20
#define sjs_array_char_typeId 23
#define sjs_string_typeId 21
#define sjs_class_typeId 26
#define sji_iface_typeId 27

typedef struct td_sjs_hash_type_bool sjs_hash_type_bool;
typedef struct td_sjs_log sjs_log;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_string sjs_string;
typedef struct td_sjs_class sjs_class;
typedef struct td_sji_iface_vtbl sji_iface_vtbl;
typedef struct td_sji_iface sji_iface;

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

struct td_sjs_class {
    int _refCount;
};

struct td_sji_iface_vtbl {
    void (*destroy)(void* _this);
    void (*asinterface)(sjs_object* _this, int typeId, sjs_interface* _return);
    void (*getclasstype)(sjs_object* _parent, int32_t* _return);
};

struct td_sji_iface {
    sjs_object* _parent;
    sji_iface_vtbl* _vtbl;
};

sji_iface_vtbl sjs_class_iface_vtbl;
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

sjs_class g_a = { -1 };
int32_t g_clocks_per_sec;
int32_t g_d1;
int32_t g_d2;
int32_t g_d3;
int32_t g_d4;
float g_f32_pi;
sji_iface g_i = { 0 };
int32_t g_i32_maxvalue;
int32_t g_i32_minvalue;
sjs_log g_log = { -1 };
sjs_hash_type_bool g_log_excludeall = { -1 };
sjs_hash_type_bool g_log_includeall = { -1 };
int32_t g_t1;
int32_t g_t2;
int32_t g_t3;
int32_t g_t4;
int32_t g_t5;
uint32_t g_u32_maxvalue;
int32_t result1;
sjs_string sjt_call1 = { -1 };
sjs_string sjt_call2 = { -1 };
sjs_string sjt_call3 = { -1 };
sjs_string sjt_call4 = { -1 };
sjs_string sjt_call5 = { -1 };
sjs_string sjt_call6 = { -1 };
sjs_string sjt_call7 = { -1 };
sjs_string sjt_call8 = { -1 };
sjs_string sjt_call9 = { -1 };
sjs_class* sjt_cast2 = 0;
sjs_string* sjt_functionParam10 = 0;
int32_t sjt_functionParam11;
sjs_string* sjt_functionParam12 = 0;
int32_t sjt_functionParam13;
sjs_string* sjt_functionParam14 = 0;
int32_t sjt_functionParam15;
sjs_string* sjt_functionParam16 = 0;
int32_t sjt_functionParam17;
sjs_string* sjt_functionParam18 = 0;
int32_t sjt_functionParam19;
sjs_string* sjt_functionParam20 = 0;
int32_t sjt_functionParam21;
sjs_string* sjt_functionParam4 = 0;
int32_t sjt_functionParam5;
sjs_string* sjt_functionParam6 = 0;
int32_t sjt_functionParam7;
sjs_string* sjt_functionParam8 = 0;
int32_t sjt_functionParam9;
sji_iface sjt_parent3 = { 0 };
sjs_hash_type_bool sjt_value1 = { -1 };

void sjf_array_char(sjs_array_char* _this);
void sjf_array_char_clone(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char* _return);
void sjf_array_char_clone_heap(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char** _return);
void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_array_char_getsize(sjs_array_char* _parent, int32_t* _return);
void sjf_array_char_heap(sjs_array_char* _this);
void sjf_class(sjs_class* _this);
void sjf_class_as_sji_iface(sjs_class* _this, sji_iface* _return);
void sjf_class_asinterface(sjs_class* _this, int typeId, sjs_interface* _return);
void sjf_class_copy(sjs_class* _this, sjs_class* _from);
void sjf_class_destroy(sjs_class* _this);
void sjf_class_getclasstype(sjs_object* _this, int* _return);
void sjf_class_heap(sjs_class* _this);
void sjf_debug_writeline(sjs_string* data);
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
void sjf_string(sjs_string* _this);
void sjf_string_copy(sjs_string* _this, sjs_string* _from);
void sjf_string_destroy(sjs_string* _this);
void sjf_string_heap(sjs_string* _this);
void sjf_string_nullterminate(sjs_string* _parent);
void sjf_type_asstring(int32_t t, sjs_string* _return);
void sjf_type_asstring_heap(int32_t t, sjs_string** _return);
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
    return ((sjs_array*)str->data.v)->data;
}
#include <lib/sj-lib-common/common.cpp>
void sjf_array_char(sjs_array_char* _this) {
#line 351 "lib/sj-lib-common/array.sj"
    if (_this->v == 0) {
#line 352
        _this->v = &g_empty;
#line 353
    }
#line 354
    sjs_array* arr = (sjs_array*)_this->v;
#line 355
    arr->refcount++;
}

void sjf_array_char_clone(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char* _return) {
    void* newv;

#line 165 "lib/sj-lib-common/array.sj"
    newv = 0;
#line 167
    sjs_array* arr = (sjs_array*)_parent->v;
#line 168
    if (offset + count > arr->count) {
#line 169
        halt("grow: offset %d count %d out of bounds %d\n", offset, count, arr->count);
#line 170
    }
#line 172
    if (count > arr->count - offset) {
#line 173
        halt("grow: new count larger than old count %d:%d\n", count, arr->count - offset);
#line 174
    }
#line 176
    sjs_array* newArr = createarray(newsize * sizeof(char));
#line 177
    if (!newArr) {
#line 178
        halt("grow: out of memory\n");
#line 179
    }
#line 181
    newv = newArr;
#line 182
    char* p = (char*)arr->data + offset;
#line 183
    char* newp = (char*)newArr->data;
#line 185
    newArr->refcount = 1;
#line 186
    newArr->size = newsize;
#line 187
    newArr->count = count;
#line 189
    #if true
#line 190
    memcpy(newp, p, sizeof(char) * count);
#line 191
    #else
#line 192
    for (int i = 0; i < count; i++) {
#line 193
        #line 166 "lib/sj-lib-common/array.sj"
newp[i] = p[i];
;
#line 194
    }
#line 195
    #endif
#line 195
    _return->_refCount = 1;
#line 197
    _return->v = newv;
#line 197
    sjf_array_char(_return);
}

void sjf_array_char_clone_heap(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char** _return) {
    void* newv;

#line 165 "lib/sj-lib-common/array.sj"
    newv = 0;
#line 167
    sjs_array* arr = (sjs_array*)_parent->v;
#line 168
    if (offset + count > arr->count) {
#line 169
        halt("grow: offset %d count %d out of bounds %d\n", offset, count, arr->count);
#line 170
    }
#line 172
    if (count > arr->count - offset) {
#line 173
        halt("grow: new count larger than old count %d:%d\n", count, arr->count - offset);
#line 174
    }
#line 176
    sjs_array* newArr = createarray(newsize * sizeof(char));
#line 177
    if (!newArr) {
#line 178
        halt("grow: out of memory\n");
#line 179
    }
#line 181
    newv = newArr;
#line 182
    char* p = (char*)arr->data + offset;
#line 183
    char* newp = (char*)newArr->data;
#line 185
    newArr->refcount = 1;
#line 186
    newArr->size = newsize;
#line 187
    newArr->count = count;
#line 189
    #if true
#line 190
    memcpy(newp, p, sizeof(char) * count);
#line 191
    #else
#line 192
    for (int i = 0; i < count; i++) {
#line 193
        #line 166 "lib/sj-lib-common/array.sj"
newp[i] = p[i];
;
#line 194
    }
#line 195
    #endif
#line 195
    (*_return) = (sjs_array_char*)malloc(sizeof(sjs_array_char));
#line 195
    (*_return)->_refCount = 1;
#line 197
    (*_return)->v = newv;
#line 197
    sjf_array_char_heap((*_return));
}

void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from) {
#line 21 "lib/sj-lib-common/array.sj"
    _this->v = _from->v;
#line 360
    sjs_array* arr = (sjs_array*)_this->v;
#line 361
    arr->refcount++;
}

void sjf_array_char_destroy(sjs_array_char* _this) {
#line 365 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_this->v;
#line 366
    arr->refcount--;
#line 367
    if (arr->refcount == 0) {
#line 368
        #if !true && !false
#line 369
        char* p = (char*)arr->data;
#line 370
        for (int i = 0; i < arr->count; i++) {
#line 371
            ;
#line 372
        }
#line 373
        #endif
#line 374
        free(arr);
#line 375
    }
}

void sjf_array_char_getsize(sjs_array_char* _parent, int32_t* _return) {
#line 32 "lib/sj-lib-common/array.sj"
    #line 31 "lib/sj-lib-common/array.sj"
(*_return) = ((sjs_array*)_parent->v)->size;
return;;
}

void sjf_array_char_heap(sjs_array_char* _this) {
#line 351 "lib/sj-lib-common/array.sj"
    if (_this->v == 0) {
#line 352
        _this->v = &g_empty;
#line 353
    }
#line 354
    sjs_array* arr = (sjs_array*)_this->v;
#line 355
    arr->refcount++;
}

void sjf_class(sjs_class* _this) {
}

void sjf_class_as_sji_iface(sjs_class* _this, sji_iface* _return) {
    _return->_parent = (sjs_object*)_this;
    _return->_vtbl = &sjs_class_iface_vtbl;
}

void sjf_class_asinterface(sjs_class* _this, int typeId, sjs_interface* _return) {
    switch (typeId) {
        case sji_iface_typeId:  {
            sjf_class_as_sji_iface(_this, (sji_iface*)_return);
            break;
        }

        default: {
            _return->_parent = 0;
            break;
        }
    }
}

void sjf_class_copy(sjs_class* _this, sjs_class* _from) {
}

void sjf_class_destroy(sjs_class* _this) {
}

void sjf_class_getclasstype(sjs_object* _this, int* _return) {
    *_return = 26;
}

void sjf_class_heap(sjs_class* _this) {
}

void sjf_debug_writeline(sjs_string* data) {
#line 10 "lib/sj-lib-common/debug.sj"
    debugout("%s\n", string_char(data));
}

void sjf_hash_type_bool(sjs_hash_type_bool* _this) {
#line 225 "lib/sj-lib-common/hash.sj"
    _this->_hash = kh_init(type_bool_hash_type);
}

void sjf_hash_type_bool__weakptrremovekey(sjs_hash_type_bool* _parent, int32_t key) {
#line 180 "lib/sj-lib-common/hash.sj"
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
#line 192 "lib/sj-lib-common/hash.sj"
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
#line 230 "lib/sj-lib-common/hash.sj"
    _this->_hash = _from->_hash;
#line 231
    khash_t(type_bool_hash_type)* p = (khash_t(type_bool_hash_type)*)_this->_hash;
#line 232
    p->refcount++;
}

void sjf_hash_type_bool_destroy(sjs_hash_type_bool* _this) {
#line 236 "lib/sj-lib-common/hash.sj"
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
        kh_destroy(type_bool_hash_type, (khash_t(type_bool_hash_type)*)_this->_hash);
#line 258
    }
}

void sjf_hash_type_bool_heap(sjs_hash_type_bool* _this) {
#line 225 "lib/sj-lib-common/hash.sj"
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

void sjf_string(sjs_string* _this) {
}

void sjf_string_copy(sjs_string* _this, sjs_string* _from) {
#line 12 "lib/sj-lib-common/string.sj"
    _this->offset = _from->offset;
#line 12
    _this->count = _from->count;
#line 12
    _this->data._refCount = 1;
#line 12
    sjf_array_char_copy(&_this->data, &_from->data);
#line 12
    _this->_isnullterminated = _from->_isnullterminated;
}

void sjf_string_destroy(sjs_string* _this) {
    if (_this->data._refCount == 1) { sjf_array_char_destroy(&_this->data); }
;
}

void sjf_string_heap(sjs_string* _this) {
}

void sjf_string_nullterminate(sjs_string* _parent) {
    bool result2;
    sjs_array_char sjt_funcold1 = { -1 };

#line 133 "lib/sj-lib-common/string.sj"
    result2 = !_parent->_isnullterminated;
    if (result2) {
        int32_t sjt_capture1;
        sjs_array_char* sjt_parent1 = 0;

#line 30 "lib/sj-lib-common/array.sj"
        sjt_parent1 = &_parent->data;
#line 30
        sjf_array_char_getsize(sjt_parent1, &sjt_capture1);
        if ((_parent->count + 1) > sjt_capture1) {
            int32_t sjt_functionParam1;
            int32_t sjt_functionParam2;
            int32_t sjt_functionParam3;
            sjs_array_char* sjt_parent2 = 0;

            sjt_funcold1._refCount = 1;
#line 164 "lib/sj-lib-common/array.sj"
            sjf_array_char_copy(&sjt_funcold1, &_parent->data);
#line 164
            sjt_parent2 = &_parent->data;
#line 135 "lib/sj-lib-common/string.sj"
            sjt_functionParam1 = _parent->offset;
#line 135
            sjt_functionParam2 = _parent->count;
#line 135
            sjt_functionParam3 = _parent->count + 1;
#line 135
            sjf_array_char_clone(sjt_parent2, sjt_functionParam1, sjt_functionParam2, sjt_functionParam3, &sjt_funcold1);
#line 135
            if (_parent->data._refCount == 1) { sjf_array_char_destroy(&_parent->data); }
;
#line 164 "lib/sj-lib-common/array.sj"
            sjf_array_char_copy(&_parent->data, &sjt_funcold1);
#line 136 "lib/sj-lib-common/string.sj"
            _parent->offset = 0;
        }

#line 139 "lib/sj-lib-common/string.sj"
        ((sjs_array*)_parent->data.v)->data[_parent->count] = 0;
#line 141
        _parent->_isnullterminated = true;
    }

    if (sjt_funcold1._refCount == 1) { sjf_array_char_destroy(&sjt_funcold1); }
;
}

void sjf_type_asstring(int32_t t, sjs_string* _return) {
    switch (t) {
        case 8:
        _return->_refCount = 1;
        _return->offset = 0;
        _return->count = 4;
        _return->data._refCount = 1;
        _return->data.v = &sjg_string2;
        sjf_array_char(&_return->data);
#line 16 "lib/sj-lib-common/string.sj"
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 29:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 5;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string3;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 9:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 4;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string4;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 6:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 3;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string5;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 7:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 3;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string6;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 1:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 3;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string7;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 2:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 3;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string8;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 12:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 8;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string9;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 5:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 3;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string10;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 27:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 6;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string11;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 13:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 0;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string1;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 23:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 10;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string12;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 25:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 5;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string13;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 24:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 7;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string14;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 26:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 5;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string15;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 28:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 1;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string16;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 30:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 9;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string17;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 14:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 6;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string18;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 15:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 17;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string19;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 18:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 17;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string20;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 19:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 19;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string21;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 20:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 3;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string22;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 21:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 6;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string23;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 22:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 13;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string24;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 31:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 13;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string25;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 16:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 9;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string26;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 17:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 12;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string27;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 11:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 4;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string28;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 3:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 3;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string29;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 4:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 3;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string30;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        case 10:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 4;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string31;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
        default:
#line 16
        _return->_refCount = 1;
#line 16
        _return->offset = 0;
#line 16
        _return->count = 0;
#line 16
        _return->data._refCount = 1;
#line 16
        _return->data.v = &sjg_string1;
#line 16
        sjf_array_char(&_return->data);
#line 16
        _return->_isnullterminated = false;
#line 16
        sjf_string(_return);
#line 16
        break;
#line 16
    }
}

void sjf_type_asstring_heap(int32_t t, sjs_string** _return) {
    (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
    (*_return)->_refCount = 1;
#line 2 "lib/sj-lib-common/type.sj"
    (*_return)->offset = 0;
#line 2
    (*_return)->count = 0;
#line 2
    (*_return)->data._refCount = 1;
#line 2
    (*_return)->data.v = &sjg_string1;
#line 2
    sjf_array_char(&(*_return)->data);
#line 16 "lib/sj-lib-common/string.sj"
    (*_return)->_isnullterminated = false;
#line 16
    sjf_string_heap((*_return));
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
    sjs_class_iface_vtbl.destroy = (void(*)(void*))sjf_class_destroy;
    sjs_class_iface_vtbl.asinterface = (void(*)(sjs_object*,int,sjs_interface*))sjf_class_asinterface;
    sjs_class_iface_vtbl.getclasstype = (void(*)(sjs_object*,int*))sjf_class_getclasstype;
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
#line 9
    sjf_class(&g_a);
#line 7 "type1.sj"
    sjt_cast2 = &g_a;
#line 1
    sjf_class_as_sji_iface(sjt_cast2, &g_i);
#line 9
    g_t1 = 26;
#line 10
    g_t2 = 1;
#line 11
    g_t3 = 29;
#line 12
    g_t4 = 27;
#line 1
    sjt_parent3 = g_i;
#line 13
    sjt_parent3._vtbl->getclasstype(sjt_parent3._parent, &g_t5);
#line 14
    g_d1 = 1;
#line 15
    g_d2 = 26;
#line 16
    g_d3 = 29;
#line 17
    g_d4 = 27;
#line 19
    sjt_functionParam5 = g_t1;
#line 19
    sjf_type_asstring(sjt_functionParam5, &sjt_call1);
#line 19
    sjt_functionParam4 = &sjt_call1;
#line 19
    sjf_debug_writeline(sjt_functionParam4);
#line 20
    sjt_functionParam7 = g_t2;
#line 20
    sjf_type_asstring(sjt_functionParam7, &sjt_call2);
#line 20
    sjt_functionParam6 = &sjt_call2;
#line 20
    sjf_debug_writeline(sjt_functionParam6);
#line 21
    sjt_functionParam9 = g_t3;
#line 21
    sjf_type_asstring(sjt_functionParam9, &sjt_call3);
#line 21
    sjt_functionParam8 = &sjt_call3;
#line 21
    sjf_debug_writeline(sjt_functionParam8);
#line 22
    sjt_functionParam11 = g_t4;
#line 22
    sjf_type_asstring(sjt_functionParam11, &sjt_call4);
#line 22
    sjt_functionParam10 = &sjt_call4;
#line 22
    sjf_debug_writeline(sjt_functionParam10);
#line 23
    sjt_functionParam13 = g_t5;
#line 23
    sjf_type_asstring(sjt_functionParam13, &sjt_call5);
#line 23
    sjt_functionParam12 = &sjt_call5;
#line 23
    sjf_debug_writeline(sjt_functionParam12);
#line 24
    sjt_functionParam15 = g_d1;
#line 24
    sjf_type_asstring(sjt_functionParam15, &sjt_call6);
#line 24
    sjt_functionParam14 = &sjt_call6;
#line 24
    sjf_debug_writeline(sjt_functionParam14);
#line 25
    sjt_functionParam17 = g_d2;
#line 25
    sjf_type_asstring(sjt_functionParam17, &sjt_call7);
#line 25
    sjt_functionParam16 = &sjt_call7;
#line 25
    sjf_debug_writeline(sjt_functionParam16);
#line 26
    sjt_functionParam19 = g_d3;
#line 26
    sjf_type_asstring(sjt_functionParam19, &sjt_call8);
#line 26
    sjt_functionParam18 = &sjt_call8;
#line 26
    sjf_debug_writeline(sjt_functionParam18);
#line 27
    sjt_functionParam21 = g_d4;
#line 27
    sjf_type_asstring(sjt_functionParam21, &sjt_call9);
#line 27
    sjt_functionParam20 = &sjt_call9;
#line 27
    sjf_debug_writeline(sjt_functionParam20);
    main_destroy();
    return 0;
}

void main_destroy() {

    if (g_a._refCount == 1) { sjf_class_destroy(&g_a); }
;
    if (g_log._refCount == 1) { sjf_log_destroy(&g_log); }
;
    if (g_log_excludeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_excludeall); }
;
    if (g_log_includeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_includeall); }
;
    if (sjt_call1._refCount == 1) { sjf_string_destroy(&sjt_call1); }
;
    if (sjt_call2._refCount == 1) { sjf_string_destroy(&sjt_call2); }
;
    if (sjt_call3._refCount == 1) { sjf_string_destroy(&sjt_call3); }
;
    if (sjt_call4._refCount == 1) { sjf_string_destroy(&sjt_call4); }
;
    if (sjt_call5._refCount == 1) { sjf_string_destroy(&sjt_call5); }
;
    if (sjt_call6._refCount == 1) { sjf_string_destroy(&sjt_call6); }
;
    if (sjt_call7._refCount == 1) { sjf_string_destroy(&sjt_call7); }
;
    if (sjt_call8._refCount == 1) { sjf_string_destroy(&sjt_call8); }
;
    if (sjt_call9._refCount == 1) { sjf_string_destroy(&sjt_call9); }
;
    if (sjt_value1._refCount == 1) { sjf_hash_type_bool_destroy(&sjt_value1); }
;
}
