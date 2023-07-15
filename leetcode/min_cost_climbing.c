#include <stdio.h>
#include <stdlib.h>

int minCostClimbingStairs_c(int* v, int n){
    int *t = malloc(n * sizeof(int));
    t[n-1] = t[n-2] = 0;
    int i = n - 3;
    while (i >= 0) {
        int a = v[i+1]+t[i+1];
        int b = v[i+2]+t[i+2];

        if (a < b)
            t[i] = a;
        else
            t[i] = b;
        i--;
    }
    int a = t[0]+v[0];
    int b = t[1]+v[1];
    int ans;
    if (a < b)
        ans = a;
    else
        ans = b;
    free(t);
    return ans;
}

__attribute__((naked))
int minCostClimbingStairs(int* v, int n){
    __asm__(
        "sub $64, %rsp;"
        "mov %rdi, 16(%rsp);"
        "movl %esi, 24(%rsp);"

        "mov %rsi, %rdi;"
        "imul $4, %rdi;"
        "call malloc;"
        "mov %rax, 32(%rsp);"

        "movl 24(%rsp), %edi;"
        "decl %edi;"
        "movl $0, (%rax,%rdi,4);"
        "decl %edi;"
        "movl $0, (%rax,%rdi,4);"
        "decl %edi;"
    
    "l1:;"
        "cmpl $0, %edi;"
        "jl l1_end;"

        "movl %edi, %esi;"
        "incl %esi;"
        "mov 16(%rsp), %rdx;"
        "movl (%rdx,%rsi,4), %edx;"
        "addl (%rax,%rsi,4), %edx;"
        "incl %esi;"
        "mov 16(%rsp), %rcx;"
        "movl (%rcx,%rsi,4), %ecx;"
        "addl (%rax,%rsi,4), %ecx;"

        "cmpl %edx, %ecx;"
        "jl if1;"

        "movl %edx, (%rax,%rdi,4);"
        "jmp l1_c1;"

    "if1:;"
        "movl %ecx, (%rax,%rdi,4);"

    "l1_c1:;"
        "decl %edi;"
        "jmp l1;"

    "l1_end:;"
        "movl $0, %esi;"
        "mov 16(%rsp), %rdx;"
        "movl (%rdx,%rsi,4), %edx;"
        "addl (%rax,%rsi,4), %edx;"
        "incl %esi;"
        "mov 16(%rsp), %rcx;"
        "movl (%rcx,%rsi,4), %ecx;"
        "addl (%rax,%rsi,4), %ecx;"

        "cmpl %edx, %ecx;"
        "jl if2;"

        "movl %edx, 40(%rsp);"
        "jmp end;"

    "if2:;"
        "movl %ecx, 40(%rsp);"

    "end:;"
        "mov 32(%rsp), %rdi;"
        "call free;"

        "movl 40(%rsp), %eax;"
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
    printf("%d", minCostClimbingStairs(arr, n));
    free(arr);
    return 0;
}

