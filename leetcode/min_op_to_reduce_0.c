#include <stdio.h>
#include <stdlib.h>

int minOperations(int n);

int minOperations_c(int n) {
    int ans = 1;
    int i=0;
    int k = 1;
    while (k < n) {
        k <<= 1;
        i++;
    }
    if (k == n)
        return ans;
    int a = minOperations(k-n);
    int b = minOperations(n-(k/2));
    if (a < b)
        ans += a;
    else
        ans += b;
    return ans;
}

__attribute__((naked))
int minOperations(int n) {
    __asm__(
        "call minop;"
        "ret;"

    "minop:;"
        "sub $48, %rsp;"
        "movl %edi, 16(%rsp);"

        "movl $1, %eax;"
        "movl $0, %esi;"
        "movl $1, %ecx;"
    "l1:;"
        "cmpl %edi, %ecx;"
        "jge l1_end;"

        "sal $1, %ecx;"
        "incl %esi;"
        "jmp l1;"

    "l1_end:;"
        "cmp %edi, %ecx;"
        "je end;"

        "movl %ecx, 24(%rsp);"

        "subl 16(%rsp), %ecx;"
        "movl %ecx, %edi;"
        "call minop;"
        "movl %eax, 32(%rsp);"

        "movl 24(%rsp), %ecx;"
        "sar $1, %ecx;"
        "movl 16(%rsp), %edi;"
        "subl %ecx, %edi;"
        "call minop;"
        "movl %eax, 40(%rsp);"

        "movl $1, %eax;"
        "movl 32(%rsp), %ecx;"
        "movl 40(%rsp), %edx;"
    
        "cmpl %ecx, %edx;"
        "jl if1;"

        "addl %ecx, %eax;"
        "jmp end;"

    "if1:;"
        "addl %edx, %eax;"
        "jmp end;"

    "end:;"
        "add $48, %rsp;"
        "ret;"
    );
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", minOperations(n));
}