#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct td_sjs_class sjs_class;

struct td_sjs_class {
    int _refCount;
    int32_t x;
};

sjs_class* sjf_class(sjs_class* _this);
void sjf_class_destroy(sjs_class* _this);
sjs_class* sjf_func();
int32_t sjf_global();

sjs_class* sjf_class(sjs_class* _this) {
    sjs_class* _retVal;
    _retVal = (_this);
    return _retVal;
}

void sjf_class_destroy(sjs_class* _this) {
}

sjs_class* sjf_func() {
    sjs_class* _retVal;
    sjs_class* sjv_temp1;
    sjv_temp1 = (sjs_class*)malloc(sizeof(sjs_class));
    sjv_temp1->_refCount = 1;
    sjv_temp1->x = 1;
    _retVal = (sjf_class(sjv_temp1));
    sjv_temp1->_refCount--;
    if (sjv_temp1->_refCount == 0) {
        sjf_class_destroy(sjv_temp1);
        free(sjv_temp1);
    }
    return _retVal;
}

int32_t sjf_global() {
    int32_t _retVal;
    _retVal = (sjf_func()->x);
    return _retVal;
}

int main() {
    sjf_global();
    return 0;
}
