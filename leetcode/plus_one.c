#include <stdio.h>
#include <stdlib.h>

int* plusOne_c(int* arr, int n, int* rs) {
    *rs = n;
    int *ans = malloc(sizeof(int) * n);
    int c = 1, i = n-1;
    while (i>=0) {
        c += arr[i];
        ans[i] = c % 10;
        c /= 10;
        i--;
    }
    if (c) {
        *rs = n + 1;
        ans = realloc(ans, sizeof(int) * (n+1));
        ans[n] = 0;
        ans[0] = c;
    }
    return ans;
}

__attribute__((naked))
int *plusOne(int *arr, int n, int *rs) {
    __asm__(
        "sub $64, %rsp;"
        "mov %rdi, 16(%rsp);"
        "movl %esi, 24(%rsp);"
        "mov %rdx, 32(%rsp);"

        "movl %esi, (%rdx);"
        
        "mov %rsi, %rdi;"
        "imul $4, %rdi;"
        "call malloc;"
        "mov %rax, 40(%rsp);"

        "movl $1, %ecx;"
        "movl 24(%rsp), %edi;"
        "decl %edi;"

    "l1:;"
        "cmpl $0, %edi;"
        "jl l1_end;"

        "mov 16(%rsp), %rsi;"
        "addl (%rsi,%rdi,4), %ecx;"

        "xor %rdx, %rdx;"
        "mov %rcx, %rax;"
        "mov $10, %rsi;"
        "idiv %rsi;"
        // quotient in %rax and remainder in %rdx

        "mov 40(%rsp), %rsi;"
        "movl %edx, (%rsi,%rdi,4);"
        "movl %eax, %ecx;"

        "decl %edi;"
        "jmp l1;"

    "l1_end:;"
        "cmp $0, %ecx;"
        "je end;"

        "movl %ecx, 48(%rsp);"

        "movl 24(%rsp), %esi;"
        "incl %esi;"
        "mov 32(%rsp), %rdx;"
        "movl %esi, (%rdx);"
        
        "mov 40(%rsp), %rdi;"
        "imul $4, %rsi;"
        "call realloc;"
        "mov %rax, 40(%rsp);"

        "movl 24(%rsp), %esi;"
        "movl $0, (%rax,%rsi,4);"

        "movl 48(%rsp), %ecx;"
        "movl %ecx, (%rax);"

    "end:;"
        "mov 40(%rsp), %rax;"
        "add $64, %rsp;"
        "ret;"
    );
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    
    int rs = -1;
    int *res = plusOne(arr, n, &rs);

    // printf("%p\n", res);
    printf("%d\n", rs);
    for (int i=0; i<rs; i++)
        printf("%d ", res[i]);

    free(arr);

    return 0;
}
