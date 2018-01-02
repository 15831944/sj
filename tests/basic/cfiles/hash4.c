#include <lib/common/common.h>

const char* sjg_string1 = " = ";

#define sjs_hash_type_bool_typeId 15
#define sjs_log_typeId 20
#define sji_interface_typeId 21
#define sjs_hash_heap_iface_interface_i32_typeId 22
#define sjs_class_typeId 27
#define cb_heap_iface_interface_i32_void_typeId 32
#define cb_heap_iface_interface_i32_void_heap_typeId 32
#define cb_local_iface_interface_i32_void_typeId 44
#define cb_local_iface_interface_i32_void_heap_typeId 44
#define sjs_array_char_typeId 37
#define sjs_string_typeId 35

typedef struct td_sjs_hash_type_bool sjs_hash_type_bool;
typedef struct td_sjs_log sjs_log;
typedef struct td_sji_interface sji_interface;
typedef struct td_sji_interface_vtbl sji_interface_vtbl;
typedef struct td_sjs_hash_heap_iface_interface_i32 sjs_hash_heap_iface_interface_i32;
typedef struct td_sjs_class sjs_class;
typedef struct td_cb_heap_iface_interface_i32_void cb_heap_iface_interface_i32_void;
typedef struct td_cb_heap_iface_interface_i32_void_heap cb_heap_iface_interface_i32_void_heap;
typedef struct td_cb_local_iface_interface_i32_void cb_local_iface_interface_i32_void;
typedef struct td_cb_local_iface_interface_i32_void_heap cb_local_iface_interface_i32_void_heap;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_string sjs_string;

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

struct td_sji_interface {
    sjs_object* _parent;
    sji_interface_vtbl* _vtbl;
};

struct td_sji_interface_vtbl {
    void (*destroy)(void* _this);
    void (*asinterface)(sjs_object* _this, int typeId, sjs_interface* _return);
    void (*getclasstype)(sjs_object* _parent, int32_t* _return);
    void (*bob)(sjs_object* _parent, int32_t* _return);
    void (*hash)(sjs_object* _parent, uint32_t* _return);
    void (*isequal)(sjs_object* _parent, sji_interface b, bool* _return);
};

struct td_sjs_hash_heap_iface_interface_i32 {
    int _refCount;
    void* _hash;
};

struct td_sjs_class {
    int _refCount;
    int32_t x;
};

struct td_cb_heap_iface_interface_i32_void {
    sjs_object* _parent;
    void (*_cb)(sjs_object* _parent, sji_interface, int32_t);
};

struct td_cb_heap_iface_interface_i32_void_heap {
    cb_heap_iface_interface_i32_void inner;
    void (*_destroy)(sjs_object*);
};

struct td_cb_local_iface_interface_i32_void {
    sjs_object* _parent;
    void (*_cb)(sjs_object* _parent, sji_interface, int32_t);
};

struct td_cb_local_iface_interface_i32_void_heap {
    cb_local_iface_interface_i32_void inner;
    void (*_destroy)(sjs_object*);
};

struct td_sjs_array_char {
    int _refCount;
    int32_t datasize;
    void* data;
    bool isglobal;
    int32_t count;
};

struct td_sjs_string {
    int _refCount;
    int32_t count;
    sjs_array_char data;
    bool _isnullterminated;
};

sji_interface_vtbl sjs_class_interface_vtbl;
#ifndef type_bool_hash_typedef
#define type_bool_hash_typedef
KHASH_INIT_TYPEDEF(type_bool_hash_type, int32_t, bool)
#endif
#ifndef type_bool_hash_typedef
#define type_bool_hash_typedef
KHASH_INIT_TYPEDEF(type_bool_hash_type, int32_t, bool)
#endif
#ifndef heap_iface_interface_i32_hash_typedef
#define heap_iface_interface_i32_hash_typedef
KHASH_INIT_TYPEDEF(heap_iface_interface_i32_hash_type, sji_interface, int32_t)
#endif
#ifndef heap_iface_interface_i32_hash_typedef
#define heap_iface_interface_i32_hash_typedef
KHASH_INIT_TYPEDEF(heap_iface_interface_i32_hash_type, sji_interface, int32_t)
#endif
int32_t g_loglevel_debug;
int32_t g_loglevel_error;
int32_t g_loglevel_fatal;
int32_t g_loglevel_info;
int32_t g_loglevel_trace;
int32_t g_loglevel_warn;

sjs_hash_heap_iface_interface_i32 g_a = { -1 };
int32_option g_b;
int32_t g_clocks_per_sec;
void* g_emptystringdata;
float g_f32_pi;
int32_t g_i32_maxvalue;
int32_t g_i32_minvalue;
sjs_log g_log = { -1 };
sjs_hash_type_bool g_log_excludeall = { -1 };
sjs_hash_type_bool g_log_includeall = { -1 };
uint32_t g_u32_maxvalue;
int32_t result1;
sjs_class* sjt_call1 = 0;
sjs_class* sjt_call2 = 0;
sjs_string sjt_call8 = { -1 };
sjs_class* sjt_cast2 = 0;
sjs_class* sjt_cast4 = 0;
sji_interface sjt_functionParam1 = { 0 };
int32_t sjt_functionParam2;
sjs_string* sjt_functionParam24 = 0;
int32_t sjt_functionParam25;
int32_t sjt_functionParam26;
sji_interface sjt_functionParam3 = { 0 };
cb_heap_iface_interface_i32_void sjt_functionParam4;
sjs_hash_heap_iface_interface_i32* sjt_parent1 = 0;
sjs_hash_heap_iface_interface_i32* sjt_parent3 = 0;
sjs_hash_heap_iface_interface_i32* sjt_parent4 = 0;
sjs_hash_type_bool sjt_value1 = { -1 };

