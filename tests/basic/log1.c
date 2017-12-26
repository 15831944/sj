#ifdef __GNUC__
#if __x86_64__ 
#define __LINUX__
#define __64__
#elif __i386__ 
#define __LINUX__
#define __32__
#else
#define __LINUX__
#define __32__
#endif
#elif _MSC_VER
#if _WIN64 
#define __WINDOWS__
#define __64__
#elif _WIN32 
#define __WINDOWS__
#define __32__
#else
#error "WINDOWS UNSUPPORTED BITS"
#endif
#else
#error "UNKNOWN PLATFORM"
#endif
#include <lib/common/khash.h>
#include <lib/common/value_option_types.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __WINDOWS__
#include <windows.h>
#endif

typedef struct td_delete_cb delete_cb;
typedef struct td_delete_cb_list delete_cb_list;
const char* sjg_string1 = "[";
const char* sjg_string10 = "hello";
const char* sjg_string2 = "trace";
const char* sjg_string3 = "debug";
const char* sjg_string4 = "info";
const char* sjg_string5 = "warn";
const char* sjg_string6 = "error";
const char* sjg_string7 = "fatal";
const char* sjg_string8 = "";
const char* sjg_string9 = "] ";

struct td_delete_cb {
    void* _parent;
    void (*_cb)(void* _parent, void* object);
};
struct td_delete_cb_list {
    int size;
    delete_cb cb[5];
    delete_cb_list* next;
};
#define sjs_object_typeId 1
#define sjs_interface_typeId 2
#define sjs_log_typeId 3
#define sjs_array_char_typeId 4
#define sjs_string_typeId 5
#define cb_string_heap_string_typeId 6
#define cb_string_heap_string_heap_typeId 7
#define sjs_lambda1_typeId 8

typedef struct td_sjs_object sjs_object;
typedef struct td_sjs_interface sjs_interface;
typedef struct td_sjs_log sjs_log;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_string sjs_string;
typedef struct td_cb_string_heap_string cb_string_heap_string;
typedef struct td_cb_string_heap_string_heap cb_string_heap_string_heap;
typedef struct td_sjs_lambda1 sjs_lambda1;

struct td_sjs_object {
    intptr_t _refCount;
};

struct td_sjs_interface {
    sjs_object* _parent;
    void* _vtbl;
};

struct td_sjs_log {
    int _refCount;
    int32_t minlevel;
};

struct td_sjs_array_char {
    int _refCount;
    int32_t datasize;
    void* data;
    bool _isglobal;
    int32_t count;
};

struct td_sjs_string {
    int _refCount;
    int32_t count;
    sjs_array_char data;
};

struct td_cb_string_heap_string {
    sjs_object* _parent;
    void (*_cb)(sjs_object* _parent, sjs_string* _return);
    void (*_cb_heap)(sjs_object* _parent, sjs_string** _return);
};

struct td_cb_string_heap_string_heap {
    cb_string_heap_string inner;
    void (*_destroy)(sjs_object*);
};

struct td_sjs_lambda1 {
    int _refCount;
};

void debugout(const char * format, ...);
void debugoutv(const char * format, va_list args);
void halt(const char * format, ...);
void ptr_hash(void* p, uint32_t* result);
void ptr_isequal(void *p1, void* p2, bool* result);
void delete_cb_list_free(delete_cb_list* d);
void delete_cb_list_add(delete_cb_list* d, delete_cb cb);
void delete_cb_list_remove(delete_cb_list* d, delete_cb cb);
void delete_cb_list_invoke(delete_cb_list* d, void* p);
void weakptr_init();
void weakptr_release(void* v);
void weakptr_cb_add(void* v, delete_cb cb);
void weakptr_cb_remove(void* v, delete_cb cb);
void weakptr_clear(void* parent, void* v);
void ptr_init();
void ptr_retain(void* ptr);
bool ptr_release(void* ptr);
#include <lib/common/object.h>
int32_t sjv_loglevel_debug;
int32_t sjv_loglevel_error;
int32_t sjv_loglevel_fatal;
int32_t sjv_loglevel_info;
int32_t sjv_loglevel_trace;
int32_t sjv_loglevel_warn;

int32_t result1;
sjs_lambda1 sjt_call8 = { -1 };
sjs_log* sjt_dot1 = 0;
cb_string_heap_string sjt_functionParam27;
int32_t sjt_math1;
int32_t sjt_math2;
int32_t sjt_negate1;
sjs_log* sjt_parent17 = 0;
void* sjv_emptystringdata;
float sjv_f32_pi;
int32_t sjv_i32_maxvalue;
int32_t sjv_i32_minvalue;
sjs_log sjv_log = { -1 };
uint32_t sjv_u32_maxvalue;

