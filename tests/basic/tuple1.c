#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct td_int32_option int32_option;
struct td_int32_option {
    bool isEmpty;
    int32_t value;
};
const int32_option int32_empty = { true };

typedef struct td_uint32_option uint32_option;
struct td_uint32_option {
    bool isEmpty;
    uint32_t value;
};
const uint32_option uint32_empty = { true };

typedef struct td_int64_option int64_option;
struct td_int64_option {
    bool isEmpty;
    int64_t value;
};
const int64_option int64_empty = { true };

typedef struct td_uint64_option uint64_option;
struct td_uint64_option {
    bool isEmpty;
    uint64_t value;
};
const uint64_option uint64_empty = { true };

typedef struct td_uintptr_option uintptr_option;
struct td_uintptr_option {
    bool isEmpty;
    uintptr_t value;
};
const uintptr_option uintptr_empty = { true };

typedef struct td_char_option char_option;
struct td_char_option {
    bool isEmpty;
    char value;
};
const char_option char_empty = { true };

typedef struct td_float_option float_option;
struct td_float_option {
    bool isEmpty;
    float value;
};
const float_option float_empty = { true };

typedef struct td_double_option double_option;
struct td_double_option {
    bool isEmpty;
    double value;
};
const double_option double_empty = { true };

const char* sjg_string1 = "bob";
const char* sjg_string2 = "foo";

#define sjs_anon1_typeId 1
#define sjs_anon2_typeId 2
#define sjs_anon3_typeId 3
#define sjs_array_char_typeId 4
#define sjs_object_typeId 5
#define sjs_string_typeId 6
#define sjs_tuple2_int32_t_sjs_string_typeId 7
#define sjs_tuple3_sjs_string_double_int32_t_typeId 8

typedef struct td_sjs_anon1 sjs_anon1;
typedef struct td_sjs_anon2 sjs_anon2;
typedef struct td_sjs_anon3 sjs_anon3;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_object sjs_object;
typedef struct td_sjs_string sjs_string;
typedef struct td_sjs_tuple2_int32_t_sjs_string sjs_tuple2_int32_t_sjs_string;
typedef struct td_sjs_tuple3_sjs_string_double_int32_t sjs_tuple3_sjs_string_double_int32_t;

struct td_sjs_anon1 {
    int _refCount;
    uintptr_t _fd;
};

struct td_sjs_anon2 {
    int _refCount;
};

struct td_sjs_anon3 {
    int _refCount;
};

struct td_sjs_array_char {
    int _refCount;
    int32_t size;
    uintptr_t data;
    bool _isGlobal;
};

struct td_sjs_object {
    int _refCount;
};

struct td_sjs_string {
    int _refCount;
    int32_t count;
    sjs_array_char* data;
};

struct td_sjs_tuple2_int32_t_sjs_string {
    int _refCount;
    int32_t item1;
    sjs_string* item2;
};

struct td_sjs_tuple3_sjs_string_double_int32_t {
    int _refCount;
    sjs_string* item1;
    double item2;
    int32_t item3;
};

void sjf_anon1(sjs_anon1* _this, sjs_anon1** _return);
void sjf_anon1_destroy(sjs_anon1* _this);
void sjf_anon2(sjs_anon2* _this, sjs_anon2** _return);
void sjf_anon2_destroy(sjs_anon2* _this);
void sjf_anon3(sjs_anon3* _this, sjs_anon3** _return);
void sjf_anon3_destroy(sjs_anon3* _this);
void sjf_array_char(sjs_array_char* _this, sjs_array_char** _return);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_func(sjs_tuple2_int32_t_sjs_string** _return);
void sjf_global(void);
void sjf_string(sjs_string* _this, sjs_string** _return);
void sjf_string_destroy(sjs_string* _this);
void sjf_tuple2_int32_t_sjs_string(sjs_tuple2_int32_t_sjs_string* _this, sjs_tuple2_int32_t_sjs_string** _return);
void sjf_tuple2_int32_t_sjs_string_destroy(sjs_tuple2_int32_t_sjs_string* _this);
void sjf_tuple3_sjs_string_double_int32_t(sjs_tuple3_sjs_string_double_int32_t* _this, sjs_tuple3_sjs_string_double_int32_t** _return);
void sjf_tuple3_sjs_string_double_int32_t_destroy(sjs_tuple3_sjs_string_double_int32_t* _this);

