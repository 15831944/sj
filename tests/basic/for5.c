#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sjf_global();

void sjf_global() {
    int32_t loopEnd1;
    int32_t x;
    int32_t y;

    y = 0;
    x = 2;
    loopEnd1 = 4;
    while (x <= loopEnd1) {
        int32_t result1;

        result1 = y + x;
        y = result1;
        x++;
    }
}

int main() {
    sjf_global();

    return 0;
}
