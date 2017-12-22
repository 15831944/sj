#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

int32_t result1;
int32_t sjt_math1;
int32_t sjt_math2;
int32_t sjt_negate1;

void main_destroy(void);

int main(int argc, char** argv) {
    sjt_negate1 = 4;
    result1 = -sjt_negate1;
    sjt_math1 = result1;
    sjt_math2 = 5;
    main_destroy();
    #ifdef _DEBUG
    printf("\npress return to end\n");
    getchar();
    #endif
    return 0;
}

void main_destroy() {
}