void sjf_array_char(sjs_array_char* _this);
void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_array_char_getat(sjs_array_char* _parent, int32_t index, char* _return);
void sjf_array_char_grow(sjs_array_char* _parent, int32_t newsize, sjs_array_char* _return);
void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newsize, sjs_array_char** _return);
void sjf_array_char_heap(sjs_array_char* _this);
void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item);
void sjf_class(sjs_class* _this);
void sjf_class_as_sji_interface(sjs_class* _this, sji_interface* _return);
void sjf_class_asinterface(sjs_class* _this, int typeId, sjs_interface* _return);
void sjf_class_bob(sjs_class* _parent, int32_t* _return);
void sjf_class_copy(sjs_class* _this, sjs_class* _from);
void sjf_class_destroy(sjs_class* _this);
void sjf_class_getclasstype(sjs_object* _this, int* _return);
void sjf_class_hash(sjs_class* _parent, uint32_t* _return);
void sjf_class_heap(sjs_class* _this);
void sjf_class_isequal(sjs_class* _parent, sji_interface b, bool* _return);
void sjf_debug_writeline(sjs_string* data);
void sjf_hash_heap_iface_interface_i32(sjs_hash_heap_iface_interface_i32* _this);
void sjf_hash_heap_iface_interface_i32__weakptrremovekey(sjs_hash_heap_iface_interface_i32* _parent, sji_interface key);
void sjf_hash_heap_iface_interface_i32__weakptrremovevalue(sjs_hash_heap_iface_interface_i32* _parent, int32_t val);
void sjf_hash_heap_iface_interface_i32_copy(sjs_hash_heap_iface_interface_i32* _this, sjs_hash_heap_iface_interface_i32* _from);
void sjf_hash_heap_iface_interface_i32_destroy(sjs_hash_heap_iface_interface_i32* _this);
void sjf_hash_heap_iface_interface_i32_each(sjs_hash_heap_iface_interface_i32* _parent, cb_heap_iface_interface_i32_void cb);
void sjf_hash_heap_iface_interface_i32_getat(sjs_hash_heap_iface_interface_i32* _parent, sji_interface key, int32_option* _return);
void sjf_hash_heap_iface_interface_i32_heap(sjs_hash_heap_iface_interface_i32* _this);
void sjf_hash_heap_iface_interface_i32_setat(sjs_hash_heap_iface_interface_i32* _parent, sji_interface key, int32_t val);
void sjf_hash_type_bool(sjs_hash_type_bool* _this);
void sjf_hash_type_bool__weakptrremovekey(sjs_hash_type_bool* _parent, int32_t key);
void sjf_hash_type_bool__weakptrremovevalue(sjs_hash_type_bool* _parent, bool val);
void sjf_hash_type_bool_copy(sjs_hash_type_bool* _this, sjs_hash_type_bool* _from);
void sjf_hash_type_bool_destroy(sjs_hash_type_bool* _this);
void sjf_hash_type_bool_heap(sjs_hash_type_bool* _this);
void sjf_i32_asstring(int32_t val, int32_t base, sjs_string* _return);
void sjf_i32_asstring_heap(int32_t val, int32_t base, sjs_string** _return);
void sjf_log(sjs_log* _this);
void sjf_log_copy(sjs_log* _this, sjs_log* _from);
void sjf_log_destroy(sjs_log* _this);
void sjf_log_heap(sjs_log* _this);
void sjf_print(sji_interface k, int32_t v);
void sjf_print_callback(void * _parent, sji_interface k, int32_t v);
void sjf_string(sjs_string* _this);
void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return);
void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string** _return);
void sjf_string_copy(sjs_string* _this, sjs_string* _from);
void sjf_string_destroy(sjs_string* _this);
void sjf_string_getat(sjs_string* _parent, int32_t index, char* _return);
void sjf_string_heap(sjs_string* _this);
void sjf_string_nullterminate(sjs_string* _parent);
void sjf_type_hash(int32_t val, uint32_t* _return);
void sjf_type_isequal(int32_t l, int32_t r, bool* _return);
void sji_interface_hash(sji_interface _parent, uint32_t* _return);
void sji_interface_isequal(sji_interface _parent, sji_interface b, bool* _return);
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
#ifndef heap_iface_interface_i32_hash_function
#define heap_iface_interface_i32_hash_function
#if false
KHASH_INIT_FUNCTION_DEREF(heap_iface_interface_i32_hash_type, sji_interface, int32_t, 1, sji_interface_hash, sji_interface_isequal)
#else
KHASH_INIT_FUNCTION(heap_iface_interface_i32_hash_type, sji_interface, int32_t, 1, sji_interface_hash, sji_interface_isequal)
#endif
#endif
#ifndef heap_iface_interface_i32_hash_function
#define heap_iface_interface_i32_hash_function
#if false
KHASH_INIT_FUNCTION_DEREF(heap_iface_interface_i32_hash_type, sji_interface, int32_t, 1, sji_interface_hash, sji_interface_isequal)
#else
KHASH_INIT_FUNCTION(heap_iface_interface_i32_hash_type, sji_interface, int32_t, 1, sji_interface_hash, sji_interface_isequal)
#endif
#endif
void sjf_array_char(sjs_array_char* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(char) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from) {
#line 1 "lib/common/array.sj"
    _this->datasize = _from->datasize;
#line 1
    _this->data = _from->data;
#line 1
    _this->isglobal = _from->isglobal;
#line 1
    _this->count = _from->count;
#line 325
    _this->data = _from->data;
#line 326
    if (!_this->isglobal && _this->data) {
#line 327
        int* refcount = (int*)_this->data - 1;
#line 328
        *refcount = *refcount + 1;
#line 329
    }
}

