#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sjf_global();

void sjf_global() {
    bool result1;

    result1 = -3 == 4;
}

int main() {
    sjf_global();

    return 0;
}
