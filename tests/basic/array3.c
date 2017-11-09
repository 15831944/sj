#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct td_sjs_array_class sjs_array_class;
typedef struct td_sjs_class sjs_class;

struct td_sjs_array_class {
    int _refCount;
    int32_t size;
    uintptr_t data;
    bool _isGlobal;
};

struct td_sjs_class {
    int _refCount;
    int32_t x;
};

void sjf_array_class(sjs_array_class* _this, sjs_array_class** _return);
void sjf_array_class_destroy(sjs_array_class* _this);
void sjf_array_class_getAt(sjs_array_class* _parent, int32_t index, sjs_class** _return);
void sjf_array_class_setAt(sjs_array_class* _parent, int32_t index, sjs_class* item);
void sjf_class(sjs_class* _this, sjs_class** _return);
void sjf_class_destroy(sjs_class* _this);
void sjf_global();

void sjf_array_class(sjs_array_class* _this, sjs_array_class** _return) {
    
		if (_this->size < 0) {
			exit(-1);
		}

		if (_this->data) {
			_this->_isGlobal = true;
		} else {
			_this->data = (uintptr_t)malloc(_this->size * sizeof(sjs_class*));
		}
	;
    _this->_refCount++;

    *_return = _this;
}

void sjf_array_class_destroy(sjs_array_class* _this) {
    
	if (!_this->_isGlobal) {
		free((sjs_class**)_this->data);	
	}
;
}

void sjf_array_class_getAt(sjs_array_class* _parent, int32_t index, sjs_class** _return) {
    
		

		if (index >= _parent->size || index < 0) {
			exit(-1);
		}

		sjs_class** p = (sjs_class**)_parent->data;
		sjs_class* val = p[index];
		if (!false) {
			if (val == 0) {
				exit(-1);
			}
		}
		*_return = val;		
	;
}

void sjf_array_class_setAt(sjs_array_class* _parent, int32_t index, sjs_class* item) {
    
		
		

		if (index >= _parent->size || index < 0) {
			exit(-1);
		}

		sjs_class** p = (sjs_class**)_parent->data;
		 p[index]->_refCount--;
if ( p[index]->_refCount <= 0) {
    sjf_class_destroy( p[index]);
    free( p[index]);
}
;
		 item->_refCount++;
;
		p[index] = item;
	;
}

void sjf_class(sjs_class* _this, sjs_class** _return) {
    _this->_refCount++;

    *_return = _this;
}

void sjf_class_destroy(sjs_class* _this) {
}

void sjf_global() {
    sjs_array_class sjd_temp1;
    sjs_class sjd_temp2;
    sjs_array_class* a;
    sjs_class* c;
    uintptr_t result1;
    sjs_class* result2;
    sjs_array_class* sjv_array1;
    sjs_array_class* sjv_temp1;
    sjs_class* sjv_temp2;
    sjs_class* sjv_temp3;
    sjs_class* sjv_temp4;
    int32_t temp1;

    result1 = (uintptr_t)0;
    sjv_temp1 = &sjd_temp1;
    sjv_temp1->_refCount = 1;
    sjv_temp1->size = 3;
    sjv_temp1->data = result1;
    sjv_temp1->_isGlobal = false;
    sjf_array_class(sjv_temp1, &sjv_temp1);
    sjv_array1 = sjv_temp1;
    sjv_array1->_refCount++;
    sjv_temp2 = (sjs_class*)malloc(sizeof(sjs_class));
    sjv_temp2->_refCount = 1;
    sjv_temp2->x = 1;
    sjf_class(sjv_temp2, &sjv_temp2);
    sjf_array_class_setAt(sjv_array1, 0, sjv_temp2);
    sjv_temp3 = (sjs_class*)malloc(sizeof(sjs_class));
    sjv_temp3->_refCount = 1;
    sjv_temp3->x = 2;
    sjf_class(sjv_temp3, &sjv_temp3);
    sjf_array_class_setAt(sjv_array1, 1, sjv_temp3);
    sjv_temp4 = (sjs_class*)malloc(sizeof(sjs_class));
    sjv_temp4->_refCount = 1;
    sjv_temp4->x = 3;
    sjf_class(sjv_temp4, &sjv_temp4);
    sjf_array_class_setAt(sjv_array1, 2, sjv_temp4);
    a = sjv_array1;
    a->_refCount++;
    result2 = &sjd_temp2;
    sjf_array_class_getAt(a, 0, &result2);
    c = result2;
    c->_refCount++;
    temp1 = c->x;

    sjv_temp2->_refCount--;
    if (sjv_temp2->_refCount <= 0) {
        sjf_class_destroy(sjv_temp2);
        free(sjv_temp2);
    }
    sjv_temp3->_refCount--;
    if (sjv_temp3->_refCount <= 0) {
        sjf_class_destroy(sjv_temp3);
        free(sjv_temp3);
    }
    sjv_temp4->_refCount--;
    if (sjv_temp4->_refCount <= 0) {
        sjf_class_destroy(sjv_temp4);
        free(sjv_temp4);
    }
    sjf_array_class_destroy(&sjd_temp1);
    sjf_class_destroy(&sjd_temp2);
}

int main() {
    sjf_global();

    return 0;
}
