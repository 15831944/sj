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
#define sjs_interface_typeId 2

typedef struct td_sjs_object sjs_object;
typedef struct td_sjs_interface sjs_interface;

struct td_sjs_object {
    intptr_t _refCount;
};

struct td_sjs_interface {
    sjs_object* _parent;
    void* _vtbl;
};

int32_t sjt_compare1;
int32_t sjt_compare2;
bool sjt_while1;
int32_t sjv_x;

void main_destroy(void);

int main(int argc, char** argv) {
    sjv_x = 10;
    sjt_compare1 = sjv_x;
    sjt_compare2 = 0;
    sjt_while1 = sjt_compare1 > sjt_compare2;
    while (sjt_while1) {
        int32_t sjt_compare3;
        int32_t sjt_compare4;
        int32_t sjt_math1;
        int32_t sjt_math2;

        sjt_math1 = sjv_x;
        sjt_math2 = 1;
        sjv_x = sjt_math1 - sjt_math2;
        sjt_compare3 = sjv_x;
        sjt_compare4 = 0;
        sjt_while1 = sjt_compare3 > sjt_compare4;
    }
    main_destroy();
    #ifdef _DEBUG
    printf("\npress return to end\n");
    getchar();
    #endif
    return 0;
}

void main_destroy() {
}
