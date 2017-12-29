#include <lib/common/common.h>

const char* sjg_string1 = "not found";

#define sjs_log_typeId 15
#define sjs_hash_i32i32_typeId 16
#define sjs_array_char_typeId 25
#define sjs_string_typeId 24

typedef struct td_sjs_log sjs_log;
typedef struct td_sjs_hash_i32i32 sjs_hash_i32i32;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_string sjs_string;

struct td_sjs_log {
    int _refCount;
    int32_t minlevel;
};

struct td_sjs_hash_i32i32 {
    int _refCount;
    void* _hash;
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

#ifndef i32_i32_hash_typedef
#define i32_i32_hash_typedef
KHASH_INIT_TYPEDEF(i32_i32_hash_type, int32_t, int32_t)
#endif
#ifndef i32_i32_hash_typedef
#define i32_i32_hash_typedef
KHASH_INIT_TYPEDEF(i32_i32_hash_type, int32_t, int32_t)
#endif
int32_t sjv_loglevel_debug;
int32_t sjv_loglevel_error;
int32_t sjv_loglevel_fatal;
int32_t sjv_loglevel_info;
int32_t sjv_loglevel_trace;
int32_t sjv_loglevel_warn;

int32_t result1;
sjs_string sjt_call2 = { -1 };
int32_t sjt_functionParam1;
int32_t sjt_functionParam2;
int32_t sjt_functionParam3;
sjs_string* sjt_functionParam9 = 0;
sjs_hash_i32i32* sjt_parent1 = 0;
sjs_hash_i32i32* sjt_parent2 = 0;
sjs_hash_i32i32 sjv_a = { -1 };
int32_option sjv_b;
sjs_string sjv_c = { -1 };
int32_t sjv_clocks_per_sec;
void* sjv_emptystringdata;
float sjv_f32_pi;
int32_t sjv_i32_maxvalue;
int32_t sjv_i32_minvalue;
sjs_log sjv_log = { -1 };
uint32_t sjv_u32_maxvalue;

void sjf_array_char(sjs_array_char* _this);
void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_array_char_grow(sjs_array_char* _parent, int32_t newsize, sjs_array_char* _return);
void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newsize, sjs_array_char** _return);
void sjf_array_char_heap(sjs_array_char* _this);
void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item);
void sjf_debug_writeline(sjs_string* data);
void sjf_hash_i32i32(sjs_hash_i32i32* _this);
void sjf_hash_i32i32__weakptrremovekey(sjs_hash_i32i32* _parent, int32_t key);
void sjf_hash_i32i32__weakptrremovevalue(sjs_hash_i32i32* _parent, int32_t val);
void sjf_hash_i32i32_copy(sjs_hash_i32i32* _this, sjs_hash_i32i32* _from);
void sjf_hash_i32i32_destroy(sjs_hash_i32i32* _this);
void sjf_hash_i32i32_getat(sjs_hash_i32i32* _parent, int32_t key, int32_option* _return);
void sjf_hash_i32i32_heap(sjs_hash_i32i32* _this);
void sjf_hash_i32i32_setat(sjs_hash_i32i32* _parent, int32_t key, int32_t val);
void sjf_i32_asstring(int32_t val, int32_t base, sjs_string* _return);
void sjf_i32_asstring_heap(int32_t val, int32_t base, sjs_string** _return);
void sjf_i32_hash(int32_t val, uint32_t* _return);
void sjf_i32_isequal(int32_t l, int32_t r, bool* _return);
void sjf_log(sjs_log* _this);
void sjf_log_copy(sjs_log* _this, sjs_log* _from);
void sjf_log_destroy(sjs_log* _this);
void sjf_log_heap(sjs_log* _this);
void sjf_string(sjs_string* _this);
void sjf_string_copy(sjs_string* _this, sjs_string* _from);
void sjf_string_destroy(sjs_string* _this);
void sjf_string_heap(sjs_string* _this);
void sjf_string_nullterminate(sjs_string* _parent);
void main_destroy(void);

