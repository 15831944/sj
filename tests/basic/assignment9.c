#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sjf_global();

void sjf_global() {
    int32_t result1;
    int32_t x;
    int32_t y;

    y = 2;
    x = 2;
    result1 = x + y;
}

int main() {
    sjf_global();

    return 0;
}
