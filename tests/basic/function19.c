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

typedef struct td_void_option void_option;
struct td_void_option {
    bool isEmpty;
    void* value;
};
const void_option void_empty = { true };

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

typedef struct td_sjs_object sjs_object;

struct td_sjs_object {
    intptr_t _refCount;
};

int32_t sjt_functionParam2;
int32_t void1;

void sjf_func(int32_t x, int32_t* _return);
void main_destroy(void);

void sjf_func(int32_t x, int32_t* _return) {
    int32_t sjt_compare1;
    int32_t sjt_compare2;
    bool sjt_ifElse1;

#line 1 "function19.sj"
    sjt_compare1 = x;
#line 2
    sjt_compare2 = 0;
#line 2
    sjt_ifElse1 = sjt_compare1 > sjt_compare2;
    if (sjt_ifElse1) {
        int32_t sjt_functionParam1;
        int32_t sjt_math1;
        int32_t sjt_math2;

#line 1 "function19.sj"
        sjt_math1 = x;
#line 3
        sjt_math2 = 1;
#line 3
        sjt_functionParam1 = sjt_math1 - sjt_math2;
#line 3
        sjf_func(sjt_functionParam1, _return);
    } else {
#line 5 "function19.sj"
        (*_return) = 0;
    }
}

int main(int argc, char** argv) {
#line 8 "function19.sj"
    sjt_functionParam2 = 4;
#line 8
    sjf_func(sjt_functionParam2, &void1);
    main_destroy();
    return 0;
}

void main_destroy() {
}