void sjf_array_char(sjs_array_char* _this);
void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_array_char_getat(sjs_array_char* _parent, int32_t index, char* _return);
void sjf_array_char_grow(sjs_array_char* _parent, int32_t newsize, sjs_array_char* _return);
void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newsize, sjs_array_char** _return);
void sjf_array_char_heap(sjs_array_char* _this);
void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item);
void sjf_array_char_setat(sjs_array_char* _parent, int32_t index, char item);
void sjf_debug_writeline(sjs_string* data);
void sjf_lambda1(sjs_lambda1* _this);
void sjf_lambda1_copy(sjs_lambda1* _this, sjs_lambda1* _from);
void sjf_lambda1_destroy(sjs_lambda1* _this);
void sjf_lambda1_heap(sjs_lambda1* _this);
void sjf_lambda1_invoke(sjs_lambda1* _parent, sjs_string* _return);
void sjf_lambda1_invoke_heap(sjs_lambda1* _parent, sjs_string** _return);
void sjf_log(sjs_log* _this);
void sjf_log__write(sjs_log* _parent, int32_t level, cb_string_heap_string cb);
void sjf_log_copy(sjs_log* _this, sjs_log* _from);
void sjf_log_destroy(sjs_log* _this);
void sjf_log_heap(sjs_log* _this);
void sjf_log_info(sjs_log* _parent, cb_string_heap_string cb);
void sjf_loglevel_asstring(int32_t e, sjs_string* _return);
void sjf_string(sjs_string* _this);
void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return);
void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string** _return);
void sjf_string_copy(sjs_string* _this, sjs_string* _from);
void sjf_string_destroy(sjs_string* _this);
void sjf_string_getat(sjs_string* _parent, int32_t index, char* _return);
void sjf_string_heap(sjs_string* _this);
void main_destroy(void);

void debugout(const char * format, ...) {
    va_list args;
    va_start(args, format);
    debugoutv(format, args);
    va_end(args);
}
void debugoutv(const char * format, va_list args) {
    #ifdef _WINDOWS
    char text[1024];
    vsnprintf(text, sizeof(text), format, args);
    OutputDebugStringA(text);
    #else
    vfprintf(stderr, format, args);
    #endif
}
void halt(const char * format, ...) {
    va_list args;
    va_start(args, format);
    debugoutv(format, args);
    va_end(args);
    #ifdef _DEBUG
    printf("\npress return to end\n");
    getchar();
    #endif
    exit(-1);
}
void ptr_hash(void* p, uint32_t* result) {
    #ifdef __32__
    *result = kh_int_hash_func((uintptr_t)p);
    #else
    *result = kh_int64_hash_func((uintptr_t)p);
    #endif
}
void ptr_isequal(void *p1, void* p2, bool* result) {
    *result = (p1 == p2);
}
void delete_cb_list_free(delete_cb_list* d) {
    if (d->next) {
        delete_cb_list_free(d->next);
    }
    free(d);
}
void delete_cb_list_add(delete_cb_list* d, delete_cb cb) {
    if (d->size < 5) {
        d->cb[d->size] = cb;
        d->size++;
    }
    else {
        if (!d->next) {
            d->next = (delete_cb_list*)malloc(sizeof(delete_cb_list));
        }
        delete_cb_list_add(d->next, cb);
    }
}
void delete_cb_list_remove(delete_cb_list* d, delete_cb cb) {
    for (int i = 0; i < d->size; i++) {
        if (d->cb[i]._parent == cb._parent && d->cb[i]._cb == cb._cb) {
            for (int j = i; j < d->size - 1; j++) {
                d->cb[j] = d->cb[j + 1];
            }
            d->size--;
        }
    }
    if (d->next) {
        delete_cb_list_remove(d->next, cb);
    }
}
void delete_cb_list_invoke(delete_cb_list* d, void* p) {
    for (int i = 0; i < d->size; i++) {
        d->cb[i]._cb(d->cb[i]._parent, p);
    }
    if (d->next) {
        delete_cb_list_invoke(d->next, p);
    }
}
KHASH_INIT_TYPEDEF(weakptr_hashtable_type, void*, delete_cb_list)
KHASH_INIT_FUNCTION(weakptr_hashtable_type, void*, delete_cb_list, 1, ptr_hash, ptr_isequal)
khash_t(weakptr_hashtable_type)* weakptr_hashtable;
void weakptr_init() {
    weakptr_hashtable = kh_init(weakptr_hashtable_type);
}
void weakptr_release(void* v) {
    khiter_t k = kh_get(weakptr_hashtable_type, weakptr_hashtable, v);
    if (k != kh_end(weakptr_hashtable)) {
        delete_cb_list* d = &kh_value(weakptr_hashtable, k);
        delete_cb_list_invoke(d, v);
        if (d->next) {
            delete_cb_list_free(d->next);
        }
        kh_del(weakptr_hashtable_type, weakptr_hashtable, k);
    }
}
void weakptr_cb_add(void* v, delete_cb cb) {
    delete_cb_list* d;
    khiter_t k = kh_get(weakptr_hashtable_type, weakptr_hashtable, v);
    if (k == kh_end(weakptr_hashtable)) {
        int ret;
        khiter_t k = kh_put(weakptr_hashtable_type, weakptr_hashtable, v, &ret);
        if (!ret) kh_del(weakptr_hashtable_type, weakptr_hashtable, k);
        d = &kh_value(weakptr_hashtable, k);
        d->size = 0;
        d->next = 0;
    }
    else {
        d = &kh_value(weakptr_hashtable, k);
    }
    delete_cb_list_add(d, cb);
}
void weakptr_cb_remove(void* v, delete_cb cb) {
    khiter_t k = kh_get(weakptr_hashtable_type, weakptr_hashtable, v);
    if (k != kh_end(weakptr_hashtable)) {
        delete_cb_list* d = &kh_value(weakptr_hashtable, k);
        delete_cb_list_remove(d, cb);
    }
}
KHASH_INIT_TYPEDEF(ptr_hashtable_type, void*, int)
KHASH_INIT_FUNCTION(ptr_hashtable_type, void*, int, 1, ptr_hash, ptr_isequal)
khash_t(ptr_hashtable_type)* ptr_hashtable;
void ptr_init() {
    ptr_hashtable = kh_init(ptr_hashtable_type);
}
void ptr_retain(void* v) {
    khiter_t k = kh_get(ptr_hashtable_type, ptr_hashtable, v);
    if (k == kh_end(ptr_hashtable)) {
        int ret;
        khiter_t k = kh_put(ptr_hashtable_type, ptr_hashtable, v, &ret);
        if (!ret) kh_del(ptr_hashtable_type, ptr_hashtable, k);
        kh_value(ptr_hashtable, k) = 1;
    }
    else {
        kh_value(ptr_hashtable, k)++;
    }
}
bool ptr_release(void* v) {
    khiter_t k = kh_get(ptr_hashtable_type, ptr_hashtable, v);
    if (k != kh_end(ptr_hashtable)) {
        kh_value(ptr_hashtable, k)--;
        if (kh_value(ptr_hashtable, k) == 0) {
            kh_del(ptr_hashtable_type, ptr_hashtable, k);
        }
        return false;
    }
    return true;
}
void weakptr_clear(void* parent, void* v) {
    void** p = (void**)parent;
    if (*p != v) {
        halt("weakptr was changed without clearing callback");
    }
    *p = 0;
}
#include <lib/common/object.c>
void sjf_array_char(sjs_array_char* _this) {
    if (_this->datasize < 0) {
        halt("size is less than zero");
    }
    if (!_this->data) {
        _this->data = malloc(_this->datasize * sizeof(char));
        if (!_this->data) {
            halt("grow: out of memory\n");
        }
    }
}

