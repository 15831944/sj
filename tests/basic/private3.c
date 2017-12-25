#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define sjs_object_typeId 1
#define sjs_interface_typeId 2
#define sjs_class_typeId 3

typedef struct td_sjs_object sjs_object;
typedef struct td_sjs_interface sjs_interface;
typedef struct td_sjs_class sjs_class;

struct td_sjs_object {
    intptr_t _refCount;
};

struct td_sjs_interface {
    sjs_object* _parent;
    void* _vtbl;
};

struct td_sjs_class {
    int _refCount;
    int32_t x;
    int32_t _y;
};

sjs_class* sjt_parent1 = 0;
int32_t sjv_a;
sjs_class sjv_c = { -1 };

void sjf_class(sjs_class* _this);
void sjf_class__func(sjs_class* _parent, int32_t* _return);
void sjf_class_copy(sjs_class* _this, sjs_class* _from);
void sjf_class_destroy(sjs_class* _this);
void sjf_class_foo(sjs_class* _parent, int32_t* _return);
void sjf_class_heap(sjs_class* _this);
void main_destroy(void);

void sjf_class(sjs_class* _this) {
}

void sjf_class__func(sjs_class* _parent, int32_t* _return) {
    sjs_class* sjt_dot1 = 0;

    sjt_dot1 = _parent;
    (*_return) = sjt_dot1->x;
}

void sjf_class_copy(sjs_class* _this, sjs_class* _from) {
    _this->x = _from->x;
    _this->_y = _from->_y;
}

void sjf_class_destroy(sjs_class* _this) {
}

void sjf_class_foo(sjs_class* _parent, int32_t* _return) {
    sjs_class* sjt_dot2 = 0;
    int32_t sjt_math1;
    int32_t sjt_math2;

    sjf_class__func(_parent, &sjt_math1);
    sjt_dot2 = _parent;
    sjt_math2 = sjt_dot2->_y;
    (*_return) = sjt_math1 + sjt_math2;
}

void sjf_class_heap(sjs_class* _this) {
}

int main(int argc, char** argv) {
    sjv_c._refCount = 1;
    sjv_c.x = 1;
    sjv_c._y = 2;
    sjf_class(&sjv_c);
    sjt_parent1 = &sjv_c;
    sjf_class_foo(sjt_parent1, &sjv_a);
    main_destroy();
    #ifdef _DEBUG
    printf("\npress return to end\n");
    getchar();
    #endif
    return 0;
}

void main_destroy() {

    if (sjv_c._refCount == 1) { sjf_class_destroy(&sjv_c); }
}