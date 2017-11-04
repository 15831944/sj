#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct td_sjs_class sjs_class;

struct td_sjs_class {
    int _refCount;
    int32_t m;
};

int32_t sjf_class(sjs_class* _this);
void sjf_class_destroy(sjs_class* _this);
int32_t sjf_class_inner(sjs_class* _parent);
int32_t sjf_global();

int32_t sjf_class(sjs_class* _this) {
    int32_t _retVal;
    _this->m = 1;
    _retVal = (sjf_class_inner((_this)));
    return _retVal;
}

void sjf_class_destroy(sjs_class* _this) {
}

int32_t sjf_class_inner(sjs_class* _parent) {
    int32_t _retVal;
    _retVal = (_parent->m);
    return _retVal;
}

int32_t sjf_global() {
    int32_t _retVal;
    sjs_class sjd_temp1;
    sjs_class* sjv_temp1;
    sjv_temp1 = &sjd_temp1;
    sjv_temp1->_refCount = 1;
    _retVal = (sjf_class(sjv_temp1));
    sjf_class_destroy(sjv_temp1);
    return _retVal;
}

int main() {
    sjf_global();
    return 0;
}
