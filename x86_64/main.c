
#include <stdio.h>
#include <stdlib.h>


__attribute__((naked))
int *fn(int k) {
    __asm__(
        "sub $48, %rsp;"
        "mov $8, %rdi;"
        "call malloc;"
        // "movq $1, (%rax);"
        // "movq $10, 4(%rax);"
        // "mov %rax, 16(%rsp);"

        "movq $0, 16(%rsp);"
        "mov 16(%rsp), %rax;"
        "add $48, %rsp;"
        "ret;"
    );
}


int main() {
    int *r = fn(0);
    // int *arr = fn();
    // printf("%p\n", arr);
    // printf("%d\n", arr[0]);
    // printf("%d\n", arr[1]);
    // free(arr);
    return 0;
}