void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from) {
    _this->datasize = _from->datasize;
    _this->data = _from->data;
    _this->_isglobal = _from->_isglobal;
    _this->count = _from->count;
    _this->data = _from->data;
    if (!_this->_isglobal && _this->data) {
        ptr_retain(_this->data);
    }
}

void sjf_array_char_destroy(sjs_array_char* _this) {
    if (!_this->_isglobal && _this->data) {
        if (ptr_release(_this->data)) {
            char* p = (char*)_this->data;
            for (int i = 0; i < _this->count; i++) {
                ;
            }
            free(p);
        }
    }
}

void sjf_array_char_getat(sjs_array_char* _parent, int32_t index, char* _return) {
    if (index >= _parent->count || index < 0) {
        halt("getAt: out of bounds\n");
    }
    char* p = (char*)_parent->data;
    (*_return) = p[index];
return;;       
}

void sjf_array_char_grow(sjs_array_char* _parent, int32_t newsize, sjs_array_char* _return) {
    sjs_array_char* sjt_dot6 = 0;
    void* sjv_newdata;

    sjv_newdata = 0;
    if (_parent->datasize != newsize) {
        if (newsize < _parent->datasize) {
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
        }
        sjv_newdata = malloc(newsize * sizeof(char));
        if (!_parent->data) {
            halt("grow: out of memory\n");
        }
        char* p = (char*)_parent->data;
        char* newp = (char*)sjv_newdata;
        int count = _parent->count;
        for (int i = 0; i < count; i++) {
            newp[i] = p[i];
;
        }
    }
    _return->_refCount = 1;
    _return->datasize = newsize;
    _return->data = sjv_newdata;
    _return->_isglobal = false;
    sjt_dot6 = _parent;
    _return->count = sjt_dot6->count;
    sjf_array_char(_return);
}