#include <lib/common/common.c>
#ifndef i32_i32_hash_function
#define i32_i32_hash_function
#if false
KHASH_INIT_FUNCTION_DEREF(i32_i32_hash_type, int32_t, int32_t, 1, sjf_i32_hash, sjf_i32_isequal)
#else
KHASH_INIT_FUNCTION(i32_i32_hash_type, int32_t, int32_t, 1, sjf_i32_hash, sjf_i32_isequal)
#endif
#endif
#ifndef i32_i32_hash_function
#define i32_i32_hash_function
#if false
KHASH_INIT_FUNCTION_DEREF(i32_i32_hash_type, int32_t, int32_t, 1, sjf_i32_hash, sjf_i32_isequal)
#else
KHASH_INIT_FUNCTION(i32_i32_hash_type, int32_t, int32_t, 1, sjf_i32_hash, sjf_i32_isequal)
#endif
#endif
void sjf_array_char(sjs_array_char* _this) {
    if (_this->datasize < 0) {
        halt("size is less than zero");
    }
    if (!_this->data) {
        _this->data = (int*)malloc(_this->datasize * sizeof(char) + sizeof(int)) + 1;
        int* refcount = (int*)_this->data - 1;
        *refcount = 1;
        if (!_this->data) {
            halt("grow: out of memory\n");
        }
    }
}

void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from) {
    _this->datasize = _from->datasize;
    _this->data = _from->data;
    _this->isglobal = _from->isglobal;
    _this->count = _from->count;
    _this->data = _from->data;
    if (!_this->isglobal && _this->data) {
        int* refcount = (int*)_this->data - 1;
        *refcount = *refcount + 1;
    }
}

void sjf_array_char_destroy(sjs_array_char* _this) {
    if (!_this->isglobal && _this->data) {
        int* refcount = (int*)_this->data - 1;
        *refcount = *refcount - 1;
        if (*refcount == 0) {
            #if !true && !false
            char* p = (char*)_this->data;
            for (int i = 0; i < _this->count; i++) {
                ;
            }
            #endif
            free(refcount);
        }
    }
}

void sjf_array_char_grow(sjs_array_char* _parent, int32_t newsize, sjs_array_char* _return) {
    void* sjv_newdata;

    sjv_newdata = 0;
    if (_parent->datasize != newsize) {
        if (newsize < _parent->datasize) {
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
        }
        sjv_newdata = (int*)(malloc(sizeof(int) + newsize * sizeof(char))) + 1;
        int* refcount = (int*)sjv_newdata - 1;
        *refcount = 1;
        if (!_parent->data) {
            halt("grow: out of memory\n");
        }
        char* p = (char*)_parent->data;
        char* newp = (char*)sjv_newdata;
        int count = _parent->count;
        #if true
        memcpy(newp, p, sizeof(char) * count);
        #else
        for (int i = 0; i < count; i++) {
            newp[i] = p[i];
;
        }
        #endif
    }
    _return->_refCount = 1;
    _return->datasize = newsize;
    _return->data = sjv_newdata;
    _return->isglobal = false;
    _return->count = _parent->count;
    sjf_array_char(_return);
}

void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newsize, sjs_array_char** _return) {
    void* sjv_newdata;

    sjv_newdata = 0;
    if (_parent->datasize != newsize) {
        if (newsize < _parent->datasize) {
            halt("grow: new size smaller than old _parent->datasize %d:%d\n", newsize, _parent->datasize);
        }
        sjv_newdata = (int*)(malloc(sizeof(int) + newsize * sizeof(char))) + 1;
        int* refcount = (int*)sjv_newdata - 1;
        *refcount = 1;
        if (!_parent->data) {
            halt("grow: out of memory\n");
        }
        char* p = (char*)_parent->data;
        char* newp = (char*)sjv_newdata;
        int count = _parent->count;
        #if true
        memcpy(newp, p, sizeof(char) * count);
        #else
        for (int i = 0; i < count; i++) {
            newp[i] = p[i];
;
        }
        #endif
    }
    (*_return) = (sjs_array_char*)malloc(sizeof(sjs_array_char));
    (*_return)->_refCount = 1;
    (*_return)->datasize = newsize;
    (*_return)->data = sjv_newdata;
    (*_return)->isglobal = false;
    (*_return)->count = _parent->count;
    sjf_array_char_heap((*_return));
}

