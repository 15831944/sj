typedef struct class_class {
    int _this;
    int x;
}

class* sj_class(class_class* _this);

class* sj_class(class_class* _this) {
    return _this;
}

int main() {
    class* c;
    class* objectRef1;
    c = sj_class(objectRef1);
    c->x;
    return 0;
}