void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newsize, sjs_array_char** _return) {
    sjs_array_char* sjt_dot7 = 0;
    void* sjv_newdata;

    sjv_newdata = 0;
    if (_parent->datasize != newsize) {
        if (newsize < _parent->datasize) {
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
        }
        sjv_newdata = malloc(newsize * sizeof(char));
        if (!_parent->data) {
            halt("grow: out of memory\n");
        }
        char* p = (char*)_parent->data;
        char* newp = (char*)sjv_newdata;
        int count = _parent->count;
        for (int i = 0; i < count; i++) {
            newp[i] = p[i];
;
        }
    }
    (*_return) = (sjs_array_char*)malloc(sizeof(sjs_array_char));
    (*_return)->_refCount = 1;
    (*_return)->datasize = newsize;
    (*_return)->data = sjv_newdata;
    (*_return)->_isglobal = false;
    sjt_dot7 = _parent;
    (*_return)->count = sjt_dot7->count;
    sjf_array_char_heap((*_return));
}

void sjf_array_char_heap(sjs_array_char* _this) {
    if (_this->datasize < 0) {
        halt("size is less than zero");
    }
    if (!_this->data) {
        _this->data = malloc(_this->datasize * sizeof(char));
        if (!_this->data) {
            halt("grow: out of memory\n");
        }
    }
}

void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item) {
    if (index != _parent->count) {
        halt("initAt: can only initialize last element\n");     
    }
    if (index >= _parent->datasize || index < 0) {
        halt("initAt: out of bounds %d:%d\n", index, _parent->datasize);
    }
    char* p = (char*)_parent->data;
    p[index] = item;
;
    _parent->count = index + 1;
}

void sjf_array_char_setat(sjs_array_char* _parent, int32_t index, char item) {
    if (index >= _parent->count || index < 0) {
        halt("setAt: out of bounds %d:%d\n", index, _parent->count);
    }
    char* p = (char*)_parent->data;
    ;
    p[index] = item;
;
}

void sjf_debug_writeline(sjs_string* data) {
    debugout("%s\n", (char*)data->data.data);
}

void sjf_lambda1(sjs_lambda1* _this) {
}

void sjf_lambda1_copy(sjs_lambda1* _this, sjs_lambda1* _from) {
}

void sjf_lambda1_destroy(sjs_lambda1* _this) {
}

void sjf_lambda1_heap(sjs_lambda1* _this) {
}

void sjf_lambda1_invoke(sjs_lambda1* _parent, sjs_string* _return) {
    _return->_refCount = 1;
    _return->count = 5;
    _return->data._refCount = 1;
    _return->data.datasize = 6;
    _return->data.data = (void*)sjg_string10;
    _return->data._isglobal = true;
    _return->data.count = 6;
    sjf_array_char(&_return->data);
    sjf_string(_return);
}