void sjf_anon1(sjs_anon1* _this, sjs_anon1** _return) {
     
		
		_this->_fd = (uintptr_t)stdout;
	;
    _this->_refCount++;

    *_return = _this;
}

void sjf_anon1_destroy(sjs_anon1* _this) {
}

void sjf_anon2(sjs_anon2* _this, sjs_anon2** _return) {
    _this->_refCount++;

    *_return = _this;
}

void sjf_anon2_destroy(sjs_anon2* _this) {
}

void sjf_anon3(sjs_anon3* _this, sjs_anon3** _return) {
    _this->_refCount++;

    *_return = _this;
}

void sjf_anon3_destroy(sjs_anon3* _this) {
}

void sjf_array_char(sjs_array_char* _this, sjs_array_char** _return) {
    
		if (_this->size < 0) {
			exit(-1);
		}

		if (_this->data) {
			_this->_isGlobal = true;
		} else {
			_this->data = (uintptr_t)malloc(_this->size * sizeof(char));
		}
	;
    _this->_refCount++;

    *_return = _this;
}

void sjf_array_char_destroy(sjs_array_char* _this) {
    
	if (!_this->_isGlobal) {
		free((char*)_this->data);	
	}
;
}

void sjf_func(sjs_tuple2_int32_t_sjs_string** _return) {
    sjs_array_char* sjv_temp4;
    sjs_string* sjv_temp5;
    sjs_tuple2_int32_t_sjs_string* sjv_temp6;

    sjv_temp4 = (sjs_array_char*)malloc(sizeof(sjs_array_char));
    sjv_temp4->_refCount = 1;
    sjv_temp4->size = 3;
    sjv_temp4->data = (uintptr_t)sjg_string1;
    sjv_temp4->_isGlobal = false;
    sjf_array_char(sjv_temp4, &sjv_temp4);
    sjv_temp5 = (sjs_string*)malloc(sizeof(sjs_string));
    sjv_temp5->_refCount = 1;
    sjv_temp5->count = 2;
    sjv_temp5->data = sjv_temp4;
    sjv_temp5->data->_refCount++;
    sjf_string(sjv_temp5, &sjv_temp5);
    sjv_temp6 = (sjs_tuple2_int32_t_sjs_string*)malloc(sizeof(sjs_tuple2_int32_t_sjs_string));
    sjv_temp6->_refCount = 1;
    sjv_temp6->item1 = 1;
    sjv_temp6->item2 = sjv_temp5;
    sjv_temp6->item2->_refCount++;
    sjf_tuple2_int32_t_sjs_string(sjv_temp6, &sjv_temp6);
    sjv_temp6->_refCount++;

    sjv_temp4->_refCount--;
    if (sjv_temp4->_refCount <= 0) {
        sjf_array_char_destroy(sjv_temp4);
        free(sjv_temp4);
    }
    sjv_temp5->_refCount--;
    if (sjv_temp5->_refCount <= 0) {
        sjf_string_destroy(sjv_temp5);
        free(sjv_temp5);
    }
    sjv_temp6->_refCount--;
    if (sjv_temp6->_refCount <= 0) {
        sjf_tuple2_int32_t_sjs_string_destroy(sjv_temp6);
        free(sjv_temp6);
    }

    *_return = sjv_temp6;
}