void sjf_array_char_heap(sjs_array_char* _this) {
    if (_this->datasize < 0) {
        halt("size is less than zero");
    }
    if (!_this->data) {
        _this->data = (int*)malloc(_this->datasize * sizeof(char) + sizeof(int)) + 1;
        int* refcount = (int*)_this->data - 1;
        *refcount = 1;
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

void sjf_debug_writeline(sjs_string* data) {
    sjs_string* sjt_parent5 = 0;

    sjt_parent5 = data;
    sjf_string_nullterminate(sjt_parent5);
    debugout("%s\n", (char*)data->data.data);
}

void sjf_hash_i32i32(sjs_hash_i32i32* _this) {
    _this->_hash = kh_init(i32_i32_hash_type);
}

void sjf_hash_i32i32__weakptrremovekey(sjs_hash_i32i32* _parent, int32_t key) {
    #if false
    khash_t(i32_i32_hash_type)* p = (khash_t(i32_i32_hash_type)*)_parent->_hash;    
    khiter_t k = kh_get(i32_i32_hash_type, p, key);
    if (k != kh_end(p)) {
        kh_del(i32_i32_hash_type, p, k);
    }
    #endif
}

void sjf_hash_i32i32__weakptrremovevalue(sjs_hash_i32i32* _parent, int32_t val) {
    #if false
    khash_t(i32_i32_hash_type)* p = (khash_t(i32_i32_hash_type)*)_parent->_hash;
    for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
        if (kh_exist(p, k)) {
            int32_t t = kh_value(p, k);
            if (t == val) {
                kh_del(i32_i32_hash_type, p, k);
            }
        }
    }
    #endif
}

void sjf_hash_i32i32_copy(sjs_hash_i32i32* _this, sjs_hash_i32i32* _from) {
    _this->_hash = _from->_hash;
    khash_t(i32_i32_hash_type)* p = (khash_t(i32_i32_hash_type)*)_this->_hash;
    p->refcount++;
}

void sjf_hash_i32i32_destroy(sjs_hash_i32i32* _this) {
    khash_t(i32_i32_hash_type)* p = (khash_t(i32_i32_hash_type)*)_this->_hash;
    p->refcount--;
    if (p->refcount == 0) {
        for (khiter_t k = kh_begin(p); k != kh_end(p); ++k) {
            if (kh_exist(p, k)) {
                #if false
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_i32i32__weakptrremovekey };
                weakptr_cb_remove(kh_key(p, k), cb);
                #else
                ;
                #endif
                #if false
                delete_cb cb = { p, (void(*)(void*, void*))sjf_hash_i32i32__weakptrremovevalue };
                weakptr_cb_remove(kh_value(p, k), cb);
                #else
                ;
                #endif
            }
        }
        kh_destroy(i32_i32_hash_type, _this->_hash);
    }
}

void sjf_hash_i32i32_getat(sjs_hash_i32i32* _parent, int32_t key, int32_option* _return) {
    khash_t(i32_i32_hash_type)* p = (khash_t(i32_i32_hash_type)*)_parent->_hash;
    #if false
    khiter_t k = kh_get(i32_i32_hash_type, p, *key);
    #else
    khiter_t k = kh_get(i32_i32_hash_type, p, key);
    #endif
    if (k == kh_end(p)) {
        (*_return) = int32_empty;
return;
    }
    _return->isvalid = true;
_return->value = kh_val(p, k);
return;;
}

void sjf_hash_i32i32_heap(sjs_hash_i32i32* _this) {
    _this->_hash = kh_init(i32_i32_hash_type);
}

void sjf_hash_i32i32_setat(sjs_hash_i32i32* _parent, int32_t key, int32_t val) {
    khash_t(i32_i32_hash_type)* p = (khash_t(i32_i32_hash_type)*)_parent->_hash;
    #if false
    khiter_t k = kh_get(i32_i32_hash_type, p, *key);
    #else
    khiter_t k = kh_get(i32_i32_hash_type, p, key);
    #endif
    if (k != kh_end(p)) {            
    ;
}
int ret;
#if false
k = kh_put(i32_i32_hash_type, _parent->_hash, *key, &ret);
#else
k = kh_put(i32_i32_hash_type, _parent->_hash, key, &ret);
#endif
if (!ret) kh_del(i32_i32_hash_type, p, k);
#if false
delete_cb cb = { _parent, (void(*)(void*, void*))sjf_hash_i32i32__weakptrremovekey };
weakptr_cb_add(key, cb);
#else
int32_t t;
t = key;
;
#endif
#if false
delete_cb cb = { _parent, (void(*)(void*, void*))sjf_hash_i32i32__weakptrremovevalue };
weakptr_cb_add(val, cb);
kh_val(p, k) = val;
#else
kh_val(p, k) = val;
;
#endif
}