void sjf_lambda1_invoke_heap(sjs_lambda1* _parent, sjs_string** _return) {
    (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
    (*_return)->_refCount = 1;
    (*_return)->count = 5;
    (*_return)->data._refCount = 1;
    (*_return)->data.datasize = 6;
    (*_return)->data.data = (void*)sjg_string10;
    (*_return)->data._isglobal = true;
    (*_return)->data.count = 6;
    sjf_array_char(&(*_return)->data);
    sjf_string_heap((*_return));
}

void sjf_log(sjs_log* _this) {
}

void sjf_log__write(sjs_log* _parent, int32_t level, cb_string_heap_string cb) {
    sjs_string sjt_call1 = { -1 };
    sjs_string sjt_call2 = { -1 };
    sjs_string sjt_call3 = { -1 };
    sjs_string sjt_call4 = { -1 };
    sjs_string sjt_call5 = { -1 };
    sjs_string sjt_call6 = { -1 };
    sjs_string sjt_call7 = { -1 };
    cb_string_heap_string sjt_callback1;
    sjs_string* sjt_functionParam1 = 0;
    sjs_string* sjt_functionParam21 = 0;
    int32_t sjt_functionParam22;
    sjs_string* sjt_functionParam23 = 0;
    sjs_string* sjt_functionParam24 = 0;
    sjs_string* sjt_parent14 = 0;
    sjs_string* sjt_parent15 = 0;
    sjs_string* sjt_parent16 = 0;

    sjt_call4._refCount = 1;
    sjt_call4.count = 1;
    sjt_call4.data._refCount = 1;
    sjt_call4.data.datasize = 2;
    sjt_call4.data.data = (void*)sjg_string1;
    sjt_call4.data._isglobal = true;
    sjt_call4.data.count = 2;
    sjf_array_char(&sjt_call4.data);
    sjf_string(&sjt_call4);
    sjt_parent16 = &sjt_call4;
    sjt_functionParam22 = level;
    sjf_loglevel_asstring(sjt_functionParam22, &sjt_call5);
    sjt_functionParam21 = &sjt_call5;
    sjf_string_add(sjt_parent16, sjt_functionParam21, &sjt_call3);
    sjt_parent15 = &sjt_call3;
    sjt_call6._refCount = 1;
    sjt_call6.count = 2;
    sjt_call6.data._refCount = 1;
    sjt_call6.data.datasize = 3;
    sjt_call6.data.data = (void*)sjg_string9;
    sjt_call6.data._isglobal = true;
    sjt_call6.data.count = 3;
    sjf_array_char(&sjt_call6.data);
    sjf_string(&sjt_call6);
    sjt_functionParam23 = &sjt_call6;
    sjf_string_add(sjt_parent15, sjt_functionParam23, &sjt_call2);
    sjt_parent14 = &sjt_call2;
    sjt_callback1 = cb;
    sjt_callback1._cb(sjt_callback1._parent, &sjt_call7);
    sjt_functionParam24 = &sjt_call7;
    sjf_string_add(sjt_parent14, sjt_functionParam24, &sjt_call1);
    sjt_functionParam1 = &sjt_call1;
    sjf_debug_writeline(sjt_functionParam1);

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
}

void sjf_log_copy(sjs_log* _this, sjs_log* _from) {
    _this->minlevel = _from->minlevel;
}

void sjf_log_destroy(sjs_log* _this) {
}

void sjf_log_heap(sjs_log* _this) {
}

void sjf_log_info(sjs_log* _parent, cb_string_heap_string cb) {
    int32_t sjt_compare1;
    int32_t sjt_compare2;
    sjs_log* sjt_dot2 = 0;
    bool sjt_ifElse1;

    sjt_compare1 = sjv_loglevel_info;
    sjt_dot2 = _parent;
    sjt_compare2 = sjt_dot2->minlevel;
    sjt_ifElse1 = sjt_compare1 >= sjt_compare2;
    if (sjt_ifElse1) {
        int32_t sjt_functionParam25;
        cb_string_heap_string sjt_functionParam26;

        sjt_functionParam25 = sjv_loglevel_info;
        sjt_functionParam26 = cb;
        sjf_log__write(_parent, sjt_functionParam25, sjt_functionParam26);
    }
}

void sjf_loglevel_asstring(int32_t e, sjs_string* _return) {
    int32_t sjt_compare7;
    int32_t sjt_compare8;
    bool sjt_switch1;
    int32_t underscore1;

    underscore1 = e;
    sjt_compare7 = underscore1;
    sjt_compare8 = 0;
    sjt_switch1 = sjt_compare7 == sjt_compare8;
    if (sjt_switch1) {
        _return->_refCount = 1;
        _return->count = 5;
        _return->data._refCount = 1;
        _return->data.datasize = 6;
        _return->data.data = (void*)sjg_string2;
        _return->data._isglobal = true;
        _return->data.count = 6;
        sjf_array_char(&_return->data);
        sjf_string(_return);
    } else {
        int32_t sjt_compare10;
        int32_t sjt_compare9;
        bool sjt_switch2;

        sjt_compare9 = underscore1;
        sjt_compare10 = 1;
        sjt_switch2 = sjt_compare9 == sjt_compare10;
        if (sjt_switch2) {
            _return->_refCount = 1;
            _return->count = 5;
            _return->data._refCount = 1;
            _return->data.datasize = 6;
            _return->data.data = (void*)sjg_string3;
            _return->data._isglobal = true;
            _return->data.count = 6;
            sjf_array_char(&_return->data);
            sjf_string(_return);
        } else {
            int32_t sjt_compare11;
            int32_t sjt_compare12;
            bool sjt_switch3;

            sjt_compare11 = underscore1;
            sjt_compare12 = 2;
            sjt_switch3 = sjt_compare11 == sjt_compare12;
            if (sjt_switch3) {
                _return->_refCount = 1;
                _return->count = 4;
                _return->data._refCount = 1;
                _return->data.datasize = 5;
                _return->data.data = (void*)sjg_string4;
                _return->data._isglobal = true;
                _return->data.count = 5;
                sjf_array_char(&_return->data);
                sjf_string(_return);
            } else {
                int32_t sjt_compare13;
                int32_t sjt_compare14;
                bool sjt_switch4;

                sjt_compare13 = underscore1;
                sjt_compare14 = 3;
                sjt_switch4 = sjt_compare13 == sjt_compare14;
                if (sjt_switch4) {
                    _return->_refCount = 1;
                    _return->count = 4;
                    _return->data._refCount = 1;
                    _return->data.datasize = 5;
                    _return->data.data = (void*)sjg_string5;
                    _return->data._isglobal = true;
                    _return->data.count = 5;
                    sjf_array_char(&_return->data);
                    sjf_string(_return);
                } else {
                    int32_t sjt_compare15;
                    int32_t sjt_compare16;
                    bool sjt_switch5;

                    sjt_compare15 = underscore1;
                    sjt_compare16 = 4;
                    sjt_switch5 = sjt_compare15 == sjt_compare16;
                    if (sjt_switch5) {
                        _return->_refCount = 1;
                        _return->count = 5;
                        _return->data._refCount = 1;
                        _return->data.datasize = 6;
                        _return->data.data = (void*)sjg_string6;
                        _return->data._isglobal = true;
                        _return->data.count = 6;
                        sjf_array_char(&_return->data);
                        sjf_string(_return);
                    } else {
                        int32_t sjt_compare17;
                        int32_t sjt_compare18;
                        bool sjt_switch6;

                        sjt_compare17 = underscore1;
                        sjt_compare18 = 5;
                        sjt_switch6 = sjt_compare17 == sjt_compare18;
                        if (sjt_switch6) {
                            _return->_refCount = 1;
                            _return->count = 5;
                            _return->data._refCount = 1;
                            _return->data.datasize = 6;
                            _return->data.data = (void*)sjg_string7;
                            _return->data._isglobal = true;
                            _return->data.count = 6;
                            sjf_array_char(&_return->data);
                            sjf_string(_return);
                        } else {
                            _return->_refCount = 1;
                            _return->count = 0;
                            _return->data._refCount = 1;
                            _return->data.datasize = 1;
                            _return->data.data = (void*)sjg_string8;
                            _return->data._isglobal = true;
                            _return->data.count = 1;
                            sjf_array_char(&_return->data);
                            sjf_string(_return);
                        }
                    }
                }
            }
        }
    }
}

void sjf_string(sjs_string* _this) {
}

void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return) {
    int32_t sjt_compare3;
    int32_t sjt_compare4;
    sjs_string* sjt_dot3 = 0;
    bool sjt_ifElse2;
    sjs_array_char sjv_newdata = { -1 };

    sjt_dot3 = item;
    sjt_compare3 = sjt_dot3->count;
    sjt_compare4 = 0;
    sjt_ifElse2 = sjt_compare3 == sjt_compare4;
    if (sjt_ifElse2) {
        sjs_array_char* sjt_copy1 = 0;
        sjs_string* sjt_dot4 = 0;
        sjs_string* sjt_dot5 = 0;

        _return->_refCount = 1;
        sjt_dot4 = _parent;
        _return->count = sjt_dot4->count;
        sjt_dot5 = _parent;
        sjt_copy1 = &sjt_dot5->data;
        _return->data._refCount = 1;
        sjf_array_char_copy(&_return->data, sjt_copy1);
        sjf_string(_return);
    } else {
        int32_t i;
        int32_t sjt_cast1;
        sjs_array_char* sjt_copy2 = 0;
        sjs_string* sjt_dot10 = 0;
        sjs_string* sjt_dot11 = 0;
        sjs_string* sjt_dot13 = 0;
        sjs_string* sjt_dot8 = 0;
        sjs_string* sjt_dot9 = 0;
        int32_t sjt_forEnd1;
        int32_t sjt_forStart1;
        int32_t sjt_functionParam10;
        char sjt_functionParam11;
        int32_t sjt_functionParam2;
        int32_t sjt_functionParam3;
        char sjt_functionParam4;
        int32_t sjt_functionParam6;
        int32_t sjt_math3;
        int32_t sjt_math4;
        int32_t sjt_math5;
        int32_t sjt_math6;
        int32_t sjt_math7;
        int32_t sjt_math8;
        sjs_array_char* sjt_parent1 = 0;
        sjs_array_char* sjt_parent2 = 0;
        sjs_string* sjt_parent4 = 0;
        sjs_array_char* sjt_parent7 = 0;
        int32_t sjv_newcount;

        sjt_dot8 = _parent;
        sjt_parent1 = &sjt_dot8->data;
        sjt_dot9 = _parent;
        sjt_math5 = sjt_dot9->count;
        sjt_dot10 = item;
        sjt_math6 = sjt_dot10->count;
        sjt_math3 = sjt_math5 + sjt_math6;
        sjt_math4 = 1;
        sjt_functionParam2 = sjt_math3 + sjt_math4;
        sjf_array_char_grow(sjt_parent1, sjt_functionParam2, &sjv_newdata);
        sjt_dot11 = _parent;
        sjv_newcount = sjt_dot11->count;
        sjt_parent2 = &sjv_newdata;
        sjt_functionParam3 = sjv_newcount;
        sjt_parent4 = item;
        sjt_functionParam6 = 0;
        sjf_string_getat(sjt_parent4, sjt_functionParam6, &sjt_functionParam4);
        sjf_array_char_setat(sjt_parent2, sjt_functionParam3, sjt_functionParam4);
        sjt_math7 = sjv_newcount;
        sjt_math8 = 1;
        sjv_newcount = sjt_math7 + sjt_math8;
        sjt_forStart1 = 1;
        sjt_dot13 = item;
        sjt_forEnd1 = sjt_dot13->count;
        i = sjt_forStart1;
        while (i < sjt_forEnd1) {
            int32_t sjt_functionParam7;
            char sjt_functionParam8;
            int32_t sjt_functionParam9;
            int32_t sjt_math10;
            int32_t sjt_math9;
            sjs_array_char* sjt_parent5 = 0;
            sjs_string* sjt_parent6 = 0;

            sjt_parent5 = &sjv_newdata;
            sjt_functionParam7 = sjv_newcount;
            sjt_parent6 = item;
            sjt_functionParam9 = i;
            sjf_string_getat(sjt_parent6, sjt_functionParam9, &sjt_functionParam8);
            sjf_array_char_initat(sjt_parent5, sjt_functionParam7, sjt_functionParam8);
            sjt_math9 = sjv_newcount;
            sjt_math10 = 1;
            sjv_newcount = sjt_math9 + sjt_math10;
            i++;
        }

        sjt_parent7 = &sjv_newdata;
        sjt_functionParam10 = sjv_newcount;
        sjt_cast1 = 0;
        sjt_functionParam11 = (char)sjt_cast1;
        sjf_array_char_initat(sjt_parent7, sjt_functionParam10, sjt_functionParam11);
        _return->_refCount = 1;
        _return->count = sjv_newcount;
        sjt_copy2 = &sjv_newdata;
        _return->data._refCount = 1;
        sjf_array_char_copy(&_return->data, sjt_copy2);
        sjf_string(_return);
    }

    if (sjv_newdata._refCount == 1) { sjf_array_char_destroy(&sjv_newdata); }
;
}