void sjf_global(void) {
    sjs_anon3 sjd_temp1;
    sjs_anon2 sjd_temp2;
    sjs_anon1 sjd_temp3;
    sjs_tuple3_sjs_string_double_int32_t sjd_temp4;
    int32_t a;
    sjs_string* b;
    int32_t c;
    sjs_anon1* console;
    sjs_string* d;
    sjs_string* e;
    double f;
    sjs_anon2* parse;
    sjs_anon3* random;
    uintptr_t result1;
    sjs_tuple2_int32_t_sjs_string* result2;
    sjs_tuple2_int32_t_sjs_string* result3;
    sjs_tuple2_int32_t_sjs_string* result4;
    sjs_anon3* sjv_temp1;
    sjs_anon2* sjv_temp2;
    sjs_anon1* sjv_temp3;
    sjs_array_char* sjv_temp7;
    sjs_string* sjv_temp8;
    sjs_tuple3_sjs_string_double_int32_t* sjv_temp9;
    sjs_tuple2_int32_t_sjs_string* t;
    int32_t temp1;
    sjs_string* temp2;
    int32_t temp3;
    sjs_string* temp4;
    int32_t temp5;
    sjs_string* temp6;
    sjs_string* temp7;
    double temp8;
    sjs_tuple2_int32_t_sjs_string* tupleResult1;
    sjs_tuple2_int32_t_sjs_string* tupleResult2;
    sjs_tuple3_sjs_string_double_int32_t* tupleResult3;

    sjv_temp1 = &sjd_temp1;
    sjv_temp1->_refCount = 1;
    sjf_anon3(sjv_temp1, &sjv_temp1);
    random = sjv_temp1;
    random->_refCount++;
    sjv_temp2 = &sjd_temp2;
    sjv_temp2->_refCount = 1;
    sjf_anon2(sjv_temp2, &sjv_temp2);
    parse = sjv_temp2;
    parse->_refCount++;
    result1 = (uintptr_t)0;
    sjv_temp3 = &sjd_temp3;
    sjv_temp3->_refCount = 1;
    sjv_temp3->_fd = result1;
    sjf_anon1(sjv_temp3, &sjv_temp3);
    console = sjv_temp3;
    console->_refCount++;
    result2 = 0;
    sjf_func(&result2);
    t = result2;
    t->_refCount++;
    temp1 = t->item1;
    a = temp1;
    temp2 = t->item2;
    b = temp2;
    b->_refCount++;
    result3 = 0;
    sjf_func(&result3);
    tupleResult1 = result3;
    tupleResult1->_refCount++;
    temp3 = tupleResult1->item1;
    a = temp3;
    temp4 = tupleResult1->item2;
    b->_refCount--;
    if (b->_refCount <= 0) {
        sjf_string_destroy(b);
        free(b);
    }

    b = temp4;

    b->_refCount++;

    result4 = 0;

    sjf_func(&result4);

    tupleResult2 = result4;

    tupleResult2->_refCount++;

    temp5 = tupleResult2->item1;

    c = temp5;

    temp6 = tupleResult2->item2;

    d = temp6;

    d->_refCount++;

    sjv_temp7 = (sjs_array_char*)malloc(sizeof(sjs_array_char));

    sjv_temp7->_refCount = 1;

    sjv_temp7->size = 3;

    sjv_temp7->data = (uintptr_t)sjg_string2;

    sjv_temp7->_isGlobal = false;

    sjf_array_char(sjv_temp7, &sjv_temp7);

    sjv_temp8 = (sjs_string*)malloc(sizeof(sjs_string));

    sjv_temp8->_refCount = 1;

    sjv_temp8->count = 2;

    sjv_temp8->data = sjv_temp7;

    sjv_temp8->data->_refCount++;

    sjf_string(sjv_temp8, &sjv_temp8);

    sjv_temp9 = &sjd_temp4;

    sjv_temp9->_refCount = 1;

    sjv_temp9->item1 = sjv_temp8;

    sjv_temp9->item1->_refCount++;

    sjv_temp9->item2 = 1.0;

    sjv_temp9->item3 = 4;

    sjf_tuple3_sjs_string_double_int32_t(sjv_temp9, &sjv_temp9);

    tupleResult3 = sjv_temp9;

    tupleResult3->_refCount++;

    temp7 = tupleResult3->item1;

    e = temp7;

    e->_refCount++;

    temp8 = tupleResult3->item2;

    f = temp8;

    b->_refCount--;
    if (b->_refCount <= 0) {
        sjf_string_destroy(b);
        free(b);
    }
    d->_refCount--;
    if (d->_refCount <= 0) {
        sjf_string_destroy(d);
        free(d);
    }
    result2->_refCount--;
    if (result2->_refCount <= 0) {
        sjf_tuple2_int32_t_sjs_string_destroy(result2);
        free(result2);
    }
    result3->_refCount--;
    if (result3->_refCount <= 0) {
        sjf_tuple2_int32_t_sjs_string_destroy(result3);
        free(result3);
    }
    result4->_refCount--;
    if (result4->_refCount <= 0) {
        sjf_tuple2_int32_t_sjs_string_destroy(result4);
        free(result4);
    }
    sjv_temp7->_refCount--;
    if (sjv_temp7->_refCount <= 0) {
        sjf_array_char_destroy(sjv_temp7);
        free(sjv_temp7);
    }
    sjv_temp8->_refCount--;
    if (sjv_temp8->_refCount <= 0) {
        sjf_string_destroy(sjv_temp8);
        free(sjv_temp8);
    }
    t->_refCount--;
    if (t->_refCount <= 0) {
        sjf_tuple2_int32_t_sjs_string_destroy(t);
        free(t);
    }
    temp2->_refCount--;
    if (temp2->_refCount <= 0) {
        sjf_string_destroy(temp2);
        free(temp2);
    }
    temp4->_refCount--;
    if (temp4->_refCount <= 0) {
        sjf_string_destroy(temp4);
        free(temp4);
    }
    temp6->_refCount--;
    if (temp6->_refCount <= 0) {
        sjf_string_destroy(temp6);
        free(temp6);
    }
    tupleResult1->_refCount--;
    if (tupleResult1->_refCount <= 0) {
        sjf_tuple2_int32_t_sjs_string_destroy(tupleResult1);
        free(tupleResult1);
    }
    tupleResult2->_refCount--;
    if (tupleResult2->_refCount <= 0) {
        sjf_tuple2_int32_t_sjs_string_destroy(tupleResult2);
        free(tupleResult2);
    }
    sjf_anon3_destroy(&sjd_temp1);
    sjf_anon2_destroy(&sjd_temp2);
    sjf_anon1_destroy(&sjd_temp3);
    sjf_tuple3_sjs_string_double_int32_t_destroy(&sjd_temp4);
}

