#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t sjf_func();
int32_t sjf_global();

int32_t sjf_func() {
    return 1;
}

int32_t sjf_global() {
    return sjf_func();
}

int main() {
    sjf_global();
    return 0;
}
