#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct td_sjs_class_i32 sjs_class_i32;

struct td_sjs_class_i32 {
};

sjs_class_i32* sjf_class_i32(sjs_class_i32* _this);
int32_t sjf_global();

sjs_class_i32* sjf_class_i32(sjs_class_i32* _this) {
    return _this;
}

int32_t sjf_global() {
    sjs_class_i32* c;
    sjs_class_i32 sjd_temp1;
    sjs_class_i32* sjv_temp1;
    sjv_temp1 = &sjd_temp1;
    c = sjf_class_i32(sjv_temp1);
    return 1;
}

int main() {
    sjf_global();
    return 0;
}