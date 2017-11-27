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
#define sjs_a_typeId 2
#define sjs_a_heap_typeId 3
#define sjs_b_typeId 4
#define sjs_b_heap_typeId 5
#define sjs_c_typeId 6
#define sjs_c_heap_typeId 7

typedef struct td_sjs_object sjs_object;
typedef struct td_sjs_a sjs_a;
typedef struct td_sjs_a_heap sjs_a_heap;
typedef struct td_sjs_b sjs_b;
typedef struct td_sjs_b_heap sjs_b_heap;
typedef struct td_sjs_c sjs_c;
typedef struct td_sjs_c_heap sjs_c_heap;

struct td_sjs_object {
    int _refCount;
};

struct td_sjs_a {
    int structsNeedAValue;
};

struct td_sjs_a_heap {
    int _refCount;
};

struct td_sjs_b {
    sjs_a a;
};

struct td_sjs_b_heap {
    int _refCount;
    sjs_a a;
};

struct td_sjs_c {
    sjs_b b;
};

struct td_sjs_c_heap {
    int _refCount;
    sjs_b b;
};

sjs_c void1;

void sjf_a(sjs_a* _this);
void sjf_a_copy(sjs_a* _this, sjs_a* to);
void sjf_a_destroy(sjs_a* _this);
void sjf_a_heap(sjs_a_heap* _this);
void sjf_b(sjs_b* _this);
void sjf_b_copy(sjs_b* _this, sjs_b* to);
void sjf_b_destroy(sjs_b* _this);
void sjf_b_heap(sjs_b_heap* _this);
void sjf_c(sjs_c* _this);
void sjf_c_copy(sjs_c* _this, sjs_c* to);
void sjf_c_destroy(sjs_c* _this);
void sjf_c_heap(sjs_c_heap* _this);
void main_destroy(void);

void sjf_a(sjs_a* _this) {
}

void sjf_a_copy(sjs_a* _this, sjs_a* to) {
}

void sjf_a_destroy(sjs_a* _this) {
}

void sjf_a_heap(sjs_a_heap* _this) {
}

void sjf_b(sjs_b* _this) {
}

void sjf_b_copy(sjs_b* _this, sjs_b* to) {
    sjf_a_copy(&_this->a, &to->a);
}

void sjf_b_destroy(sjs_b* _this) {
}

void sjf_b_heap(sjs_b_heap* _this) {
}

void sjf_c(sjs_c* _this) {
}

void sjf_c_copy(sjs_c* _this, sjs_c* to) {
    sjf_b_copy(&_this->b, &to->b);
}

void sjf_c_destroy(sjs_c* _this) {
}

void sjf_c_heap(sjs_c_heap* _this) {
}

int main() {
    sjf_a(&void1.b.a);
    sjf_b(&void1.b);
    sjf_c(&void1);
    main_destroy();
    return 0;
}

void main_destroy() {

    sjf_c_destroy(&void1);
}
