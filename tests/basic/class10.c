typedef struct {
    int x;
} sjs_class;

sjs_class* sjf_class(sjs_class* _this);
int sjf_func(sjs_class* _parent);

sjs_class* sjf_class(sjs_class* _this) {
    return _this;
}

int sjf_func(sjs_class* _parent) {
    return x;
}

int main() {
    sjs_class* c;
    sjs_class sjd_temp1;
    sjs_class* sjv_temp1;
    sjv_temp1 = &sjd_temp1;
    sjv_temp1->x = 1;
    c = sjf_class(sjv_temp1);
    csjf_func((_parent));
    return 0;
}
