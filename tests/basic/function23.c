#include <lib/common/common.h>

#define sjs_log_typeId 1
#define sjs_func_typeId 2

typedef struct td_sjs_log sjs_log;
typedef struct td_sjs_func sjs_func;

struct td_sjs_log {
    int _refCount;
    int32_t minlevel;
};

struct td_sjs_func {
    int _refCount;
    int32_t x;
    int32_t y;
    int32_t z;
};

int32_t sjv_loglevel_debug;
int32_t sjv_loglevel_error;
int32_t sjv_loglevel_fatal;
int32_t sjv_loglevel_info;
int32_t sjv_loglevel_trace;
int32_t sjv_loglevel_warn;

int32_t result1;
sjs_func sjt_void1 = { -1 };
sjs_func sjt_void2 = { -1 };
void* sjv_emptystringdata;
float sjv_f32_pi;
int32_t sjv_i32_maxvalue;
int32_t sjv_i32_minvalue;
sjs_log sjv_log = { -1 };
uint32_t sjv_u32_maxvalue;

void sjf_func(sjs_func* _this);
void sjf_func_copy(sjs_func* _this, sjs_func* _from);
void sjf_func_destroy(sjs_func* _this);
void sjf_func_heap(sjs_func* _this);
void sjf_log(sjs_log* _this);
void sjf_log_copy(sjs_log* _this, sjs_log* _from);
void sjf_log_destroy(sjs_log* _this);
void sjf_log_heap(sjs_log* _this);
void main_destroy(void);

#include <lib/common/common.c>
void sjf_func(sjs_func* _this) {
}

void sjf_func_copy(sjs_func* _this, sjs_func* _from) {
    _this->x = _from->x;
    _this->y = _from->y;
    _this->z = _from->z;
}

void sjf_func_destroy(sjs_func* _this) {
}

void sjf_func_heap(sjs_func* _this) {
}

void sjf_log(sjs_log* _this) {
}

void sjf_log_copy(sjs_log* _this, sjs_log* _from) {
    _this->minlevel = _from->minlevel;
}

void sjf_log_destroy(sjs_log* _this) {
}

void sjf_log_heap(sjs_log* _this) {
}

int main(int argc, char** argv) {
    sjv_loglevel_trace = 0;
    sjv_loglevel_debug = 1;
    sjv_loglevel_info = 2;
    sjv_loglevel_warn = 3;
    sjv_loglevel_error = 4;
    sjv_loglevel_fatal = 5;
    sjv_f32_pi = 3.14159265358979323846f;
    sjv_u32_maxvalue = (uint32_t)4294967295u;
    result1 = -1;
    sjv_i32_maxvalue = result1 - 2147483647;
    sjv_i32_minvalue = 2147483647;
    sjv_log._refCount = 1;
    sjv_log.minlevel = sjv_loglevel_warn;
    sjf_log(&sjv_log);
    sjv_emptystringdata = 0;
    sjv_emptystringdata = "";
    ptr_init();
    weakptr_init();
    sjt_void1._refCount = 1;
    sjt_void1.x = 4;
    sjt_void1.y = 5;
    sjt_void1.z = 6;
    sjf_func(&sjt_void1);
    sjt_void2._refCount = 1;
    sjt_void2.x = 7;
    sjt_void2.y = 8;
    sjt_void2.z = 9;
    sjf_func(&sjt_void2);
    main_destroy();
    return 0;
}

void main_destroy() {

    if (sjt_void1._refCount == 1) { sjf_func_destroy(&sjt_void1); }
;
    if (sjt_void2._refCount == 1) { sjf_func_destroy(&sjt_void2); }
;
    if (sjv_log._refCount == 1) { sjf_log_destroy(&sjv_log); }
;
}
