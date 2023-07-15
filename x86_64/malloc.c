#include <stdio.h>
#include <stdlib.h>


__attribute__((naked))
int *fn(int a, int b) {
    __asm__(
        "sub $64, %rsp;"
        "movl %edi, 16(%rsp);"
        "movl %esi, 24(%rsp);"

        "mov $8, %rdi;"
        "call malloc;"
        "mov %rax, 32(%rsp);"

        "movl $0, %edi;"
        "movl 16(%rsp), %esi;"
        "movl %esi, (%rax,%rdi,4);"

        "movl $1, %edi;"
        "movl 24(%rsp), %esi;"
        "movl %esi, (%rax,%rdi,4);"

        "add $64, %rsp;"
        "ret;"
    );
}


int main() {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    int *arr = fn(a, b);
    // printf("%p\n", arr);
    printf("%d\n", arr[0]);
    printf("%d\n", arr[1]);
    free(arr);
    return 0;
}