void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string** _return) {
    int32_t sjt_compare5;
    int32_t sjt_compare6;
    sjs_string* sjt_dot14 = 0;
    bool sjt_ifElse3;
    sjs_array_char sjv_newdata = { -1 };

    sjt_dot14 = item;
    sjt_compare5 = sjt_dot14->count;
    sjt_compare6 = 0;
    sjt_ifElse3 = sjt_compare5 == sjt_compare6;
    if (sjt_ifElse3) {
        sjs_array_char* sjt_copy3 = 0;
        sjs_string* sjt_dot15 = 0;
        sjs_string* sjt_dot16 = 0;

        (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
        (*_return)->_refCount = 1;
        sjt_dot15 = _parent;
        (*_return)->count = sjt_dot15->count;
        sjt_dot16 = _parent;
        sjt_copy3 = &sjt_dot16->data;
        (*_return)->data._refCount = 1;
        sjf_array_char_copy(&(*_return)->data, sjt_copy3);
        sjf_string_heap((*_return));
    } else {
        int32_t i;
        int32_t sjt_cast2;
        sjs_array_char* sjt_copy4 = 0;
        sjs_string* sjt_dot17 = 0;
        sjs_string* sjt_dot18 = 0;
        sjs_string* sjt_dot19 = 0;
        sjs_string* sjt_dot20 = 0;
        sjs_string* sjt_dot21 = 0;
        int32_t sjt_forEnd2;
        int32_t sjt_forStart2;
        int32_t sjt_functionParam12;
        int32_t sjt_functionParam13;
        char sjt_functionParam14;
        int32_t sjt_functionParam15;
        int32_t sjt_functionParam19;
        char sjt_functionParam20;
        int32_t sjt_math11;
        int32_t sjt_math12;
        int32_t sjt_math13;
        int32_t sjt_math14;
        int32_t sjt_math15;
        int32_t sjt_math16;
        sjs_string* sjt_parent10 = 0;
        sjs_array_char* sjt_parent13 = 0;
        sjs_array_char* sjt_parent8 = 0;
        sjs_array_char* sjt_parent9 = 0;
        int32_t sjv_newcount;

        sjt_dot17 = _parent;
        sjt_parent8 = &sjt_dot17->data;
        sjt_dot18 = _parent;
        sjt_math13 = sjt_dot18->count;
        sjt_dot19 = item;
        sjt_math14 = sjt_dot19->count;
        sjt_math11 = sjt_math13 + sjt_math14;
        sjt_math12 = 1;
        sjt_functionParam12 = sjt_math11 + sjt_math12;
        sjf_array_char_grow(sjt_parent8, sjt_functionParam12, &sjv_newdata);
        sjt_dot20 = _parent;
        sjv_newcount = sjt_dot20->count;
        sjt_parent9 = &sjv_newdata;
        sjt_functionParam13 = sjv_newcount;
        sjt_parent10 = item;
        sjt_functionParam15 = 0;
        sjf_string_getat(sjt_parent10, sjt_functionParam15, &sjt_functionParam14);
        sjf_array_char_setat(sjt_parent9, sjt_functionParam13, sjt_functionParam14);
        sjt_math15 = sjv_newcount;
        sjt_math16 = 1;
        sjv_newcount = sjt_math15 + sjt_math16;
        sjt_forStart2 = 1;
        sjt_dot21 = item;
        sjt_forEnd2 = sjt_dot21->count;
        i = sjt_forStart2;
        while (i < sjt_forEnd2) {
            int32_t sjt_functionParam16;
            char sjt_functionParam17;
            int32_t sjt_functionParam18;
            int32_t sjt_math17;
            int32_t sjt_math18;
            sjs_array_char* sjt_parent11 = 0;
            sjs_string* sjt_parent12 = 0;

            sjt_parent11 = &sjv_newdata;
            sjt_functionParam16 = sjv_newcount;
            sjt_parent12 = item;
            sjt_functionParam18 = i;
            sjf_string_getat(sjt_parent12, sjt_functionParam18, &sjt_functionParam17);
            sjf_array_char_initat(sjt_parent11, sjt_functionParam16, sjt_functionParam17);
            sjt_math17 = sjv_newcount;
            sjt_math18 = 1;
            sjv_newcount = sjt_math17 + sjt_math18;
            i++;
        }

        sjt_parent13 = &sjv_newdata;
        sjt_functionParam19 = sjv_newcount;
        sjt_cast2 = 0;
        sjt_functionParam20 = (char)sjt_cast2;
        sjf_array_char_initat(sjt_parent13, sjt_functionParam19, sjt_functionParam20);
        (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
        (*_return)->_refCount = 1;
        (*_return)->count = sjv_newcount;
        sjt_copy4 = &sjv_newdata;
        (*_return)->data._refCount = 1;
        sjf_array_char_copy(&(*_return)->data, sjt_copy4);
        sjf_string_heap((*_return));
    }

    if (sjv_newdata._refCount == 1) { sjf_array_char_destroy(&sjv_newdata); }
;
}

void sjf_string_copy(sjs_string* _this, sjs_string* _from) {
    _this->count = _from->count;
    _this->data._refCount = 1;
    sjf_array_char_copy(&_this->data, &_from->data);
}

void sjf_string_destroy(sjs_string* _this) {
    if (_this->data._refCount == 1) { sjf_array_char_destroy(&_this->data); }
;
}

void sjf_string_getat(sjs_string* _parent, int32_t index, char* _return) {
    sjs_string* sjt_dot12 = 0;
    int32_t sjt_functionParam5;
    sjs_array_char* sjt_parent3 = 0;

    sjt_dot12 = _parent;
    sjt_parent3 = &sjt_dot12->data;
    sjt_functionParam5 = index;
    sjf_array_char_getat(sjt_parent3, sjt_functionParam5, _return);
}

void sjf_string_heap(sjs_string* _this) {
}

int main(int argc, char** argv) {
    sjv_loglevel_trace = 0;
    sjv_loglevel_debug = 1;
    sjv_loglevel_info = 2;
    sjv_loglevel_warn = 3;
    sjv_loglevel_error = 4;
    sjv_loglevel_fatal = 5;
    sjv_f32_pi = 3.14159265358979323846f;
    sjv_u32_maxvalue = (uint32_t)4294967295u;
    sjt_negate1 = 1;
    result1 = -sjt_negate1;
    sjt_math1 = result1;
    sjt_math2 = 2147483647;
    sjv_i32_maxvalue = sjt_math1 - sjt_math2;
    sjv_i32_minvalue = 2147483647;
    sjv_log._refCount = 1;
    sjv_log.minlevel = sjv_loglevel_warn;
    sjf_log(&sjv_log);
    sjv_emptystringdata = 0;
    sjv_emptystringdata = "";
    ptr_init();
    weakptr_init();
    sjt_dot1 = &sjv_log;
    sjt_dot1->minlevel = sjv_loglevel_info;
    sjt_parent17 = &sjv_log;
    sjs_lambda1* lambainit1;
    sjt_call8._refCount = 1;
    sjf_lambda1(&sjt_call8);
    lambainit1 = &sjt_call8;
    sjt_functionParam27._parent = (sjs_object*)lambainit1;
    sjt_functionParam27._cb = (void(*)(sjs_object*, sjs_string*))sjf_lambda1_invoke;
    sjt_functionParam27._cb_heap = (void(*)(sjs_object*, sjs_string**))sjf_lambda1_invoke_heap;
    sjf_log_info(sjt_parent17, sjt_functionParam27);
    main_destroy();
    #ifdef _DEBUG
    printf("\npress return to end\n");
    getchar();
    #endif
    return 0;
}

void main_destroy() {

    if (sjt_call8._refCount == 1) { sjf_lambda1_destroy(&sjt_call8); }
;
    if (sjv_log._refCount == 1) { sjf_log_destroy(&sjv_log); }
;
}