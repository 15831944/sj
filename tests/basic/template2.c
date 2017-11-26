#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct td_int32_option int32_option;
struct td_int32_option {
    bool isEmpty;
    int32_t value;
};
const int32_option int32_empty = { true };

typedef struct td_uint32_option uint32_option;
struct td_uint32_option {
    bool isEmpty;
    uint32_t value;
};
const uint32_option uint32_empty = { true };

typedef struct td_int64_option int64_option;
struct td_int64_option {
    bool isEmpty;
    int64_t value;
};
const int64_option int64_empty = { true };

typedef struct td_uint64_option uint64_option;
struct td_uint64_option {
    bool isEmpty;
    uint64_t value;
};
const uint64_option uint64_empty = { true };

typedef struct td_uintptr_option uintptr_option;
struct td_uintptr_option {
    bool isEmpty;
    uintptr_t value;
};
const uintptr_option uintptr_empty = { true };

typedef struct td_char_option char_option;
struct td_char_option {
    bool isEmpty;
    char value;
};
const char_option char_empty = { true };

typedef struct td_float_option float_option;
struct td_float_option {
    bool isEmpty;
    float value;
};
const float_option float_empty = { true };

typedef struct td_double_option double_option;
struct td_double_option {
    bool isEmpty;
    double value;
};
const double_option double_empty = { true };

#define sjs_object_typeId 1
#define sjs_class_i32_typeId 2
#define sjs_class_i32_heap_typeId 3

typedef struct td_sjs_object sjs_object;
typedef struct td_sjs_class_i32 sjs_class_i32;
typedef struct td_sjs_class_i32_heap sjs_class_i32_heap;

struct td_sjs_object {
    int _refCount;
};

struct td_sjs_class_i32 {
    int32_t x;
};

struct td_sjs_class_i32_heap {
    int _refCount;
    int32_t x;
};

sjs_class_i32 c;
int32_t dotTemp1;
sjs_class_i32* sjt_dot1;

void sjf_class_i32(sjs_class_i32* _this);
void sjf_class_i32_copy(sjs_class_i32* _this, sjs_class_i32* to);
void sjf_class_i32_destroy(sjs_class_i32* _this);
void sjf_class_i32_heap(sjs_class_i32_heap* _this);
void main_destroy();

void sjf_class_i32(sjs_class_i32* _this) {
}

void sjf_class_i32_copy(sjs_class_i32* _this, sjs_class_i32* to) {
    _this->x = to->x;
}

void sjf_class_i32_destroy(sjs_class_i32* _this) {
}

void sjf_class_i32_heap(sjs_class_i32_heap* _this) {
}

int main() {
    c.x = 1;
    sjf_class_i32(&c);
    sjt_dot1 = &c;
    dotTemp1 = sjt_dot1->x;
    main_destroy();
    return 0;
}

void main_destroy() {

    sjf_class_i32_destroy(&c);
}
