#include <lib/sj-lib-common/common.h>

sjs_array sjg_string1 = { 1, 2, 2, ", "};
sjs_array sjg_string2 = { 1, 0, 0, ""};
sjs_array sjg_string3 = { 1, 1, 1, "c"};

sjs_array g_empty = { 1, 1, 0, "" };
#define sjs_hash_type_bool_typeId 15
#define sjs_log_typeId 20
#define sjs_array_char_typeId 23
#define sjs_string_typeId 21
#define sjs_class_typeId 26
#define sjs_array_class_typeId 27
#define cb_class_class_i32_typeId 48
#define cb_class_class_i32_heap_typeId 48

typedef struct td_sjs_hash_type_bool sjs_hash_type_bool;
typedef struct td_sjs_log sjs_log;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_string sjs_string;
typedef struct td_sjs_class sjs_class;
typedef struct td_sjs_array_class sjs_array_class;
typedef struct td_cb_class_class_i32 cb_class_class_i32;
typedef struct td_cb_class_class_i32_heap cb_class_class_i32_heap;

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
    int32_t x;
};

struct td_sjs_array_class {
    int _refCount;
    void* v;
};

struct td_cb_class_class_i32 {
    sjs_object* _parent;
    void (*_cb)(sjs_object* _parent, sjs_class*, sjs_class*, int32_t* _return);
};

struct td_cb_class_class_i32_heap {
    cb_class_class_i32 inner;
    void (*_destroy)(sjs_object*);
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

sjs_array_class g_a = { -1 };
int32_t g_clocks_per_sec;
float g_f32_pi;
int32_t g_i32_maxvalue;
int32_t g_i32_minvalue;
sjs_log g_log = { -1 };
sjs_hash_type_bool g_log_excludeall = { -1 };
sjs_hash_type_bool g_log_includeall = { -1 };
uint32_t g_u32_maxvalue;
int32_t result1;
sjs_class sjt_call1 = { -1 };
sjs_string sjt_call11 = { -1 };
sjs_class sjt_call2 = { -1 };
sjs_string sjt_call20 = { -1 };
sjs_string sjt_call22 = { -1 };
sjs_string sjt_call23 = { -1 };
sjs_string sjt_call27 = { -1 };
sjs_string sjt_call28 = { -1 };
sjs_class sjt_call3 = { -1 };
sjs_class sjt_call4 = { -1 };
sjs_class sjt_call5 = { -1 };
int32_t sjt_functionParam10;
sjs_string* sjt_functionParam101 = 0;
sjs_string* sjt_functionParam102 = 0;
sjs_class* sjt_functionParam11 = 0;
int32_t sjt_functionParam12;
sjs_class* sjt_functionParam13 = 0;
sjs_string* sjt_functionParam35 = 0;
int32_t sjt_functionParam4;
sjs_class* sjt_functionParam5 = 0;
int32_t sjt_functionParam6;
sjs_string* sjt_functionParam67 = 0;
sjs_class* sjt_functionParam7 = 0;
sjs_string* sjt_functionParam74 = 0;
sjs_string* sjt_functionParam75 = 0;
int32_t sjt_functionParam8;
sjs_class* sjt_functionParam9 = 0;
cb_class_class_i32 sjt_functionParam98;
sjs_array_class* sjt_parent12 = 0;
sjs_array_class* sjt_parent3 = 0;
sjs_array_class* sjt_parent39 = 0;
sjs_array_class* sjt_parent4 = 0;
sjs_array_class* sjt_parent40 = 0;
sjs_array_class* sjt_parent41 = 0;
sjs_array_class* sjt_parent42 = 0;
sjs_array_class* sjt_parent43 = 0;
sjs_array_class* sjt_parent5 = 0;
sjs_array_class* sjt_parent6 = 0;
sjs_array_class* sjt_parent7 = 0;
sjs_hash_type_bool sjt_value1 = { -1 };

void sjf_array_char(sjs_array_char* _this);
void sjf_array_char_clone(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char* _return);
void sjf_array_char_clone_heap(sjs_array_char* _parent, int32_t offset, int32_t count, int32_t newsize, sjs_array_char** _return);
void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_array_char_getat(sjs_array_char* _parent, int32_t index, char* _return);
void sjf_array_char_getcount(sjs_array_char* _parent, int32_t* _return);
void sjf_array_char_getsize(sjs_array_char* _parent, int32_t* _return);
void sjf_array_char_heap(sjs_array_char* _this);
void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item);
void sjf_array_class(sjs_array_class* _this);
void sjf_array_class__quicksort(sjs_array_class* _parent, int32_t left, int32_t right);
void sjf_array_class__quicksortcallback(sjs_array_class* _parent, int32_t left, int32_t right, cb_class_class_i32 cb);
void sjf_array_class_asstring(sjs_array_class* _parent, sjs_string* sep, sjs_string* _return);
void sjf_array_class_asstring_heap(sjs_array_class* _parent, sjs_string* sep, sjs_string** _return);
void sjf_array_class_copy(sjs_array_class* _this, sjs_array_class* _from);
void sjf_array_class_destroy(sjs_array_class* _this);
void sjf_array_class_getat(sjs_array_class* _parent, int32_t index, sjs_class* _return);
void sjf_array_class_getat_heap(sjs_array_class* _parent, int32_t index, sjs_class** _return);
void sjf_array_class_getcount(sjs_array_class* _parent, int32_t* _return);
void sjf_array_class_heap(sjs_array_class* _this);
void sjf_array_class_initat(sjs_array_class* _parent, int32_t index, sjs_class* item);
void sjf_array_class_reverse(sjs_array_class* _parent);
void sjf_array_class_setat(sjs_array_class* _parent, int32_t index, sjs_class* item);
void sjf_array_class_sort(sjs_array_class* _parent);
void sjf_array_class_sortcb(sjs_array_class* _parent, cb_class_class_i32 cb);
void sjf_class(sjs_class* _this);
void sjf_class_asstring(sjs_class* _parent, sjs_string* _return);
void sjf_class_asstring_heap(sjs_class* _parent, sjs_string** _return);
void sjf_class_compare(sjs_class* l, sjs_class* r, int32_t* _return);
void sjf_class_compare_callback(void * _parent, sjs_class* l, sjs_class* r, int32_t* _return);
void sjf_class_copy(sjs_class* _this, sjs_class* _from);
void sjf_class_destroy(sjs_class* _this);
void sjf_class_heap(sjs_class* _this);
void sjf_class_isgreater(sjs_class* _parent, sjs_class* c, bool* _return);
void sjf_class_isless(sjs_class* _parent, sjs_class* c, bool* _return);
void sjf_console_writeline(sjs_string* data);
void sjf_hash_type_bool(sjs_hash_type_bool* _this);
void sjf_hash_type_bool__weakptrremovekey(sjs_hash_type_bool* _parent, int32_t key);
void sjf_hash_type_bool__weakptrremovevalue(sjs_hash_type_bool* _parent, bool val);
void sjf_hash_type_bool_copy(sjs_hash_type_bool* _this, sjs_hash_type_bool* _from);
void sjf_hash_type_bool_destroy(sjs_hash_type_bool* _this);
void sjf_hash_type_bool_heap(sjs_hash_type_bool* _this);
void sjf_i32_asstring(int32_t val, int32_t base, sjs_string* _return);
void sjf_i32_asstring_heap(int32_t val, int32_t base, sjs_string** _return);
void sjf_i32_compare(int32_t l, int32_t r, int32_t* _return);
void sjf_log(sjs_log* _this);
void sjf_log_copy(sjs_log* _this, sjs_log* _from);
void sjf_log_destroy(sjs_log* _this);
void sjf_log_heap(sjs_log* _this);
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

void sjf_array_char_getat(sjs_array_char* _parent, int32_t index, char* _return) {
#line 38 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_parent->v;
#line 39
    if (index >= arr->count || index < 0) {
#line 40
        halt("getAt: out of bounds\n");
#line 41
    }
#line 42
    char* p = (char*)arr->data;
#line 43
    #line 37 "lib/sj-lib-common/array.sj"
(*_return) = p[index];
return;;       
}

