#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct td_int32_option int32_option;
struct td_int32_option {
    bool isempty;
    int32_t value;
};
const int32_option int32_empty = { true };

typedef struct td_uint32_option uint32_option;
struct td_uint32_option {
    bool isempty;
    uint32_t value;
};
const uint32_option uint32_empty = { true };

typedef struct td_int64_option int64_option;
struct td_int64_option {
    bool isempty;
    int64_t value;
};
const int64_option int64_empty = { true };

typedef struct td_uint64_option uint64_option;
struct td_uint64_option {
    bool isempty;
    uint64_t value;
};
const uint64_option uint64_empty = { true };

typedef struct td_void_option void_option;
struct td_void_option {
    bool isempty;
    void* value;
};
const void_option void_empty = { true };

typedef struct td_char_option char_option;
struct td_char_option {
    bool isempty;
    char value;
};
const char_option char_empty = { true };

typedef struct td_float_option float_option;
struct td_float_option {
    bool isempty;
    float value;
};
const float_option float_empty = { true };

typedef struct td_double_option double_option;
struct td_double_option {
    bool isempty;
    double value;
};
const double_option double_empty = { true };

#define sjs_object_typeId 1
#define sjs_class_anon1_typeId 2
#define sjs_class_anon1_heap_typeId 3
#define sjs_class_typeId 4
#define sjs_class_heap_typeId 5

typedef struct td_sjs_object sjs_object;
typedef struct td_sjs_class_anon1 sjs_class_anon1;
typedef struct td_sjs_class_anon1_heap sjs_class_anon1_heap;
typedef struct td_sjs_class sjs_class;
typedef struct td_sjs_class_heap sjs_class_heap;

struct td_sjs_object {
    intptr_t _refCount;
};

struct td_sjs_class_anon1 {
    int32_t x;
};

struct td_sjs_class_anon1_heap {
    intptr_t _refCount;
    int32_t x;
};

struct td_sjs_class {
    sjs_class_anon1 data;
};

struct td_sjs_class_heap {
    intptr_t _refCount;
    sjs_class_anon1 data;
};

sjs_class* sjt_parent1;
sjs_class sjv_c;
sjs_class_anon1* sjv_d;

void sjf_class(sjs_class* _this);
void sjf_class_anon1(sjs_class_anon1* _this, sjs_class* _parent);
void sjf_class_anon1_copy(sjs_class_anon1* _this, sjs_class_anon1* _from);
void sjf_class_anon1_destroy(sjs_class_anon1* _this);
void sjf_class_anon1_heap(sjs_class_anon1_heap* _this, sjs_class* _parent);
void sjf_class_copy(sjs_class* _this, sjs_class* _from);
void sjf_class_destroy(sjs_class* _this);
void sjf_class_get(sjs_class* _parent, sjs_class_anon1** _return);
void sjf_class_heap(sjs_class_heap* _this);
void main_destroy(void);

void sjf_class(sjs_class* _this) {
}

void sjf_class_anon1(sjs_class_anon1* _this, sjs_class* _parent) {
}

void sjf_class_anon1_copy(sjs_class_anon1* _this, sjs_class_anon1* _from) {
#line 2 "heap2.sj"
    _this->x = _from->x;
}

void sjf_class_anon1_destroy(sjs_class_anon1* _this) {
}

void sjf_class_anon1_heap(sjs_class_anon1_heap* _this, sjs_class* _parent) {
}

void sjf_class_copy(sjs_class* _this, sjs_class* _from) {
#line 1 "heap2.sj"
    sjf_class_anon1_copy(&_this->data, &_from->data);
}

void sjf_class_destroy(sjs_class* _this) {
}

void sjf_class_get(sjs_class* _parent, sjs_class_anon1** _return) {
    sjs_class* sjt_dot1;

#line 6 "heap2.sj"
    sjt_dot1 = _parent;
#line 6
    (*_return) = &(sjt_dot1)->data;
}

void sjf_class_heap(sjs_class_heap* _this) {
}

int main(int argc, char** argv) {
#line 3 "heap2.sj"
    sjv_c.data.x = 0;
#line 3
    sjf_class_anon1(&sjv_c.data, &sjv_c);
#line 3
    sjf_class(&sjv_c);
#line 6
    sjt_parent1 = &sjv_c;
#line 6
    sjf_class_get(sjt_parent1, &sjv_d);
    main_destroy();
    return 0;
}

void main_destroy() {

    sjf_class_destroy(&sjv_c);
}