void sjf_array_char_destroy(sjs_array_char* _this) {
#line 333 "lib/common/array.sj"
    if (!_this->isglobal && _this->data) {
#line 334
        int* refcount = (int*)_this->data - 1;
#line 335
        *refcount = *refcount - 1;
#line 336
        if (*refcount == 0) {
#line 337
            #if !true && !false
#line 338
            char* p = (char*)_this->data;
#line 339
            for (int i = 0; i < _this->count; i++) {
#line 340
                ;
#line 341
            }
#line 342
            #endif
#line 343
            free(refcount);
#line 344
        }
#line 345
    }
}

void sjf_array_char_getat(sjs_array_char* _parent, int32_t index, char* _return) {
#line 9 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 10
        halt("getAt: out of bounds\n");
#line 11
    }
#line 13
    char* p = (char*)_parent->data;
#line 14
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
return;;       
}

void sjf_array_char_grow(sjs_array_char* _parent, int32_t newsize, sjs_array_char* _return) {
    void* newdata;

#line 135 "lib/common/array.sj"
    newdata = 0;
#line 137
    if (_parent->datasize != newsize) {
#line 138
        if (newsize < _parent->datasize) {
#line 139
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
#line 140
        }
#line 142
        newdata = (int*)(malloc(sizeof(int) + newsize * sizeof(char))) + 1;
#line 143
        int* refcount = (int*)newdata - 1;
#line 144
        *refcount = 1;
#line 146
        if (!_parent->data) {
#line 147
            halt("grow: out of memory\n");
#line 148
        }
#line 150
        char* p = (char*)_parent->data;
#line 151
        char* newp = (char*)newdata;
#line 153
        int count = _parent->count;
#line 155
        #if true
#line 156
        memcpy(newp, p, sizeof(char) * count);
#line 157
        #else
#line 158
        for (int i = 0; i < count; i++) {
#line 159
            #line 136 "lib/common/array.sj"
newp[i] = p[i];
;
#line 160
        }
#line 161
        #endif
#line 162
    }
#line 162
    _return->_refCount = 1;
#line 134
    _return->datasize = newsize;
#line 164
    _return->data = newdata;
#line 4
    _return->isglobal = false;
#line 164
    _return->count = _parent->count;
#line 164
    sjf_array_char(_return);
}

void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newsize, sjs_array_char** _return) {
    void* newdata;

#line 135 "lib/common/array.sj"
    newdata = 0;
#line 137
    if (_parent->datasize != newsize) {
#line 138
        if (newsize < _parent->datasize) {
#line 139
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
#line 140
        }
#line 142
        newdata = (int*)(malloc(sizeof(int) + newsize * sizeof(char))) + 1;
#line 143
        int* refcount = (int*)newdata - 1;
#line 144
        *refcount = 1;
#line 146
        if (!_parent->data) {
#line 147
            halt("grow: out of memory\n");
#line 148
        }
#line 150
        char* p = (char*)_parent->data;
#line 151
        char* newp = (char*)newdata;
#line 153
        int count = _parent->count;
#line 155
        #if true
#line 156
        memcpy(newp, p, sizeof(char) * count);
#line 157
        #else
#line 158
        for (int i = 0; i < count; i++) {
#line 159
            #line 136 "lib/common/array.sj"
newp[i] = p[i];
;
#line 160
        }
#line 161
        #endif
#line 162
    }
#line 162
    (*_return) = (sjs_array_char*)malloc(sizeof(sjs_array_char));
#line 162
    (*_return)->_refCount = 1;
#line 134
    (*_return)->datasize = newsize;
#line 164
    (*_return)->data = newdata;
#line 4
    (*_return)->isglobal = false;
#line 164
    (*_return)->count = _parent->count;
#line 164
    sjf_array_char_heap((*_return));
}

void sjf_array_char_heap(sjs_array_char* _this) {
#line 309 "lib/common/array.sj"
    if (_this->datasize < 0) {
#line 310
        halt("size is less than zero");
#line 311
    }
#line 313
    if (!_this->data) {
#line 314
        _this->data = (int*)malloc(_this->datasize * sizeof(char) + sizeof(int)) + 1;
#line 315
        int* refcount = (int*)_this->data - 1;
#line 316
        *refcount = 1;
#line 317
        if (!_this->data) {
#line 318
            halt("grow: out of memory\n");
#line 319
        }
#line 320
    }
}

void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item) {
#line 36 "lib/common/array.sj"
    if (index != _parent->count) {
#line 37
        halt("initAt: can only initialize last element\n");     
#line 38
    }
#line 39
    if (index >= _parent->datasize || index < 0) {
#line 40
        halt("initAt: out of bounds %d:%d\n", index, _parent->datasize);
#line 41
    }
#line 43
    char* p = (char*)_parent->data;
#line 44
    #line 34 "lib/common/array.sj"
p[index] = item;
;
#line 45
    _parent->count = index + 1;
}

void sjf_class(sjs_class* _this) {
}

void sjf_class_as_sji_interface(sjs_class* _this, sji_interface* _return) {
    _return->_parent = (sjs_object*)_this;
    _return->_vtbl = &sjs_class_interface_vtbl;
}

void sjf_class_asinterface(sjs_class* _this, int typeId, sjs_interface* _return) {
    switch (typeId) {
        case sji_interface_typeId:  {
            sjf_class_as_sji_interface(_this, (sji_interface*)_return);
            break;
        }

        default: {
            _return->_parent = 0;
            break;
        }
    }
}

void sjf_class_bob(sjs_class* _parent, int32_t* _return) {
#line 10 "hash4.sj"
    (*_return) = _parent->x;
}

void sjf_class_copy(sjs_class* _this, sjs_class* _from) {
#line 8 "hash4.sj"
    _this->x = _from->x;
}

void sjf_class_destroy(sjs_class* _this) {
}

void sjf_class_getclasstype(sjs_object* _this, int* _return) {
    *_return = 27;
}