void sjf_i32_asstring(int32_t val, int32_t base, sjs_string* _return) {
    int32_t sjv_count;
    void* sjv_data;

    sjv_count = 0;
    sjv_data = 0;
    sjv_data = (int*)malloc(sizeof(int) + sizeof(char) * 256) + 1;
    int* refcount = (int*)sjv_data - 1;
    *refcount = 1;
    char *tmp = (char*)sjv_data + 128;
    char *tp = (char*)sjv_data + 128;
    int i;
    unsigned v;
    int sign = (base == 10 && val < 0);    
    if (sign)
    v = -val;
    else
    v = (unsigned)val;
    while (v || tp == tmp)
    {
        i = v % base;
        v /= base; // v/=base uses less CPU clocks than v=v/base does
        if (i < 10)
        *tp++ = i + '0';
        else
        *tp++ = i + 'a' - 10;
    }
    int len = tp - tmp;
    char* sp = (char*)sjv_data;
    if (sign) 
    {
        *sp++ = '-';
        len++;
    }
    while (tp > tmp)
    *sp++ = *--tp;
    sjv_count = len;
    _return->_refCount = 1;
    _return->count = sjv_count;
    _return->data._refCount = 1;
    _return->data.datasize = 256;
    _return->data.data = sjv_data;
    _return->data.isglobal = false;
    _return->data.count = sjv_count;
    sjf_array_char(&_return->data);
    _return->_isnullterminated = false;
    sjf_string(_return);
}