void sjf_array_char_getcount(sjs_array_char* _parent, int32_t* _return) {
#line 26 "lib/sj-lib-common/array.sj"
    #line 25 "lib/sj-lib-common/array.sj"
(*_return) = ((sjs_array*)_parent->v)->count;
return;;
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

void sjf_array_char_initat(sjs_array_char* _parent, int32_t index, char item) {
#line 49 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_parent->v;
#line 50
    if (index != arr->count) {
#line 51
        halt("initAt: can only initialize last element\n");     
#line 52
    }
#line 53
    if (index >= arr->size || index < 0) {
#line 54
        halt("initAt: out of bounds %d:%d\n", index, arr->size);
#line 55
    }
#line 57
    char* p = (char*)arr->data;
#line 58
    #line 47 "lib/sj-lib-common/array.sj"
p[index] = item;
;
#line 59
    arr->count = index + 1;
}

void sjf_array_class(sjs_array_class* _this) {
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

void sjf_array_class__quicksort(sjs_array_class* _parent, int32_t left, int32_t right) {
    int32_t i;
    int32_t j;
    sjs_class pivot = { -1 };
    int32_t sjt_functionParam14;
    bool sjt_while1;

#line 200 "lib/sj-lib-common/array.sj"
    i = left;
#line 200
    j = right;
#line 204
    sjt_functionParam14 = (left + right) / 2;
#line 204
    sjf_array_class_getat(_parent, sjt_functionParam14, &pivot);
#line 205
    sjt_while1 = i <= j;
    while (sjt_while1) {
        sjs_class sjt_call10 = { -1 };
        sjs_class sjt_call6 = { -1 };
        sjs_class sjt_call8 = { -1 };
        int32_t sjt_functionParam15;
        sjs_class* sjt_functionParam16 = 0;
        int32_t sjt_functionParam19;
        sjs_class* sjt_functionParam20 = 0;
        sjs_class* sjt_parent10 = 0;
        sjs_class* sjt_parent8 = 0;
        bool sjt_while2;
        bool sjt_while3;
        sjs_class tmp = { -1 };

#line 206 "lib/sj-lib-common/array.sj"
        sjt_functionParam15 = i;
#line 206
        sjf_array_class_getat(_parent, sjt_functionParam15, &sjt_call6);
#line 206
        sjt_parent8 = &sjt_call6;
#line 206
        sjt_functionParam16 = &pivot;
#line 206
        sjf_class_isless(sjt_parent8, sjt_functionParam16, &sjt_while2);
        while (sjt_while2) {
            sjs_class sjt_call7 = { -1 };
            int32_t sjt_functionParam17;
            sjs_class* sjt_functionParam18 = 0;
            sjs_class* sjt_parent9 = 0;

#line 207 "lib/sj-lib-common/array.sj"
            i = i + 1;
#line 206
            sjt_functionParam17 = i;
#line 206
            sjf_array_class_getat(_parent, sjt_functionParam17, &sjt_call7);
#line 206
            sjt_parent9 = &sjt_call7;
#line 206
            sjt_functionParam18 = &pivot;
#line 206
            sjf_class_isless(sjt_parent9, sjt_functionParam18, &sjt_while2);

            if (sjt_call7._refCount == 1) { sjf_class_destroy(&sjt_call7); }
;
        }

#line 210
        sjt_functionParam19 = j;
#line 210
        sjf_array_class_getat(_parent, sjt_functionParam19, &sjt_call8);
#line 210
        sjt_parent10 = &sjt_call8;
#line 210
        sjt_functionParam20 = &pivot;
#line 210
        sjf_class_isgreater(sjt_parent10, sjt_functionParam20, &sjt_while3);
        while (sjt_while3) {
            sjs_class sjt_call9 = { -1 };
            int32_t sjt_functionParam21;
            sjs_class* sjt_functionParam22 = 0;
            sjs_class* sjt_parent11 = 0;

#line 211 "lib/sj-lib-common/array.sj"
            j = j - 1;
#line 210
            sjt_functionParam21 = j;
#line 210
            sjf_array_class_getat(_parent, sjt_functionParam21, &sjt_call9);
#line 210
            sjt_parent11 = &sjt_call9;
#line 210
            sjt_functionParam22 = &pivot;
#line 210
            sjf_class_isgreater(sjt_parent11, sjt_functionParam22, &sjt_while3);

            if (sjt_call9._refCount == 1) { sjf_class_destroy(&sjt_call9); }
;
        }

        if (i <= j) {
            int32_t sjt_functionParam23;
            int32_t sjt_functionParam24;
            sjs_class* sjt_functionParam25 = 0;
            int32_t sjt_functionParam26;
            int32_t sjt_functionParam27;
            sjs_class* sjt_functionParam28 = 0;

#line 215 "lib/sj-lib-common/array.sj"
            sjt_functionParam23 = i;
#line 215
            sjf_array_class_getat(_parent, sjt_functionParam23, &tmp);
#line 216
            sjt_functionParam24 = i;
#line 216
            sjt_functionParam26 = j;
#line 216
            sjf_array_class_getat(_parent, sjt_functionParam26, &sjt_call10);
#line 216
            sjt_functionParam25 = &sjt_call10;
#line 216
            sjf_array_class_setat(_parent, sjt_functionParam24, sjt_functionParam25);
#line 217
            sjt_functionParam27 = j;
#line 217
            sjt_functionParam28 = &tmp;
#line 217
            sjf_array_class_setat(_parent, sjt_functionParam27, sjt_functionParam28);
#line 218
            i = i + 1;
#line 219
            j = j - 1;
        }

#line 205
        sjt_while1 = i <= j;

        if (sjt_call10._refCount == 1) { sjf_class_destroy(&sjt_call10); }
;
        if (sjt_call6._refCount == 1) { sjf_class_destroy(&sjt_call6); }
;
        if (sjt_call8._refCount == 1) { sjf_class_destroy(&sjt_call8); }
;
        if (tmp._refCount == 1) { sjf_class_destroy(&tmp); }
;
    }

    if (left < j) {
        int32_t sjt_functionParam29;
        int32_t sjt_functionParam30;

#line 200 "lib/sj-lib-common/array.sj"
        sjt_functionParam29 = left;
#line 224
        sjt_functionParam30 = j;
#line 224
        sjf_array_class__quicksort(_parent, sjt_functionParam29, sjt_functionParam30);
    }

    if (i < right) {
        int32_t sjt_functionParam31;
        int32_t sjt_functionParam32;

#line 227 "lib/sj-lib-common/array.sj"
        sjt_functionParam31 = i;
#line 200
        sjt_functionParam32 = right;
#line 200
        sjf_array_class__quicksort(_parent, sjt_functionParam31, sjt_functionParam32);
    }

    if (pivot._refCount == 1) { sjf_class_destroy(&pivot); }
;
}

void sjf_array_class__quicksortcallback(sjs_array_class* _parent, int32_t left, int32_t right, cb_class_class_i32 cb) {
    int32_t i;
    int32_t j;
    sjs_class pivot = { -1 };
    int32_t sjt_functionParam76;
    bool sjt_while4;

#line 231 "lib/sj-lib-common/array.sj"
    i = left;
#line 231
    j = right;
#line 235
    sjt_functionParam76 = (left + right) / 2;
#line 235
    sjf_array_class_getat(_parent, sjt_functionParam76, &pivot);
#line 236
    sjt_while4 = i <= j;
    while (sjt_while4) {
        bool shouldcontinue;
        sjs_class sjt_call26 = { -1 };
        int32_t sjt_capture13;
        bool sjt_while5;
        bool sjt_while6;
        sjs_class tmp = { -1 };

#line 237 "lib/sj-lib-common/array.sj"
        shouldcontinue = true;
#line 237
        sjf_array_class_getcount(_parent, &sjt_capture13);
        if (i < sjt_capture13) {
#line 238 "lib/sj-lib-common/array.sj"
            sjt_while5 = shouldcontinue;
        } else {
#line 238 "lib/sj-lib-common/array.sj"
            sjt_while5 = false;
        }

        while (sjt_while5) {
            sjs_class sjt_call24 = { -1 };
            int32_t sjt_capture14;
            int32_t sjt_capture15;
            sjs_class* sjt_functionParam77 = 0;
            int32_t sjt_functionParam78;
            sjs_class* sjt_functionParam79 = 0;

#line 239 "lib/sj-lib-common/array.sj"
            sjt_functionParam78 = i;
#line 239
            sjf_array_class_getat(_parent, sjt_functionParam78, &sjt_call24);
#line 239
            sjt_functionParam77 = &sjt_call24;
#line 239
            sjt_functionParam79 = &pivot;
#line 239
            cb._cb(cb._parent, sjt_functionParam77, sjt_functionParam79, &sjt_capture14);
#line 239
            shouldcontinue = sjt_capture14 < 0;
            if (shouldcontinue) {
#line 241 "lib/sj-lib-common/array.sj"
                i = i + 1;
            }

#line 239
            sjf_array_class_getcount(_parent, &sjt_capture15);
            if (i < sjt_capture15) {
#line 238 "lib/sj-lib-common/array.sj"
                sjt_while5 = shouldcontinue;
            } else {
#line 238 "lib/sj-lib-common/array.sj"
                sjt_while5 = false;
            }

            if (sjt_call24._refCount == 1) { sjf_class_destroy(&sjt_call24); }
;
        }

#line 245
        shouldcontinue = true;
        if (j >= 0) {
#line 246 "lib/sj-lib-common/array.sj"
            sjt_while6 = shouldcontinue;
        } else {
#line 246 "lib/sj-lib-common/array.sj"
            sjt_while6 = false;
        }

        while (sjt_while6) {
            sjs_class sjt_call25 = { -1 };
            int32_t sjt_capture16;
            sjs_class* sjt_functionParam80 = 0;
            int32_t sjt_functionParam81;
            sjs_class* sjt_functionParam82 = 0;

#line 247 "lib/sj-lib-common/array.sj"
            sjt_functionParam81 = j;
#line 247
            sjf_array_class_getat(_parent, sjt_functionParam81, &sjt_call25);
#line 247
            sjt_functionParam80 = &sjt_call25;
#line 247
            sjt_functionParam82 = &pivot;
#line 247
            cb._cb(cb._parent, sjt_functionParam80, sjt_functionParam82, &sjt_capture16);
#line 247
            shouldcontinue = sjt_capture16 > 0;
            if (shouldcontinue) {
#line 249 "lib/sj-lib-common/array.sj"
                j = j - 1;
            }

            if (j >= 0) {
#line 246 "lib/sj-lib-common/array.sj"
                sjt_while6 = shouldcontinue;
            } else {
#line 246 "lib/sj-lib-common/array.sj"
                sjt_while6 = false;
            }

            if (sjt_call25._refCount == 1) { sjf_class_destroy(&sjt_call25); }
;
        }

        if (i <= j) {
            int32_t sjt_functionParam83;
            int32_t sjt_functionParam84;
            sjs_class* sjt_functionParam85 = 0;
            int32_t sjt_functionParam86;
            int32_t sjt_functionParam87;
            sjs_class* sjt_functionParam88 = 0;

#line 254 "lib/sj-lib-common/array.sj"
            sjt_functionParam83 = i;
#line 254
            sjf_array_class_getat(_parent, sjt_functionParam83, &tmp);
#line 255
            sjt_functionParam84 = i;
#line 255
            sjt_functionParam86 = j;
#line 255
            sjf_array_class_getat(_parent, sjt_functionParam86, &sjt_call26);
#line 255
            sjt_functionParam85 = &sjt_call26;
#line 255
            sjf_array_class_setat(_parent, sjt_functionParam84, sjt_functionParam85);
#line 256
            sjt_functionParam87 = j;
#line 256
            sjt_functionParam88 = &tmp;
#line 256
            sjf_array_class_setat(_parent, sjt_functionParam87, sjt_functionParam88);
#line 257
            i = i + 1;
#line 258
            j = j - 1;
        }

#line 236
        sjt_while4 = i <= j;

        if (sjt_call26._refCount == 1) { sjf_class_destroy(&sjt_call26); }
;
        if (tmp._refCount == 1) { sjf_class_destroy(&tmp); }
;
    }

    if (left < j) {
        int32_t sjt_functionParam89;
        int32_t sjt_functionParam90;
        cb_class_class_i32 sjt_functionParam91;

#line 231 "lib/sj-lib-common/array.sj"
        sjt_functionParam89 = left;
#line 263
        sjt_functionParam90 = j;
#line 231
        sjt_functionParam91 = cb;
#line 231
        sjf_array_class__quicksortcallback(_parent, sjt_functionParam89, sjt_functionParam90, sjt_functionParam91);
    }

    if (i < right) {
        int32_t sjt_functionParam92;
        int32_t sjt_functionParam93;
        cb_class_class_i32 sjt_functionParam94;

#line 266 "lib/sj-lib-common/array.sj"
        sjt_functionParam92 = i;
#line 231
        sjt_functionParam93 = right;
#line 231
        sjt_functionParam94 = cb;
#line 231
        sjf_array_class__quicksortcallback(_parent, sjt_functionParam92, sjt_functionParam93, sjt_functionParam94);
    }

    if (pivot._refCount == 1) { sjf_class_destroy(&pivot); }
;
}

void sjf_array_class_asstring(sjs_array_class* _parent, sjs_string* sep, sjs_string* _return) {
    int32_t i;
    sjs_string result = { -1 };
    int32_t sjt_forEnd1;
    int32_t sjt_forStart1;

    result._refCount = 1;
#line 292 "lib/sj-lib-common/array.sj"
    result.offset = 0;
#line 292
    result.count = 0;
#line 292
    result.data._refCount = 1;
#line 292
    result.data.v = &sjg_string2;
#line 292
    sjf_array_char(&result.data);
#line 16 "lib/sj-lib-common/string.sj"
    result._isnullterminated = false;
#line 16
    sjf_string(&result);
#line 293 "lib/sj-lib-common/array.sj"
    sjt_forStart1 = 0;
#line 293
    sjf_array_class_getcount(_parent, &sjt_forEnd1);
#line 293
    i = sjt_forStart1;
    while (i < sjt_forEnd1) {
        sjs_string sjt_call12 = { -1 };
        sjs_class sjt_call17 = { -1 };
        sjs_string sjt_funcold2 = { -1 };
        sjs_string sjt_funcold3 = { -1 };
        sjs_string* sjt_functionParam56 = 0;
        int32_t sjt_functionParam63;
        sjs_string* sjt_parent32 = 0;
        sjs_class* sjt_parent35 = 0;

        if (i != 0) {
            sjs_string* sjt_functionParam55 = 0;
            sjs_string* sjt_parent31 = 0;

            sjt_funcold2._refCount = 1;
#line 18 "lib/sj-lib-common/string.sj"
            sjf_string_copy(&sjt_funcold2, &result);
#line 18
            sjt_parent31 = &result;
#line 291 "lib/sj-lib-common/array.sj"
            sjt_functionParam55 = sep;
#line 291
            sjf_string_add(sjt_parent31, sjt_functionParam55, &sjt_funcold2);
#line 291
            if (result._refCount == 1) { sjf_string_destroy(&result); }
;
#line 18 "lib/sj-lib-common/string.sj"
            sjf_string_copy(&result, &sjt_funcold2);
        }

        sjt_funcold3._refCount = 1;
#line 18 "lib/sj-lib-common/string.sj"
        sjf_string_copy(&sjt_funcold3, &result);
#line 18
        sjt_parent32 = &result;
#line 293 "lib/sj-lib-common/array.sj"
        sjt_functionParam63 = i;
#line 293
        sjf_array_class_getat(_parent, sjt_functionParam63, &sjt_call17);
#line 297
        sjt_parent35 = &sjt_call17;
#line 297
        sjf_class_asstring(sjt_parent35, &sjt_call12);
#line 297
        sjt_functionParam56 = &sjt_call12;
#line 297
        sjf_string_add(sjt_parent32, sjt_functionParam56, &sjt_funcold3);
#line 297
        if (result._refCount == 1) { sjf_string_destroy(&result); }
;
#line 18 "lib/sj-lib-common/string.sj"
        sjf_string_copy(&result, &sjt_funcold3);
#line 293 "lib/sj-lib-common/array.sj"
        i++;

        if (sjt_call12._refCount == 1) { sjf_string_destroy(&sjt_call12); }
;
        if (sjt_call17._refCount == 1) { sjf_class_destroy(&sjt_call17); }
;
        if (sjt_funcold2._refCount == 1) { sjf_string_destroy(&sjt_funcold2); }
;
        if (sjt_funcold3._refCount == 1) { sjf_string_destroy(&sjt_funcold3); }
;
    }

#line 293
    _return->_refCount = 1;
#line 291
    sjf_string_copy(_return, &result);

    if (result._refCount == 1) { sjf_string_destroy(&result); }
;
}

void sjf_array_class_asstring_heap(sjs_array_class* _parent, sjs_string* sep, sjs_string** _return) {
    int32_t i;
    sjs_string result = { -1 };
    int32_t sjt_forEnd6;
    int32_t sjt_forStart6;

    result._refCount = 1;
#line 292 "lib/sj-lib-common/array.sj"
    result.offset = 0;
#line 292
    result.count = 0;
#line 292
    result.data._refCount = 1;
#line 292
    result.data.v = &sjg_string2;
#line 292
    sjf_array_char(&result.data);
#line 16 "lib/sj-lib-common/string.sj"
    result._isnullterminated = false;
#line 16
    sjf_string(&result);
#line 293 "lib/sj-lib-common/array.sj"
    sjt_forStart6 = 0;
#line 293
    sjf_array_class_getcount(_parent, &sjt_forEnd6);
#line 293
    i = sjt_forStart6;
    while (i < sjt_forEnd6) {
        sjs_string sjt_call18 = { -1 };
        sjs_class sjt_call19 = { -1 };
        sjs_string sjt_funcold4 = { -1 };
        sjs_string sjt_funcold5 = { -1 };
        sjs_string* sjt_functionParam65 = 0;
        int32_t sjt_functionParam66;
        sjs_string* sjt_parent37 = 0;
        sjs_class* sjt_parent38 = 0;

        if (i != 0) {
            sjs_string* sjt_functionParam64 = 0;
            sjs_string* sjt_parent36 = 0;

            sjt_funcold4._refCount = 1;
#line 18 "lib/sj-lib-common/string.sj"
            sjf_string_copy(&sjt_funcold4, &result);
#line 18
            sjt_parent36 = &result;
#line 291 "lib/sj-lib-common/array.sj"
            sjt_functionParam64 = sep;
#line 291
            sjf_string_add(sjt_parent36, sjt_functionParam64, &sjt_funcold4);
#line 291
            if (result._refCount == 1) { sjf_string_destroy(&result); }
;
#line 18 "lib/sj-lib-common/string.sj"
            sjf_string_copy(&result, &sjt_funcold4);
        }

        sjt_funcold5._refCount = 1;
#line 18 "lib/sj-lib-common/string.sj"
        sjf_string_copy(&sjt_funcold5, &result);
#line 18
        sjt_parent37 = &result;
#line 293 "lib/sj-lib-common/array.sj"
        sjt_functionParam66 = i;
#line 293
        sjf_array_class_getat(_parent, sjt_functionParam66, &sjt_call19);
#line 297
        sjt_parent38 = &sjt_call19;
#line 297
        sjf_class_asstring(sjt_parent38, &sjt_call18);
#line 297
        sjt_functionParam65 = &sjt_call18;
#line 297
        sjf_string_add(sjt_parent37, sjt_functionParam65, &sjt_funcold5);
#line 297
        if (result._refCount == 1) { sjf_string_destroy(&result); }
;
#line 18 "lib/sj-lib-common/string.sj"
        sjf_string_copy(&result, &sjt_funcold5);
#line 293 "lib/sj-lib-common/array.sj"
        i++;

        if (sjt_call18._refCount == 1) { sjf_string_destroy(&sjt_call18); }
;
        if (sjt_call19._refCount == 1) { sjf_class_destroy(&sjt_call19); }
;
        if (sjt_funcold4._refCount == 1) { sjf_string_destroy(&sjt_funcold4); }
;
        if (sjt_funcold5._refCount == 1) { sjf_string_destroy(&sjt_funcold5); }
;
    }

#line 293
    (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
#line 293
    (*_return)->_refCount = 1;
#line 291
    sjf_string_copy((*_return), &result);

    if (result._refCount == 1) { sjf_string_destroy(&result); }
;
}

void sjf_array_class_copy(sjs_array_class* _this, sjs_array_class* _from) {
#line 21 "lib/sj-lib-common/array.sj"
    _this->v = _from->v;
#line 360
    sjs_array* arr = (sjs_array*)_this->v;
#line 361
    arr->refcount++;
}

void sjf_array_class_destroy(sjs_array_class* _this) {
#line 365 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_this->v;
#line 366
    arr->refcount--;
#line 367
    if (arr->refcount == 0) {
#line 368
        #if !false && !true
#line 369
        sjs_class* p = (sjs_class*)arr->data;
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

void sjf_array_class_getat(sjs_array_class* _parent, int32_t index, sjs_class* _return) {
#line 38 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_parent->v;
#line 39
    if (index >= arr->count || index < 0) {
#line 40
        halt("getAt: out of bounds\n");
#line 41
    }
#line 42
    sjs_class* p = (sjs_class*)arr->data;
#line 43
    _return->_refCount = 1;
#line 37 "lib/sj-lib-common/array.sj"
sjf_class_copy(_return, &p[index]);
return;;       
}

void sjf_array_class_getat_heap(sjs_array_class* _parent, int32_t index, sjs_class** _return) {
#line 38 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_parent->v;
#line 39
    if (index >= arr->count || index < 0) {
#line 40
        halt("getAt: out of bounds\n");
#line 41
    }
#line 42
    sjs_class* p = (sjs_class*)arr->data;
#line 43
    (*_return) = (sjs_class*)malloc(sizeof(sjs_class));
(*_return)->_refCount = 1;
#line 37 "lib/sj-lib-common/array.sj"
sjf_class_copy((*_return), &p[index]);
return;;       
}

void sjf_array_class_getcount(sjs_array_class* _parent, int32_t* _return) {
#line 26 "lib/sj-lib-common/array.sj"
    #line 25 "lib/sj-lib-common/array.sj"
(*_return) = ((sjs_array*)_parent->v)->count;
return;;
}

void sjf_array_class_heap(sjs_array_class* _this) {
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

void sjf_array_class_initat(sjs_array_class* _parent, int32_t index, sjs_class* item) {
#line 49 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_parent->v;
#line 50
    if (index != arr->count) {
#line 51
        halt("initAt: can only initialize last element\n");     
#line 52
    }
#line 53
    if (index >= arr->size || index < 0) {
#line 54
        halt("initAt: out of bounds %d:%d\n", index, arr->size);
#line 55
    }
#line 57
    sjs_class* p = (sjs_class*)arr->data;
#line 58
    p[index]._refCount = 1;
#line 47 "lib/sj-lib-common/array.sj"
sjf_class_copy(&p[index], item);
;
#line 59
    arr->count = index + 1;
}

void sjf_array_class_reverse(sjs_array_class* _parent) {
    int32_t i;
    int32_t sjt_capture10;
    int32_t sjt_forEnd7;
    int32_t sjt_forStart7;

#line 283 "lib/sj-lib-common/array.sj"
    sjt_forStart7 = 0;
#line 283
    sjf_array_class_getcount(_parent, &sjt_capture10);
#line 283
    sjt_forEnd7 = sjt_capture10 / 2;
#line 283
    i = sjt_forStart7;
    while (i < sjt_forEnd7) {
        int32_t j;
        sjs_class sjt_call21 = { -1 };
        int32_t sjt_capture11;
        int32_t sjt_functionParam68;
        int32_t sjt_functionParam69;
        sjs_class* sjt_functionParam70 = 0;
        int32_t sjt_functionParam71;
        int32_t sjt_functionParam72;
        sjs_class* sjt_functionParam73 = 0;
        sjs_class tmp = { -1 };

        sjf_array_class_getcount(_parent, &sjt_capture11);
#line 284 "lib/sj-lib-common/array.sj"
        j = (sjt_capture11 - i) - 1;
#line 283
        sjt_functionParam68 = i;
#line 283
        sjf_array_class_getat(_parent, sjt_functionParam68, &tmp);
#line 283
        sjt_functionParam69 = i;
#line 286
        sjt_functionParam71 = j;
#line 286
        sjf_array_class_getat(_parent, sjt_functionParam71, &sjt_call21);
#line 286
        sjt_functionParam70 = &sjt_call21;
#line 286
        sjf_array_class_setat(_parent, sjt_functionParam69, sjt_functionParam70);
#line 287
        sjt_functionParam72 = j;
#line 287
        sjt_functionParam73 = &tmp;
#line 287
        sjf_array_class_setat(_parent, sjt_functionParam72, sjt_functionParam73);
#line 283
        i++;

        if (sjt_call21._refCount == 1) { sjf_class_destroy(&sjt_call21); }
;
        if (tmp._refCount == 1) { sjf_class_destroy(&tmp); }
;
    }
}

void sjf_array_class_setat(sjs_array_class* _parent, int32_t index, sjs_class* item) {
#line 65 "lib/sj-lib-common/array.sj"
    sjs_array* arr = (sjs_array*)_parent->v;
#line 66
    if (index >= arr->count || index < 0) {
#line 67
        halt("setAt: out of bounds %d:%d\n", index, arr->count);
#line 68
    }
#line 70
    sjs_class* p = (sjs_class*)arr->data;
#line 71
    ;
#line 72
    p[index]._refCount = 1;
#line 63 "lib/sj-lib-common/array.sj"
sjf_class_copy(&p[index], item);
;
}

void sjf_array_class_sort(sjs_array_class* _parent) {
    int32_t sjt_capture2;

    sjf_array_class_getcount(_parent, &sjt_capture2);
    if (sjt_capture2 > 1) {
        int32_t sjt_capture3;
        int32_t sjt_functionParam33;
        int32_t sjt_functionParam34;

#line 272 "lib/sj-lib-common/array.sj"
        sjt_functionParam33 = 0;
#line 272
        sjf_array_class_getcount(_parent, &sjt_capture3);
#line 272
        sjt_functionParam34 = sjt_capture3 - 1;
#line 272
        sjf_array_class__quicksort(_parent, sjt_functionParam33, sjt_functionParam34);
    }
}

void sjf_array_class_sortcb(sjs_array_class* _parent, cb_class_class_i32 cb) {
    int32_t sjt_capture12;

    sjf_array_class_getcount(_parent, &sjt_capture12);
    if (sjt_capture12 > 1) {
        int32_t sjt_capture17;
        int32_t sjt_functionParam95;
        int32_t sjt_functionParam96;
        cb_class_class_i32 sjt_functionParam97;

#line 278 "lib/sj-lib-common/array.sj"
        sjt_functionParam95 = 0;
#line 278
        sjf_array_class_getcount(_parent, &sjt_capture17);
#line 278
        sjt_functionParam96 = sjt_capture17 - 1;
#line 276
        sjt_functionParam97 = cb;
#line 276
        sjf_array_class__quicksortcallback(_parent, sjt_functionParam95, sjt_functionParam96, sjt_functionParam97);
    }
}

void sjf_class(sjs_class* _this) {
}

void sjf_class_asstring(sjs_class* _parent, sjs_string* _return) {
    sjs_string sjt_call13 = { -1 };
    sjs_string sjt_call14 = { -1 };
    sjs_string* sjt_functionParam57 = 0;
    int32_t sjt_functionParam58;
    int32_t sjt_functionParam59;
    sjs_string* sjt_parent33 = 0;

    sjt_call13._refCount = 1;
#line 14 "array7.sj"
    sjt_call13.offset = 0;
#line 14
    sjt_call13.count = 1;
#line 14
    sjt_call13.data._refCount = 1;
#line 14
    sjt_call13.data.v = &sjg_string3;
#line 14
    sjf_array_char(&sjt_call13.data);
#line 16 "lib/sj-lib-common/string.sj"
    sjt_call13._isnullterminated = false;
#line 16
    sjf_string(&sjt_call13);
#line 14 "array7.sj"
    sjt_parent33 = &sjt_call13;
#line 14
    sjt_functionParam58 = _parent->x;
#line 22 "lib/sj-lib-common/i32.sj"
    sjt_functionParam59 = 10;
#line 22
    sjf_i32_asstring(sjt_functionParam58, sjt_functionParam59, &sjt_call14);
#line 14 "array7.sj"
    sjt_functionParam57 = &sjt_call14;
#line 14
    sjf_string_add(sjt_parent33, sjt_functionParam57, _return);

    if (sjt_call13._refCount == 1) { sjf_string_destroy(&sjt_call13); }
;
    if (sjt_call14._refCount == 1) { sjf_string_destroy(&sjt_call14); }
;
}

void sjf_class_asstring_heap(sjs_class* _parent, sjs_string** _return) {
    sjs_string sjt_call15 = { -1 };
    sjs_string sjt_call16 = { -1 };
    sjs_string* sjt_functionParam60 = 0;
    int32_t sjt_functionParam61;
    int32_t sjt_functionParam62;
    sjs_string* sjt_parent34 = 0;

    sjt_call15._refCount = 1;
#line 14 "array7.sj"
    sjt_call15.offset = 0;
#line 14
    sjt_call15.count = 1;
#line 14
    sjt_call15.data._refCount = 1;
#line 14
    sjt_call15.data.v = &sjg_string3;
#line 14
    sjf_array_char(&sjt_call15.data);
#line 16 "lib/sj-lib-common/string.sj"
    sjt_call15._isnullterminated = false;
#line 16
    sjf_string(&sjt_call15);
#line 14 "array7.sj"
    sjt_parent34 = &sjt_call15;
#line 14
    sjt_functionParam61 = _parent->x;
#line 22 "lib/sj-lib-common/i32.sj"
    sjt_functionParam62 = 10;
#line 22
    sjf_i32_asstring(sjt_functionParam61, sjt_functionParam62, &sjt_call16);
#line 14 "array7.sj"
    sjt_functionParam60 = &sjt_call16;
#line 14
    sjf_string_add_heap(sjt_parent34, sjt_functionParam60, _return);

    if (sjt_call15._refCount == 1) { sjf_string_destroy(&sjt_call15); }
;
    if (sjt_call16._refCount == 1) { sjf_string_destroy(&sjt_call16); }
;
}

void sjf_class_compare(sjs_class* l, sjs_class* r, int32_t* _return) {
    int32_t sjt_functionParam100;
    int32_t sjt_functionParam99;

#line 19 "array7.sj"
    sjt_functionParam99 = l->x;
#line 19
    sjt_functionParam100 = r->x;
#line 19
    sjf_i32_compare(sjt_functionParam99, sjt_functionParam100, _return);
}

void sjf_class_compare_callback(void * _parent, sjs_class* l, sjs_class* r, int32_t* _return) {
    sjf_class_compare(l, r, _return);
}

void sjf_class_copy(sjs_class* _this, sjs_class* _from) {
#line 2 "array7.sj"
    _this->x = _from->x;
}

void sjf_class_destroy(sjs_class* _this) {
}

void sjf_class_heap(sjs_class* _this) {
}

void sjf_class_isgreater(sjs_class* _parent, sjs_class* c, bool* _return) {
#line 10 "array7.sj"
    (*_return) = _parent->x > c->x;
}

void sjf_class_isless(sjs_class* _parent, sjs_class* c, bool* _return) {
#line 6 "array7.sj"
    (*_return) = _parent->x < c->x;
}

void sjf_console_writeline(sjs_string* data) {
    sjs_string* sjt_parent13 = 0;

#line 9 "lib/sj-lib-common/console.sj"
    sjt_parent13 = data;
#line 9
    sjf_string_nullterminate(sjt_parent13);
#line 12
    printf("%s\n", string_char(data));
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

void sjf_i32_asstring(int32_t val, int32_t base, sjs_string* _return) {
    int32_t count;
    void* vresult;

#line 23 "lib/sj-lib-common/i32.sj"
    count = 0;
#line 24
    vresult = 0;
#line 26
    sjs_array* arr = createarray(256);
#line 27
    vresult = (void*)arr;
#line 28
    char *tmp = (char*)arr->data + 128;
#line 29
    char *tp = (char*)arr->data + 128;
#line 30
    int i;
#line 31
    unsigned v;
#line 33
    int sign = (base == 10 && val < 0);    
#line 34
    if (sign)
#line 35
    v = -val;
#line 36
    else
#line 37
    v = (unsigned)val;
#line 39
    while (v || tp == tmp)
#line 40
    {
#line 41
        i = v % base;
#line 42
        v /= base; // v/=base uses less CPU clocks than v=v/base does
#line 43
        if (i < 10)
#line 44
        *tp++ = i + '0';
#line 45
        else
#line 46
        *tp++ = i + 'a' - 10;
#line 47
    }
#line 49
    int len = tp - tmp;
#line 51
    char* sp = (char*)arr->data;
#line 52
    if (sign) 
#line 53
    {
#line 54
        *sp++ = '-';
#line 55
        len++;
#line 56
    }
#line 58
    while (tp > tmp)
#line 59
    *sp++ = *--tp;
#line 61
    arr->count = len;
#line 62
    count = len;
#line 62
    _return->_refCount = 1;
#line 13 "lib/sj-lib-common/string.sj"
    _return->offset = 0;
#line 64 "lib/sj-lib-common/i32.sj"
    _return->count = count;
#line 64
    _return->data._refCount = 1;
#line 64
    _return->data.v = vresult;
#line 64
    sjf_array_char(&_return->data);
#line 16 "lib/sj-lib-common/string.sj"
    _return->_isnullterminated = false;
#line 16
    sjf_string(_return);
}

void sjf_i32_asstring_heap(int32_t val, int32_t base, sjs_string** _return) {
    int32_t count;
    void* vresult;

#line 23 "lib/sj-lib-common/i32.sj"
    count = 0;
#line 24
    vresult = 0;
#line 26
    sjs_array* arr = createarray(256);
#line 27
    vresult = (void*)arr;
#line 28
    char *tmp = (char*)arr->data + 128;
#line 29
    char *tp = (char*)arr->data + 128;
#line 30
    int i;
#line 31
    unsigned v;
#line 33
    int sign = (base == 10 && val < 0);    
#line 34
    if (sign)
#line 35
    v = -val;
#line 36
    else
#line 37
    v = (unsigned)val;
#line 39
    while (v || tp == tmp)
#line 40
    {
#line 41
        i = v % base;
#line 42
        v /= base; // v/=base uses less CPU clocks than v=v/base does
#line 43
        if (i < 10)
#line 44
        *tp++ = i + '0';
#line 45
        else
#line 46
        *tp++ = i + 'a' - 10;
#line 47
    }
#line 49
    int len = tp - tmp;
#line 51
    char* sp = (char*)arr->data;
#line 52
    if (sign) 
#line 53
    {
#line 54
        *sp++ = '-';
#line 55
        len++;
#line 56
    }
#line 58
    while (tp > tmp)
#line 59
    *sp++ = *--tp;
#line 61
    arr->count = len;
#line 62
    count = len;
#line 62
    (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
#line 62
    (*_return)->_refCount = 1;
#line 13 "lib/sj-lib-common/string.sj"
    (*_return)->offset = 0;
#line 64 "lib/sj-lib-common/i32.sj"
    (*_return)->count = count;
#line 64
    (*_return)->data._refCount = 1;
#line 64
    (*_return)->data.v = vresult;
#line 64
    sjf_array_char(&(*_return)->data);
#line 16 "lib/sj-lib-common/string.sj"
    (*_return)->_isnullterminated = false;
#line 16
    sjf_string_heap((*_return));
}

void sjf_i32_compare(int32_t l, int32_t r, int32_t* _return) {
    if (l == r) {
#line 69 "lib/sj-lib-common/i32.sj"
        (*_return) = 0;
    } else {
        if (l < r) {
            int32_t result3;

#line 71 "lib/sj-lib-common/i32.sj"
            result3 = -1;
#line 71
            (*_return) = result3;
        } else {
#line 73 "lib/sj-lib-common/i32.sj"
            (*_return) = 1;
        }
    }
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

void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return) {
    sjs_array_char newdata = { -1 };

    if (item->count == 0) {
        _return->_refCount = 1;
#line 20 "lib/sj-lib-common/string.sj"
        sjf_string_copy(_return, _parent);
    } else {
        bool sjt_capture4;
        int32_t sjt_capture5;
        sjs_array_char* sjt_parent14 = 0;

#line 30 "lib/sj-lib-common/array.sj"
        sjt_parent14 = &_parent->data;
#line 30
        sjf_array_char_getsize(sjt_parent14, &sjt_capture5);
        if (((_parent->offset + _parent->count) + item->count) < sjt_capture5) {
            int32_t sjt_capture6;
            sjs_array_char* sjt_parent15 = 0;

#line 24 "lib/sj-lib-common/array.sj"
            sjt_parent15 = &_parent->data;
#line 24
            sjf_array_char_getcount(sjt_parent15, &sjt_capture6);
#line 24 "lib/sj-lib-common/string.sj"
            sjt_capture4 = ((_parent->offset + _parent->count) == sjt_capture6);
        } else {
#line 24 "lib/sj-lib-common/string.sj"
            sjt_capture4 = false;
        }

        if (sjt_capture4) {
            int32_t i;
            int32_t newcount;
            int32_t sjt_forEnd2;
            int32_t sjt_forStart2;

#line 25 "lib/sj-lib-common/string.sj"
            newcount = _parent->count;
#line 27
            sjt_forStart2 = 0;
#line 27
            sjt_forEnd2 = item->count;
#line 27
            i = sjt_forStart2;
            while (i < sjt_forEnd2) {
                int32_t sjt_functionParam36;
                char sjt_functionParam37;
                int32_t sjt_functionParam39;
                sjs_array_char* sjt_parent16 = 0;
                sjs_string* sjt_parent18 = 0;

#line 47 "lib/sj-lib-common/array.sj"
                sjt_parent16 = &_parent->data;
#line 28 "lib/sj-lib-common/string.sj"
                sjt_functionParam36 = newcount;
#line 18
                sjt_parent18 = item;
#line 27
                sjt_functionParam39 = i;
#line 27
                sjf_string_getat(sjt_parent18, sjt_functionParam39, &sjt_functionParam37);
#line 27
                sjf_array_char_initat(sjt_parent16, sjt_functionParam36, sjt_functionParam37);
#line 29
                newcount = newcount + 1;
#line 27
                i++;
            }

#line 27
            _return->_refCount = 1;
#line 32
            _return->offset = _parent->offset;
#line 32
            _return->count = newcount;
#line 32
            _return->data._refCount = 1;
#line 32
            sjf_array_char_copy(&_return->data, &_parent->data);
#line 16
            _return->_isnullterminated = false;
#line 16
            sjf_string(_return);
        } else {
            int32_t i;
            int32_t newcount;
            int32_t sjt_forEnd3;
            int32_t sjt_forStart3;
            int32_t sjt_functionParam40;
            int32_t sjt_functionParam41;
            int32_t sjt_functionParam42;
            sjs_array_char* sjt_parent19 = 0;
            sjs_array_char* sjt_parent20 = 0;

#line 164 "lib/sj-lib-common/array.sj"
            sjt_parent19 = &_parent->data;
#line 34 "lib/sj-lib-common/string.sj"
            sjt_functionParam40 = _parent->offset;
#line 34
            sjt_functionParam41 = _parent->count;
#line 34
            sjt_functionParam42 = ((((_parent->count + item->count) - 1) / 256) + 1) * 256;
#line 34
            sjf_array_char_clone(sjt_parent19, sjt_functionParam40, sjt_functionParam41, sjt_functionParam42, &newdata);
#line 24 "lib/sj-lib-common/array.sj"
            sjt_parent20 = &newdata;
#line 24
            sjf_array_char_getcount(sjt_parent20, &newcount);
#line 37 "lib/sj-lib-common/string.sj"
            sjt_forStart3 = 0;
#line 37
            sjt_forEnd3 = item->count;
#line 37
            i = sjt_forStart3;
            while (i < sjt_forEnd3) {
                int32_t sjt_functionParam43;
                char sjt_functionParam44;
                int32_t sjt_functionParam45;
                sjs_array_char* sjt_parent21 = 0;
                sjs_string* sjt_parent22 = 0;

#line 47 "lib/sj-lib-common/array.sj"
                sjt_parent21 = &newdata;
#line 38 "lib/sj-lib-common/string.sj"
                sjt_functionParam43 = newcount;
#line 18
                sjt_parent22 = item;
#line 37
                sjt_functionParam45 = i;
#line 37
                sjf_string_getat(sjt_parent22, sjt_functionParam45, &sjt_functionParam44);
#line 37
                sjf_array_char_initat(sjt_parent21, sjt_functionParam43, sjt_functionParam44);
#line 39
                newcount = newcount + 1;
#line 37
                i++;
            }

#line 37
            _return->_refCount = 1;
#line 42
            _return->offset = 0;
#line 42
            _return->count = newcount;
#line 42
            _return->data._refCount = 1;
#line 42
            sjf_array_char_copy(&_return->data, &newdata);
#line 16
            _return->_isnullterminated = false;
#line 16
            sjf_string(_return);
        }
    }

    if (newdata._refCount == 1) { sjf_array_char_destroy(&newdata); }
;
}

void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string** _return) {
    sjs_array_char newdata = { -1 };

    if (item->count == 0) {
        (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
        (*_return)->_refCount = 1;
#line 20 "lib/sj-lib-common/string.sj"
        sjf_string_copy((*_return), _parent);
    } else {
        bool sjt_capture7;
        int32_t sjt_capture8;
        sjs_array_char* sjt_parent23 = 0;

#line 30 "lib/sj-lib-common/array.sj"
        sjt_parent23 = &_parent->data;
#line 30
        sjf_array_char_getsize(sjt_parent23, &sjt_capture8);
        if (((_parent->offset + _parent->count) + item->count) < sjt_capture8) {
            int32_t sjt_capture9;
            sjs_array_char* sjt_parent24 = 0;

#line 24 "lib/sj-lib-common/array.sj"
            sjt_parent24 = &_parent->data;
#line 24
            sjf_array_char_getcount(sjt_parent24, &sjt_capture9);
#line 24 "lib/sj-lib-common/string.sj"
            sjt_capture7 = ((_parent->offset + _parent->count) == sjt_capture9);
        } else {
#line 24 "lib/sj-lib-common/string.sj"
            sjt_capture7 = false;
        }

        if (sjt_capture7) {
            int32_t i;
            int32_t newcount;
            int32_t sjt_forEnd4;
            int32_t sjt_forStart4;

#line 25 "lib/sj-lib-common/string.sj"
            newcount = _parent->count;
#line 27
            sjt_forStart4 = 0;
#line 27
            sjt_forEnd4 = item->count;
#line 27
            i = sjt_forStart4;
            while (i < sjt_forEnd4) {
                int32_t sjt_functionParam46;
                char sjt_functionParam47;
                int32_t sjt_functionParam48;
                sjs_array_char* sjt_parent25 = 0;
                sjs_string* sjt_parent26 = 0;

#line 47 "lib/sj-lib-common/array.sj"
                sjt_parent25 = &_parent->data;
#line 28 "lib/sj-lib-common/string.sj"
                sjt_functionParam46 = newcount;
#line 18
                sjt_parent26 = item;
#line 27
                sjt_functionParam48 = i;
#line 27
                sjf_string_getat(sjt_parent26, sjt_functionParam48, &sjt_functionParam47);
#line 27
                sjf_array_char_initat(sjt_parent25, sjt_functionParam46, sjt_functionParam47);
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
            (*_return)->offset = _parent->offset;
#line 32
            (*_return)->count = newcount;
#line 32
            (*_return)->data._refCount = 1;
#line 32
            sjf_array_char_copy(&(*_return)->data, &_parent->data);
#line 16
            (*_return)->_isnullterminated = false;
#line 16
            sjf_string_heap((*_return));
        } else {
            int32_t i;
            int32_t newcount;
            int32_t sjt_forEnd5;
            int32_t sjt_forStart5;
            int32_t sjt_functionParam49;
            int32_t sjt_functionParam50;
            int32_t sjt_functionParam51;
            sjs_array_char* sjt_parent27 = 0;
            sjs_array_char* sjt_parent28 = 0;

#line 164 "lib/sj-lib-common/array.sj"
            sjt_parent27 = &_parent->data;
#line 34 "lib/sj-lib-common/string.sj"
            sjt_functionParam49 = _parent->offset;
#line 34
            sjt_functionParam50 = _parent->count;
#line 34
            sjt_functionParam51 = ((((_parent->count + item->count) - 1) / 256) + 1) * 256;
#line 34
            sjf_array_char_clone(sjt_parent27, sjt_functionParam49, sjt_functionParam50, sjt_functionParam51, &newdata);
#line 24 "lib/sj-lib-common/array.sj"
            sjt_parent28 = &newdata;
#line 24
            sjf_array_char_getcount(sjt_parent28, &newcount);
#line 37 "lib/sj-lib-common/string.sj"
            sjt_forStart5 = 0;
#line 37
            sjt_forEnd5 = item->count;
#line 37
            i = sjt_forStart5;
            while (i < sjt_forEnd5) {
                int32_t sjt_functionParam52;
                char sjt_functionParam53;
                int32_t sjt_functionParam54;
                sjs_array_char* sjt_parent29 = 0;
                sjs_string* sjt_parent30 = 0;

#line 47 "lib/sj-lib-common/array.sj"
                sjt_parent29 = &newdata;
#line 38 "lib/sj-lib-common/string.sj"
                sjt_functionParam52 = newcount;
#line 18
                sjt_parent30 = item;
#line 37
                sjt_functionParam54 = i;
#line 37
                sjf_string_getat(sjt_parent30, sjt_functionParam54, &sjt_functionParam53);
#line 37
                sjf_array_char_initat(sjt_parent29, sjt_functionParam52, sjt_functionParam53);
#line 39
                newcount = newcount + 1;
#line 37
                i++;
            }

#line 37
            (*_return) = (sjs_string*)malloc(sizeof(sjs_string));
#line 37
            (*_return)->_refCount = 1;
#line 42
            (*_return)->offset = 0;
#line 42
            (*_return)->count = newcount;
#line 42
            (*_return)->data._refCount = 1;
#line 42
            sjf_array_char_copy(&(*_return)->data, &newdata);
#line 16
            (*_return)->_isnullterminated = false;
#line 16
            sjf_string_heap((*_return));
        }
    }

    if (newdata._refCount == 1) { sjf_array_char_destroy(&newdata); }
;
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

void sjf_string_getat(sjs_string* _parent, int32_t index, char* _return) {
    int32_t sjt_functionParam38;
    sjs_array_char* sjt_parent17 = 0;

#line 36 "lib/sj-lib-common/array.sj"
    sjt_parent17 = &_parent->data;
#line 64 "lib/sj-lib-common/string.sj"
    sjt_functionParam38 = _parent->offset + index;
#line 64
    sjf_array_char_getat(sjt_parent17, sjt_functionParam38, _return);
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
#line 23 "array7.sj"
    g_a.v = createarray(5 * sizeof(sjs_class));
#line 23
    sjf_array_class(&g_a);
#line 23
    sjs_array_class* array1;
#line 23
    array1 = &g_a;
#line 23
    sjt_parent3 = array1;
#line 23
    sjt_functionParam4 = 0;
#line 23
    sjt_call1._refCount = 1;
#line 23
    sjt_call1.x = 1;
#line 23
    sjf_class(&sjt_call1);
#line 23
    sjt_functionParam5 = &sjt_call1;
#line 23
    sjf_array_class_initat(sjt_parent3, sjt_functionParam4, sjt_functionParam5);
#line 23
    sjt_parent4 = array1;
#line 23
    sjt_functionParam6 = 1;
#line 23
    sjt_call2._refCount = 1;
#line 23
    sjt_call2.x = 4;
#line 23
    sjf_class(&sjt_call2);
#line 23
    sjt_functionParam7 = &sjt_call2;
#line 23
    sjf_array_class_initat(sjt_parent4, sjt_functionParam6, sjt_functionParam7);
#line 23
    sjt_parent5 = array1;
#line 23
    sjt_functionParam8 = 2;
#line 23
    sjt_call3._refCount = 1;
#line 23
    sjt_call3.x = 5;
#line 23
    sjf_class(&sjt_call3);
#line 23
    sjt_functionParam9 = &sjt_call3;
#line 23
    sjf_array_class_initat(sjt_parent5, sjt_functionParam8, sjt_functionParam9);
#line 23
    sjt_parent6 = array1;
#line 23
    sjt_functionParam10 = 3;
#line 23
    sjt_call4._refCount = 1;
#line 23
    sjt_call4.x = 6;
#line 23
    sjf_class(&sjt_call4);
#line 23
    sjt_functionParam11 = &sjt_call4;
#line 23
    sjf_array_class_initat(sjt_parent6, sjt_functionParam10, sjt_functionParam11);
#line 23
    sjt_parent7 = array1;
#line 23
    sjt_functionParam12 = 4;
#line 23
    sjt_call5._refCount = 1;
#line 23
    sjt_call5.x = 2;
#line 23
    sjf_class(&sjt_call5);
#line 23
    sjt_functionParam13 = &sjt_call5;
#line 23
    sjf_array_class_initat(sjt_parent7, sjt_functionParam12, sjt_functionParam13);
#line 270 "lib/sj-lib-common/array.sj"
    sjt_parent12 = &g_a;
#line 270
    sjf_array_class_sort(sjt_parent12);
#line 291
    sjt_parent39 = &g_a;
#line 291
    sjt_call20._refCount = 1;
#line 291
    sjt_call20.offset = 0;
#line 291
    sjt_call20.count = 2;
#line 291
    sjt_call20.data._refCount = 1;
#line 291
    sjt_call20.data.v = &sjg_string1;
#line 291
    sjf_array_char(&sjt_call20.data);
#line 16 "lib/sj-lib-common/string.sj"
    sjt_call20._isnullterminated = false;
#line 16
    sjf_string(&sjt_call20);
#line 291 "lib/sj-lib-common/array.sj"
    sjt_functionParam67 = &sjt_call20;
#line 291
    sjf_array_class_asstring(sjt_parent39, sjt_functionParam67, &sjt_call11);
#line 25 "array7.sj"
    sjt_functionParam35 = &sjt_call11;
#line 25
    sjf_console_writeline(sjt_functionParam35);
#line 282 "lib/sj-lib-common/array.sj"
    sjt_parent40 = &g_a;
#line 282
    sjf_array_class_reverse(sjt_parent40);
#line 291
    sjt_parent41 = &g_a;
#line 291
    sjt_call23._refCount = 1;
#line 291
    sjt_call23.offset = 0;
#line 291
    sjt_call23.count = 2;
#line 291
    sjt_call23.data._refCount = 1;
#line 291
    sjt_call23.data.v = &sjg_string1;
#line 291
    sjf_array_char(&sjt_call23.data);
#line 16 "lib/sj-lib-common/string.sj"
    sjt_call23._isnullterminated = false;
#line 16
    sjf_string(&sjt_call23);
#line 291 "lib/sj-lib-common/array.sj"
    sjt_functionParam75 = &sjt_call23;
#line 291
    sjf_array_class_asstring(sjt_parent41, sjt_functionParam75, &sjt_call22);
#line 28 "array7.sj"
    sjt_functionParam74 = &sjt_call22;
#line 28
    sjf_console_writeline(sjt_functionParam74);
#line 276 "lib/sj-lib-common/array.sj"
    sjt_parent42 = &g_a;
#line 30 "array7.sj"
    sjt_functionParam98._parent = (sjs_object*)1;
#line 30
    sjt_functionParam98._cb = (void(*)(sjs_object*,sjs_class*,sjs_class*, int32_t*))sjf_class_compare_callback;
#line 30
    sjf_array_class_sortcb(sjt_parent42, sjt_functionParam98);
#line 291 "lib/sj-lib-common/array.sj"
    sjt_parent43 = &g_a;
#line 291
    sjt_call28._refCount = 1;
#line 291
    sjt_call28.offset = 0;
#line 291
    sjt_call28.count = 2;
#line 291
    sjt_call28.data._refCount = 1;
#line 291
    sjt_call28.data.v = &sjg_string1;
#line 291
    sjf_array_char(&sjt_call28.data);
#line 16 "lib/sj-lib-common/string.sj"
    sjt_call28._isnullterminated = false;
#line 16
    sjf_string(&sjt_call28);
#line 291 "lib/sj-lib-common/array.sj"
    sjt_functionParam102 = &sjt_call28;
#line 291
    sjf_array_class_asstring(sjt_parent43, sjt_functionParam102, &sjt_call27);
#line 31 "array7.sj"
    sjt_functionParam101 = &sjt_call27;
#line 31
    sjf_console_writeline(sjt_functionParam101);
    main_destroy();
    return 0;
}

void main_destroy() {

    if (g_a._refCount == 1) { sjf_array_class_destroy(&g_a); }
;
    if (g_log._refCount == 1) { sjf_log_destroy(&g_log); }
;
    if (g_log_excludeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_excludeall); }
;
    if (g_log_includeall._refCount == 1) { sjf_hash_type_bool_destroy(&g_log_includeall); }
;
    if (sjt_call1._refCount == 1) { sjf_class_destroy(&sjt_call1); }
;
    if (sjt_call11._refCount == 1) { sjf_string_destroy(&sjt_call11); }
;
    if (sjt_call2._refCount == 1) { sjf_class_destroy(&sjt_call2); }
;
    if (sjt_call20._refCount == 1) { sjf_string_destroy(&sjt_call20); }
;
    if (sjt_call22._refCount == 1) { sjf_string_destroy(&sjt_call22); }
;
    if (sjt_call23._refCount == 1) { sjf_string_destroy(&sjt_call23); }
;
    if (sjt_call27._refCount == 1) { sjf_string_destroy(&sjt_call27); }
;
    if (sjt_call28._refCount == 1) { sjf_string_destroy(&sjt_call28); }
;
    if (sjt_call3._refCount == 1) { sjf_class_destroy(&sjt_call3); }
;
    if (sjt_call4._refCount == 1) { sjf_class_destroy(&sjt_call4); }
;
    if (sjt_call5._refCount == 1) { sjf_class_destroy(&sjt_call5); }
;
    if (sjt_value1._refCount == 1) { sjf_hash_type_bool_destroy(&sjt_value1); }
;
}