void sjf_class_hash(sjs_class* _parent, uint32_t* _return) {
    int32_t sjt_cast3;

    sjf_class_bob(_parent, &sjt_cast3);
#line 12 "hash4.sj"
    (*_return) = (uint32_t)sjt_cast3;
}

void sjf_class_heap(sjs_class* _this) {
}

void sjf_class_isequal(sjs_class* _parent, sji_interface b, bool* _return) {
    int32_t sjt_capture1;
    int32_t sjt_capture2;
    sji_interface sjt_parent2 = { 0 };

    sjf_class_bob(_parent, &sjt_capture1);
#line 13 "hash4.sj"
    sjt_parent2 = b;
#line 13
    sjt_parent2._vtbl->bob(sjt_parent2._parent, &sjt_capture2);
#line 13
    (*_return) = sjt_capture1 == sjt_capture2;
}

void sjf_debug_writeline(sjs_string* data) {
    sjs_string* sjt_parent7 = 0;

#line 9 "lib/common/debug.sj"
    sjt_parent7 = data;
#line 9
    sjf_string_nullterminate(sjt_parent7);
#line 12
    debugout("%s\n", (char*)data->data.data);
}

void sjf_hash_heap_iface_interface_i32(sjs_hash_heap_iface_interface_i32* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(heap_iface_interface_i32_hash_type);
}

void sjf_hash_heap_iface_interface_i32__weakptrremovekey(sjs_hash_heap_iface_interface_i32* _parent, sji_interface key) {
#line 180 "lib/common/hash.sj"
    #if false
#line 181
    khash_t(heap_iface_interface_i32_hash_type)* p = (khash_t(heap_iface_interface_i32_hash_type)*)_parent->_hash;    
#line 182
    khiter_t k = kh_get(heap_iface_interface_i32_hash_type, p, key);
#line 183
    if (k != kh_end(p)) {
#line 184
        kh_del(heap_iface_interface_i32_hash_type, p, k);
#line 185
    }
#line 186
    #endif
}

void sjf_hash_heap_iface_interface_i32__weakptrremovevalue(sjs_hash_heap_iface_interface_i32* _parent, int32_t val) {
#line 192 "lib/common/hash.sj"
    #if false
#line 193
    khash_t(heap_iface_interface_i32_hash_type)* p = (khash_t(heap_iface_interface_i32_hash_type)*)_parent->_hash;
#line 194
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 195
        if (kh_exist(p, k)) {
#line 196
            int32_t t = kh_value(p, k);
#line 197
            if (t == val) {
#line 198
                kh_del(heap_iface_interface_i32_hash_type, p, k);
#line 199
            }
#line 200
        }
#line 201
    }
#line 202
    #endif
}

void sjf_hash_heap_iface_interface_i32_copy(sjs_hash_heap_iface_interface_i32* _this, sjs_hash_heap_iface_interface_i32* _from) {
#line 230 "lib/common/hash.sj"
    _this->_hash = _from->_hash;
#line 231
    khash_t(heap_iface_interface_i32_hash_type)* p = (khash_t(heap_iface_interface_i32_hash_type)*)_this->_hash;
#line 232
    p->refcount++;
}

void sjf_hash_heap_iface_interface_i32_destroy(sjs_hash_heap_iface_interface_i32* _this) {
#line 236 "lib/common/hash.sj"
    khash_t(heap_iface_interface_i32_hash_type)* p = (khash_t(heap_iface_interface_i32_hash_type)*)_this->_hash;
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
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_heap_iface_interface_i32__weakptrremovekey };
#line 244
                weakptr_cb_remove(kh_key(p, k)._parent, cb);
#line 245
                #else
#line 246
                if (kh_key(p, k)._parent != 0) {
    kh_key(p, k)._parent->_refCount--;
    if (kh_key(p, k)._parent->_refCount <= 0) {
        kh_key(p, k)._vtbl->destroy(kh_key(p, k)._parent);
        free(kh_key(p, k)._parent);
    }
}
;
#line 247
                #endif
#line 249
                #if false
#line 250
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_heap_iface_interface_i32__weakptrremovevalue };
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
        kh_destroy(heap_iface_interface_i32_hash_type, _this->_hash);
#line 258
    }
}

void sjf_hash_heap_iface_interface_i32_each(sjs_hash_heap_iface_interface_i32* _parent, cb_heap_iface_interface_i32_void cb) {
#line 98 "lib/common/hash.sj"
    khash_t(heap_iface_interface_i32_hash_type)* p = (khash_t(heap_iface_interface_i32_hash_type)*)_parent->_hash;
#line 99
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
#line 100
        if (kh_exist(p, k)) {
#line 101
            cb._cb(
#line 102
            cb._parent, 
#line 103
            #if false
#line 104
            &kh_key(p, k), 
#line 105
            #else
#line 106
            kh_key(p, k), 
#line 107
            #endif
#line 109
            #if false
#line 110
            &kh_value(p, k)
#line 111
            #else
#line 112
            kh_value(p, k)
#line 113
            #endif
#line 114
            );
#line 115
        }
#line 116
    }
}

void sjf_hash_heap_iface_interface_i32_getat(sjs_hash_heap_iface_interface_i32* _parent, sji_interface key, int32_option* _return) {
#line 23 "lib/common/hash.sj"
    khash_t(heap_iface_interface_i32_hash_type)* p = (khash_t(heap_iface_interface_i32_hash_type)*)_parent->_hash;
#line 25
    #if false
#line 26
    khiter_t k = kh_get(heap_iface_interface_i32_hash_type, p, *key);
#line 27
    #else
#line 28
    khiter_t k = kh_get(heap_iface_interface_i32_hash_type, p, key);
#line 29
    #endif
#line 31
    if (k == kh_end(p)) {
#line 32
        #line 22 "lib/common/hash.sj"
(*_return) = int32_empty;
return;
#line 33
    }
#line 34
    #line 22 "lib/common/hash.sj"
_return->isvalid = true;
#line 22
_return->value = kh_val(p, k);
return;;
}