void sjf_string(sjs_string* _this, sjs_string** _return) {
    _this->_refCount++;

    *_return = _this;
}

void sjf_string_destroy(sjs_string* _this) {
    _this->data->_refCount--;
    if (_this->data->_refCount <= 0) {
        sjf_array_char_destroy(_this->data);
        free(_this->data);
    }
}

void sjf_tuple2_int32_t_sjs_string(sjs_tuple2_int32_t_sjs_string* _this, sjs_tuple2_int32_t_sjs_string** _return) {
    _this->_refCount++;

    *_return = _this;
}

void sjf_tuple2_int32_t_sjs_string_destroy(sjs_tuple2_int32_t_sjs_string* _this) {
    _this->item2->_refCount--;
    if (_this->item2->_refCount <= 0) {
        sjf_string_destroy(_this->item2);
        free(_this->item2);
    }
}

void sjf_tuple3_sjs_string_double_int32_t(sjs_tuple3_sjs_string_double_int32_t* _this, sjs_tuple3_sjs_string_double_int32_t** _return) {
    _this->_refCount++;

    *_return = _this;
}

void sjf_tuple3_sjs_string_double_int32_t_destroy(sjs_tuple3_sjs_string_double_int32_t* _this) {
    sjf_string_destroy(_this->item1);
}

int main() {
    sjf_global();

    return 0;
}