void sjf_i32_asstring_heap(int32_t val, int32_t base, sjs_string** _return) {
    int32_t sjv_count;
    void* sjv_data;

    sjv_count = 0;
    sjv_data = 0;
    sjv_data = (int*)malloc(sizeof(int) + sizeof(char) * 256) + 1;
    int* refcount = (int*)sjv_data - 1;
    *refcount = 1;
    char *tmp = (char*)sjv_data + 128;
    char *tp = (char*)sjv_data + 128;
    int i;
    unsigned v;
    int sign = (base == 10 && val < 0);    
    if (sign)
    v = -val;
    else
    v = (unsigned)val;
    while (v || tp == tmp)
    {
        i = v % base;
        v /= base; // v/=base uses less CPU clocks than v=v/base does
        if (i < 10)
        *tp++ = i + '0';
        else
        *tp++ = i + 'a' - 10;
    }
    int len = tp - tmp;
    char* sp = (char*)sjv_data;
    if (sign) 
    {
        *sp++ = '-';
        len++;
    }
    while (tp > tmp)
    *sp++ = *--tp;
    sjv_count = len;
    (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
    (*_return)->_refCount = 1;
    (*_return)->count = sjv_count;
    (*_return)->data._refCount = 1;
    (*_return)->data.datasize = 256;
    (*_return)->data.data = sjv_data;
    (*_return)->data.isglobal = false;
    (*_return)->data.count = sjv_count;
    sjf_array_char(&(*_return)->data);
    (*_return)->_isnullterminated = false;
    sjf_string_heap((*_return));
}

void sjf_i32_hash(int32_t val, uint32_t* _return) {
    int32_t sjt_cast1;

    sjt_cast1 = val;
    (*_return) = (uint32_t)sjt_cast1;
}

void sjf_i32_isequal(int32_t l, int32_t r, bool* _return) {
    (*_return) = l == r;
}

void sjf_log(sjs_log* _this) {
}

void sjf_log_copy(sjs_log* _this, sjs_log* _from) {
    _this->minlevel = _from->minlevel;
}

void sjf_log_destroy(sjs_log* _this) {
}

void sjf_log_heap(sjs_log* _this) {
}

void sjf_string(sjs_string* _this) {
}

void sjf_string_copy(sjs_string* _this, sjs_string* _from) {
    _this->count = _from->count;
    _this->data._refCount = 1;
    sjf_array_char_copy(&_this->data, &_from->data);
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
    bool result3;
    sjs_array_char sjt_call1 = { -1 };

    result2 = !(&_parent->data)->isglobal;
    result3 = !_parent->_isnullterminated;
    if (result2 || result3) {
        int32_t sjt_functionParam7;
        char sjt_functionParam8;
        sjs_array_char* sjt_parent4 = 0;

        if ((_parent->count + 1) > (&_parent->data)->datasize) {
            int32_t sjt_functionParam6;
            sjs_array_char* sjt_parent3 = 0;

            sjt_parent3 = &_parent->data;
            sjt_functionParam6 = _parent->count + 1;
            sjf_array_char_grow(sjt_parent3, sjt_functionParam6, &sjt_call1);
            if (_parent->data._refCount == 1) { sjf_array_char_destroy(&_parent->data); }
;
            _parent->data._refCount = 1;
            sjf_array_char_copy(&_parent->data, (&sjt_call1));
        }

        sjt_parent4 = &_parent->data;
        sjt_functionParam7 = _parent->count;
        sjt_functionParam8 = '\0';
        sjf_array_char_initat(sjt_parent4, sjt_functionParam7, sjt_functionParam8);
        _parent->_isnullterminated = true;
    }

    if (sjt_call1._refCount == 1) { sjf_array_char_destroy(&sjt_call1); }
;
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
    result1 = -1;
    sjv_i32_maxvalue = result1 - 2147483647;
    sjv_i32_minvalue = 2147483647;
    sjv_log._refCount = 1;
    sjv_log.minlevel = sjv_loglevel_warn;
    sjf_log(&sjv_log);
    sjv_emptystringdata = 0;
    sjv_emptystringdata = "";
    ptr_init();
    weakptr_init();
    sjv_clocks_per_sec = 0;
    sjv_clocks_per_sec = CLOCKS_PER_SEC;
    sjv_a._refCount = 1;
    sjf_hash_i32i32(&sjv_a);
    sjt_parent1 = &sjv_a;
    sjt_functionParam1 = 1;
    sjt_functionParam2 = 2;
    sjf_hash_i32i32_setat(sjt_parent1, sjt_functionParam1, sjt_functionParam2);
    sjt_parent2 = &sjv_a;
    sjt_functionParam3 = 1;
    sjf_hash_i32i32_getat(sjt_parent2, sjt_functionParam3, &sjv_b);
    if (sjv_b.isvalid) {
        int32_t sjt_functionParam4;
        int32_t sjt_functionParam5;
        int32_option sjt_getValue1;

        sjt_getValue1 = sjv_b;
        sjt_functionParam4 = sjt_getValue1.value;
        sjt_functionParam5 = 10;
        sjf_i32_asstring(sjt_functionParam4, sjt_functionParam5, &sjv_c);
    } else {
        sjv_c._refCount = -1;
    }

    if ((sjv_c._refCount != -1 ? &sjv_c : 0) != 0) {
        sjt_functionParam9 = (sjv_c._refCount != -1 ? &sjv_c : 0);
    } else {
        sjt_call2._refCount = 1;
        sjt_call2.count = 9;
        sjt_call2.data._refCount = 1;
        sjt_call2.data.datasize = 9;
        sjt_call2.data.data = (void*)sjg_string1;
        sjt_call2.data.isglobal = true;
        sjt_call2.data.count = 9;
        sjf_array_char(&sjt_call2.data);
        sjt_call2._isnullterminated = false;
        sjf_string(&sjt_call2);
        sjt_functionParam9 = &sjt_call2;
    }

    sjf_debug_writeline(sjt_functionParam9);
    main_destroy();
    return 0;
}

void main_destroy() {

    if (sjt_call2._refCount == 1) { sjf_string_destroy(&sjt_call2); }
;
    if (sjv_a._refCount == 1) { sjf_hash_i32i32_destroy(&sjv_a); }
;
    if (sjv_c._refCount == 1) { sjf_string_destroy(&sjv_c); }
;
    if (sjv_log._refCount == 1) { sjf_log_destroy(&sjv_log); }
;
}
