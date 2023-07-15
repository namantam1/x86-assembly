#include <stdio.h>
#include <stdlib.h>

int fib_C(int n){
    if (n == 0) return 0;
    int a_0 = 0, a_1 = 1, i = 2;
    while (i <= n) {
        int t = a_1 + a_0;
        a_0 = a_1;
        a_1 = t;
        i++;
    }
    return a_1;
}

__attribute__((naked))
int fib(int n){
    __asm__(
        "cmpl $0, %edi;"
        "je l0;"

        "movl $0, %ecx;"
        "movl $1, %edx;"
        "movl $1, %esi;"
    "l1:"
        "cmpl %edi, %esi;"
        "je end;"

        "movl %ecx, %eax;"
        "addl %edx, %eax;"
        "movl %edx, %ecx;"
        "movl %eax, %edx;"
        "incl %esi;"
        "jmp l1;"

    "l0:"
        "movl $0, %edx;"
        "jmp end;"

    "end:;"
        "movl %edx, %eax;"
        "ret;"
    );
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", fib(n));
    return 0;
}