void sjf_hash_heap_iface_interface_i32_heap(sjs_hash_heap_iface_interface_i32* _this) {
#line 225 "lib/common/hash.sj"
    _this->_hash = kh_init(heap_iface_interface_i32_hash_type);
}

void sjf_hash_heap_iface_interface_i32_setat(sjs_hash_heap_iface_interface_i32* _parent, sji_interface key, int32_t val) {
#line 40 "lib/common/hash.sj"
    khash_t(heap_iface_interface_i32_hash_type)* p = (khash_t(heap_iface_interface_i32_hash_type)*)_parent->_hash;
#line 42
    #if false
#line 43
    khiter_t k = kh_get(heap_iface_interface_i32_hash_type, p, *key);
#line 44
    #else
#line 45
    khiter_t k = kh_get(heap_iface_interface_i32_hash_type, p, key);
#line 46
    #endif
#line 48
    if (k != kh_end(p)) {            
#line 49
    ;
#line 50
}
#line 52
int ret;
#line 53
#if false
#line 54
k = kh_put(heap_iface_interface_i32_hash_type, _parent->_hash, *key, &ret);
#line 55
#else
#line 56
k = kh_put(heap_iface_interface_i32_hash_type, _parent->_hash, key, &ret);
#line 57
#endif
#line 59
if (!ret) kh_del(heap_iface_interface_i32_hash_type, p, k);
#line 61
#if false
#line 62
delete_cb cb = { _parent, (void(*)(void*, void*))sjf_hash_heap_iface_interface_i32__weakptrremovekey };
#line 63
weakptr_cb_add(key._parent, cb);
#line 64
#else
#line 65
sji_interface t;
#line 66
#line 38 "lib/common/hash.sj"
t = key;
if (t._parent != 0) {
    t._parent->_refCount++;
}
;
#line 67
#endif
#line 69
#if false
#line 70
delete_cb cb = { _parent, (void(*)(void*, void*))sjf_hash_heap_iface_interface_i32__weakptrremovevalue };
#line 71
weakptr_cb_add(val, cb);
#line 72
kh_val(p, k) = val;
#line 73
#else
#line 74
#line 38 "lib/common/hash.sj"
kh_val(p, k) = val;
;
#line 75
#endif
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

void sjf_i32_asstring(int32_t val, int32_t base, sjs_string* _return) {
    int32_t count;
    void* data;

#line 23 "lib/common/i32.sj"
    count = 0;
#line 24
    data = 0;
#line 26
    data = (int*)malloc(sizeof(int) + sizeof(char) * 256) + 1;
#line 27
    int* refcount = (int*)data - 1;
#line 28
    *refcount = 1;
#line 30
    char *tmp = (char*)data + 128;
#line 31
    char *tp = (char*)data + 128;
#line 32
    int i;
#line 33
    unsigned v;
#line 35
    int sign = (base == 10 && val < 0);    
#line 36
    if (sign)
#line 37
    v = -val;
#line 38
    else
#line 39
    v = (unsigned)val;
#line 41
    while (v || tp == tmp)
#line 42
    {
#line 43
        i = v % base;
#line 44
        v /= base; // v/=base uses less CPU clocks than v=v/base does
#line 45
        if (i < 10)
#line 46
        *tp++ = i + '0';
#line 47
        else
#line 48
        *tp++ = i + 'a' - 10;
#line 49
    }
#line 51
    int len = tp - tmp;
#line 53
    char* sp = (char*)data;
#line 54
    if (sign) 
#line 55
    {
#line 56
        *sp++ = '-';
#line 57
        len++;
#line 58
    }
#line 60
    while (tp > tmp)
#line 61
    *sp++ = *--tp;
#line 63
    count = len;
#line 63
    _return->_refCount = 1;
#line 65
    _return->count = count;
#line 65
    _return->data._refCount = 1;
#line 65
    _return->data.datasize = 256;
#line 65
    _return->data.data = data;
#line 4 "lib/common/array.sj"
    _return->data.isglobal = false;
#line 65 "lib/common/i32.sj"
    _return->data.count = count;
#line 65
    sjf_array_char(&_return->data);
#line 14 "lib/common/string.sj"
    _return->_isnullterminated = false;
#line 14
    sjf_string(_return);
}

void sjf_i32_asstring_heap(int32_t val, int32_t base, sjs_string** _return) {
    int32_t count;
    void* data;

#line 23 "lib/common/i32.sj"
    count = 0;
#line 24
    data = 0;
#line 26
    data = (int*)malloc(sizeof(int) + sizeof(char) * 256) + 1;
#line 27
    int* refcount = (int*)data - 1;
#line 28
    *refcount = 1;
#line 30
    char *tmp = (char*)data + 128;
#line 31
    char *tp = (char*)data + 128;
#line 32
    int i;
#line 33
    unsigned v;
#line 35
    int sign = (base == 10 && val < 0);    
#line 36
    if (sign)
#line 37
    v = -val;
#line 38
    else
#line 39
    v = (unsigned)val;
#line 41
    while (v || tp == tmp)
#line 42
    {
#line 43
        i = v % base;
#line 44
        v /= base; // v/=base uses less CPU clocks than v=v/base does
#line 45
        if (i < 10)
#line 46
        *tp++ = i + '0';
#line 47
        else
#line 48
        *tp++ = i + 'a' - 10;
#line 49
    }
#line 51
    int len = tp - tmp;
#line 53
    char* sp = (char*)data;
#line 54
    if (sign) 
#line 55
    {
#line 56
        *sp++ = '-';
#line 57
        len++;
#line 58
    }
#line 60
    while (tp > tmp)
#line 61
    *sp++ = *--tp;
#line 63
    count = len;
#line 63
    (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
#line 63
    (*_return)->_refCount = 1;
#line 65
    (*_return)->count = count;
#line 65
    (*_return)->data._refCount = 1;
#line 65
    (*_return)->data.datasize = 256;
#line 65
    (*_return)->data.data = data;
#line 4 "lib/common/array.sj"
    (*_return)->data.isglobal = false;
#line 65 "lib/common/i32.sj"
    (*_return)->data.count = count;
#line 65
    sjf_array_char(&(*_return)->data);
#line 14 "lib/common/string.sj"
    (*_return)->_isnullterminated = false;
#line 14
    sjf_string_heap((*_return));
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

void sjf_print(sji_interface k, int32_t v) {
    sjs_string sjt_call3 = { -1 };
    sjs_string sjt_call4 = { -1 };
    sjs_string sjt_call5 = { -1 };
    sjs_string sjt_call6 = { -1 };
    sjs_string sjt_call7 = { -1 };
    int32_t sjt_functionParam18;
    int32_t sjt_functionParam19;
    sjs_string* sjt_functionParam20 = 0;
    sjs_string* sjt_functionParam21 = 0;
    int32_t sjt_functionParam22;
    int32_t sjt_functionParam23;
    sjs_string* sjt_functionParam8 = 0;
    sjs_string* sjt_parent15 = 0;
    sjs_string* sjt_parent16 = 0;
    sji_interface sjt_parent17 = { 0 };

#line 23 "hash4.sj"
    sjt_parent17 = k;
#line 24
    sjt_parent17._vtbl->bob(sjt_parent17._parent, &sjt_functionParam18);
#line 22 "lib/common/i32.sj"
    sjt_functionParam19 = 10;
#line 22
    sjf_i32_asstring(sjt_functionParam18, sjt_functionParam19, &sjt_call5);
#line 24 "hash4.sj"
    sjt_parent16 = &sjt_call5;
#line 24
    sjt_call6._refCount = 1;
#line 24
    sjt_call6.count = 3;
#line 24
    sjt_call6.data._refCount = 1;
#line 24
    sjt_call6.data.datasize = 3;
#line 24
    sjt_call6.data.data = (void*)sjg_string1;
#line 24
    sjt_call6.data.isglobal = true;
#line 24
    sjt_call6.data.count = 3;
#line 24
    sjf_array_char(&sjt_call6.data);
#line 14 "lib/common/string.sj"
    sjt_call6._isnullterminated = false;
#line 14
    sjf_string(&sjt_call6);
#line 24 "hash4.sj"
    sjt_functionParam20 = &sjt_call6;
#line 24
    sjf_string_add(sjt_parent16, sjt_functionParam20, &sjt_call4);
#line 24
    sjt_parent15 = &sjt_call4;
#line 23
    sjt_functionParam22 = v;
#line 22 "lib/common/i32.sj"
    sjt_functionParam23 = 10;
#line 22
    sjf_i32_asstring(sjt_functionParam22, sjt_functionParam23, &sjt_call7);
#line 24 "hash4.sj"
    sjt_functionParam21 = &sjt_call7;
#line 24
    sjf_string_add(sjt_parent15, sjt_functionParam21, &sjt_call3);
#line 24
    sjt_functionParam8 = &sjt_call3;
#line 24
    sjf_debug_writeline(sjt_functionParam8);

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
}

void sjf_print_callback(void * _parent, sji_interface k, int32_t v) {
    sjf_print(k, v);
}

void sjf_string(sjs_string* _this) {
}

void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return) {
    sjs_array_char newdata = { -1 };

    if (item->count == 0) {
        _return->_refCount = 1;
#line 18 "lib/common/string.sj"
        _return->count = _parent->count;
#line 18
        _return->data._refCount = 1;
#line 18
        sjf_array_char_copy(&_return->data, &_parent->data);
#line 14
        _return->_isnullterminated = false;
#line 14
        sjf_string(_return);
    } else {
        int32_t i;
        int32_t newcount;
        int32_t sjt_forEnd1;
        int32_t sjt_forStart1;

        if ((_parent->count + item->count) > (&_parent->data)->datasize) {
            int32_t sjt_functionParam9;
            sjs_array_char* sjt_parent8 = 0;

#line 134 "lib/common/array.sj"
            sjt_parent8 = &_parent->data;
#line 21 "lib/common/string.sj"
            sjt_functionParam9 = ((((_parent->count + item->count) - 1) / 256) + 1) * 256;
#line 21
            sjf_array_char_grow(sjt_parent8, sjt_functionParam9, &newdata);
        } else {
            newdata._refCount = 1;
#line 20 "lib/common/string.sj"
            sjf_array_char_copy(&newdata, &_parent->data);
        }

#line 25 "lib/common/string.sj"
        newcount = _parent->count;
#line 27
        sjt_forStart1 = 0;
#line 27
        sjt_forEnd1 = item->count;
#line 27
        i = sjt_forStart1;
        while (i < sjt_forEnd1) {
            int32_t sjt_functionParam10;
            char sjt_functionParam11;
            int32_t sjt_functionParam13;
            sjs_string* sjt_parent11 = 0;
            sjs_array_char* sjt_parent9 = 0;

#line 34 "lib/common/array.sj"
            sjt_parent9 = &newdata;
#line 28 "lib/common/string.sj"
            sjt_functionParam10 = newcount;
#line 16
            sjt_parent11 = item;
#line 27
            sjt_functionParam13 = i;
#line 27
            sjf_string_getat(sjt_parent11, sjt_functionParam13, &sjt_functionParam11);
#line 27
            sjf_array_char_initat(sjt_parent9, sjt_functionParam10, sjt_functionParam11);
#line 29
            newcount = newcount + 1;
#line 27
            i++;
        }

#line 27
        _return->_refCount = 1;
#line 32
        _return->count = newcount;
#line 32
        _return->data._refCount = 1;
#line 32
        sjf_array_char_copy(&_return->data, &newdata);
#line 14
        _return->_isnullterminated = false;
#line 14
        sjf_string(_return);
    }

    if (newdata._refCount == 1) { sjf_array_char_destroy(&newdata); }
;
}

void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string** _return) {
    sjs_array_char newdata = { -1 };

    if (item->count == 0) {
        (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
        (*_return)->_refCount = 1;
#line 18 "lib/common/string.sj"
        (*_return)->count = _parent->count;
#line 18
        (*_return)->data._refCount = 1;
#line 18
        sjf_array_char_copy(&(*_return)->data, &_parent->data);
#line 14
        (*_return)->_isnullterminated = false;
#line 14
        sjf_string_heap((*_return));
    } else {
        int32_t i;
        int32_t newcount;
        int32_t sjt_forEnd2;
        int32_t sjt_forStart2;

        if ((_parent->count + item->count) > (&_parent->data)->datasize) {
            int32_t sjt_functionParam14;
            sjs_array_char* sjt_parent12 = 0;

#line 134 "lib/common/array.sj"
            sjt_parent12 = &_parent->data;
#line 21 "lib/common/string.sj"
            sjt_functionParam14 = ((((_parent->count + item->count) - 1) / 256) + 1) * 256;
#line 21
            sjf_array_char_grow(sjt_parent12, sjt_functionParam14, &newdata);
        } else {
            newdata._refCount = 1;
#line 20 "lib/common/string.sj"
            sjf_array_char_copy(&newdata, &_parent->data);
        }

#line 25 "lib/common/string.sj"
        newcount = _parent->count;
#line 27
        sjt_forStart2 = 0;
#line 27
        sjt_forEnd2 = item->count;
#line 27
        i = sjt_forStart2;
        while (i < sjt_forEnd2) {
            int32_t sjt_functionParam15;
            char sjt_functionParam16;
            int32_t sjt_functionParam17;
            sjs_array_char* sjt_parent13 = 0;
            sjs_string* sjt_parent14 = 0;

#line 34 "lib/common/array.sj"
            sjt_parent13 = &newdata;
#line 28 "lib/common/string.sj"
            sjt_functionParam15 = newcount;
#line 16
            sjt_parent14 = item;
#line 27
            sjt_functionParam17 = i;
#line 27
            sjf_string_getat(sjt_parent14, sjt_functionParam17, &sjt_functionParam16);
#line 27
            sjf_array_char_initat(sjt_parent13, sjt_functionParam15, sjt_functionParam16);
#line 29
            newcount = newcount + 1;
#line 27
            i++;
        }

#line 27
        (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
#line 27
        (*_return)->_refCount = 1;
#line 32
        (*_return)->count = newcount;
#line 32
        (*_return)->data._refCount = 1;
#line 32
        sjf_array_char_copy(&(*_return)->data, &newdata);
#line 14
        (*_return)->_isnullterminated = false;
#line 14
        sjf_string_heap((*_return));
    }

    if (newdata._refCount == 1) { sjf_array_char_destroy(&newdata); }
;
}

void sjf_string_copy(sjs_string* _this, sjs_string* _from) {
#line 6 "lib/common/string.sj"
    _this->count = _from->count;
#line 6
    _this->data._refCount = 1;
#line 6
    sjf_array_char_copy(&_this->data, &_from->data);
#line 6
    _this->_isnullterminated = _from->_isnullterminated;
}

void sjf_string_destroy(sjs_string* _this) {
    if (_this->data._refCount == 1) { sjf_array_char_destroy(&_this->data); }
;
}

void sjf_string_getat(sjs_string* _parent, int32_t index, char* _return) {
    int32_t sjt_functionParam12;
    sjs_array_char* sjt_parent10 = 0;

#line 7 "lib/common/array.sj"
    sjt_parent10 = &_parent->data;
#line 36 "lib/common/string.sj"
    sjt_functionParam12 = index;
#line 36
    sjf_array_char_getat(sjt_parent10, sjt_functionParam12, _return);
}

void sjf_string_heap(sjs_string* _this) {
}

void sjf_string_nullterminate(sjs_string* _parent) {
    bool result2;
    bool result3;
    sjs_array_char sjt_funcold1 = { -1 };

#line 73 "lib/common/string.sj"
    result2 = !(&_parent->data)->isglobal;
#line 73
    result3 = !_parent->_isnullterminated;
    if (result2 || result3) {
        int32_t sjt_functionParam6;
        char sjt_functionParam7;
        sjs_array_char* sjt_parent6 = 0;

        if ((_parent->count + 1) > (&_parent->data)->datasize) {
            int32_t sjt_functionParam5;
            sjs_array_char* sjt_parent5 = 0;

            sjt_funcold1._refCount = 1;
#line 134 "lib/common/array.sj"
            sjf_array_char_copy(&sjt_funcold1, &_parent->data);
#line 134
            sjt_parent5 = &_parent->data;
#line 75 "lib/common/string.sj"
            sjt_functionParam5 = _parent->count + 1;
#line 75
            sjf_array_char_grow(sjt_parent5, sjt_functionParam5, &sjt_funcold1);
#line 75
            if (_parent->data._refCount == 1) { sjf_array_char_destroy(&_parent->data); }
;
#line 134 "lib/common/array.sj"
            sjf_array_char_copy(&_parent->data, &sjt_funcold1);
        }

#line 34 "lib/common/array.sj"
        sjt_parent6 = &_parent->data;
#line 77 "lib/common/string.sj"
        sjt_functionParam6 = _parent->count;
#line 77
        sjt_functionParam7 = '\0';
#line 77
        sjf_array_char_initat(sjt_parent6, sjt_functionParam6, sjt_functionParam7);
#line 78
        _parent->_isnullterminated = true;
    }

    if (sjt_funcold1._refCount == 1) { sjf_array_char_destroy(&sjt_funcold1); }
;
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

void sji_interface_hash(sji_interface _parent, uint32_t* _return) {
    _parent._vtbl->hash(_parent._parent, _return);
}

void sji_interface_isequal(sji_interface _parent, sji_interface b, bool* _return) {
    _parent._vtbl->isequal(_parent._parent, b, _return);
}

int main(int argc, char** argv) {
    sjs_class_interface_vtbl.destroy = (void(*)(void*))sjf_class_destroy;
    sjs_class_interface_vtbl.asinterface = (void(*)(sjs_object*,int,sjs_interface*))sjf_class_asinterface;
    sjs_class_interface_vtbl.getclasstype = (void(*)(sjs_object*,int*))sjf_class_getclasstype;
    sjs_class_interface_vtbl.bob = (void(*)(sjs_object*, int32_t*))sjf_class_bob;
    sjs_class_interface_vtbl.hash = (void(*)(sjs_object*, uint32_t*))sjf_class_hash;
    sjs_class_interface_vtbl.isequal = (void(*)(sjs_object*,sji_interface, bool*))sjf_class_isequal;
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
#line 9
    sjf_hash_heap_iface_interface_i32(&g_a);
#line 38 "lib/common/hash.sj"
    sjt_parent1 = &g_a;
#line 38
    sjt_call1 = (sjs_class*)malloc(sizeof(sjs_class));
#line 38
    sjt_call1->_refCount = 1;
#line 17 "hash4.sj"
    sjt_call1->x = 32;
#line 17
    sjf_class_heap(sjt_call1);
#line 17
    sjt_cast2 = sjt_call1;
#line 2
    sjf_class_as_sji_interface(sjt_cast2, &sjt_functionParam1);
    if (sjt_functionParam1._parent != 0) {
        sjt_functionParam1._parent->_refCount++;
    }

#line 17
    sjt_functionParam2 = 1;
#line 17
    sjf_hash_heap_iface_interface_i32_setat(sjt_parent1, sjt_functionParam1, sjt_functionParam2);
#line 21 "lib/common/hash.sj"
    sjt_parent3 = &g_a;
#line 21
    sjt_call2 = (sjs_class*)malloc(sizeof(sjs_class));
#line 21
    sjt_call2->_refCount = 1;
#line 18 "hash4.sj"
    sjt_call2->x = 1;
#line 18
    sjf_class_heap(sjt_call2);
#line 18
    sjt_cast4 = sjt_call2;
#line 2
    sjf_class_as_sji_interface(sjt_cast4, &sjt_functionParam3);
    if (sjt_functionParam3._parent != 0) {
        sjt_functionParam3._parent->_refCount++;
    }

#line 2
    sjf_hash_heap_iface_interface_i32_getat(sjt_parent3, sjt_functionParam3, &g_b);
#line 96 "lib/common/hash.sj"
    sjt_parent4 = &g_a;
#line 20 "hash4.sj"
    sjt_functionParam4._parent = (sjs_object*)1;
#line 20
    sjt_functionParam4._cb = (void(*)(sjs_object*,sji_interface,int32_t))sjf_print_callback;
#line 20
    sjf_hash_heap_iface_interface_i32_each(sjt_parent4, sjt_functionParam4);
    if (g_b.isvalid) {
        int32_option sjt_getValue1;

#line 21 "hash4.sj"
        sjt_getValue1 = g_b;
#line 21
        sjt_functionParam25 = sjt_getValue1.value;
    } else {
        int32_t result4;

#line 21 "hash4.sj"
        result4 = -1;
#line 21
        sjt_functionParam25 = result4;
    }

#line 22 "lib/common/i32.sj"
    sjt_functionParam26 = 10;
#line 22
    sjf_i32_asstring(sjt_functionParam25, sjt_functionParam26, &sjt_call8);
#line 21 "hash4.sj"
    sjt_functionParam24 = &sjt_call8;
#line 21
    sjf_debug_writeline(sjt_functionParam24);
    main_destroy();
    return 0;
}

void main_destroy() {

    sjt_call1->_refCount--;
    if (sjt_call1->_refCount <= 0) {
        weakptr_release(sjt_call1);
        sjf_class_destroy(sjt_call1);
        free(sjt_call1);
    }
    sjt_call2->_refCount--;
    if (sjt_call2->_refCount <= 0) {
        weakptr_release(sjt_call2);
        sjf_class_destroy(sjt_call2);
        free(sjt_call2);
    }
    if (sjt_functionParam1._parent != 0) {
        sjt_functionParam1._parent->_refCount--;
        if (sjt_functionParam1._parent->_refCount <= 0) {
            sjt_functionParam1._vtbl->destroy(sjt_functionParam1._parent);
            free(sjt_functionParam1._parent);
        }
    }
    if (sjt_functionParam3._parent != 0) {
        sjt_functionParam3._parent->_refCount--;
        if (sjt_functionParam3._parent->_refCount <= 0) {
            sjt_functionParam3._vtbl->destroy(sjt_functionParam3._parent);
            free(sjt_functionParam3._parent);
        }
    }
    if (g_a._refCount == 1) { sjf_hash_heap_iface_interface_i32_destroy(&g_a); }
;
    if (g_log._refCount == 1) { sjf_log_destroy(&g_log); }
;
    if (g_log_excludeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_excludeall); }
;
    if (g_log_includeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_includeall); }
;
    if (sjt_call8._refCount == 1) { sjf_string_destroy(&sjt_call8); }
;
    if (sjt_value1._refCount == 1) { sjf_hash_type_bool_destroy(&sjt_value1); }
;
}