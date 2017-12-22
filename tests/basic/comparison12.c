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

double result1;
double sjt_compare1;
double sjt_compare2;
double sjt_negate1;
bool sjv_x;

void main_destroy(void);

int main(int argc, char** argv) {
    sjt_negate1 = 3.0;
    result1 = -sjt_negate1;
    sjt_compare1 = result1;
    sjt_compare2 = 4.0;
    sjv_x = sjt_compare1 > sjt_compare2;
    main_destroy();
    #ifdef _DEBUG
    printf("\npress return to end\n");
    getchar();
    #endif
    return 0;
}

void main_destroy() {
}
