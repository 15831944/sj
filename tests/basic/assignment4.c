#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define sjs_object_typeId 1

typedef struct td_sjs_object sjs_object;

struct td_sjs_object {
    int _refCount;
};

void sjf_global(void);

void sjf_global(void) {
    int32_t result1;
    int32_t x;

    x = 1;
    x = 2;
    result1 = x + 1;
}

int main() {
    sjf_global();

    return 0;
}
