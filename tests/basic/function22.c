#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sjf_foo();
void sjf_global();

void sjf_foo() {
}

void sjf_global() {
    sjf_foo();
}

int main() {
    sjf_global();
    return 0;
}
