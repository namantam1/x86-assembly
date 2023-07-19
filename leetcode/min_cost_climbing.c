/*
auther: Naman Tamrakar
date: 2023-07-19

level: easy
url: https://leetcode.com/problems/min-cost-climbing-stairs/
question: You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.
*/

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
        "pushq %rbp;"
        "movq %rsp, %rbp;"
        "sub $64, %rsp;"

        "mov %rdi, -8(%rbp);"
        "movl %esi, -16(%rbp);"

        // int *t = malloc(n * sizeof(int));
        "mov %rsi, %rdi;"
        "imul $4, %rdi;"
        "call malloc;"
        "mov %rax, -24(%rbp);"

        "movl -16(%rbp), %edi;"
        // t[n-1] = 0
        "decl %edi;"
        "movl $0, (%rax,%rdi,4);"
        // t[n-2] = 0;
        "decl %edi;"
        "movl $0, (%rax,%rdi,4);"
        // int i = n - 3;
        "decl %edi;"
    
    "l1:;"
        // while (i >= 0) {
        "cmpl $0, %edi;"
        "jl l1_end;"


        // int a = v[i+1]+t[i+1];
        "movl %edi, %esi;" // i
        "incl %esi;" // i + 1
        "mov -8(%rbp), %rdx;"
        "movl (%rdx,%rsi,4), %edx;"
        "addl (%rax,%rsi,4), %edx;"

        // int b = v[i+2]+t[i+2];
        "incl %esi;"
        "mov -8(%rbp), %rcx;"
        "movl (%rcx,%rsi,4), %ecx;"
        "addl (%rax,%rsi,4), %ecx;"

        //     if (a < b)
        "cmpl %edx, %ecx;"
        "jl if1;"

        // else
        // t[i] = b;
        "movl %edx, (%rax,%rdi,4);"
        "jmp l1_c1;"

    "if1:;"
        // t[i] = a;
        "movl %ecx, (%rax,%rdi,4);"

    "l1_c1:;"
        // i--;
        "decl %edi;"
        "jmp l1;"

    "l1_end:;"
        // int a = t[0]+v[0];
        // int b = t[1]+v[1];
        // int ans;
        "movl $0, %esi;"
        "mov -8(%rbp), %rdx;"
        "movl (%rdx,%rsi,4), %edx;"
        "addl (%rax,%rsi,4), %edx;"
        "incl %esi;"
        "mov -8(%rbp), %rcx;"
        "movl (%rcx,%rsi,4), %ecx;"
        "addl (%rax,%rsi,4), %ecx;"

        // if (a < b)
        //     ans = a;
        // else
        //     ans = b;
        "cmpl %edx, %ecx;"
        "jl if2;"

        "movl %edx, -32(%rbp);"
        "jmp end;"

    "if2:;"
        "movl %ecx, -32(%rbp);"

    "end:;"
        // free(t);
        "mov -24(%rbp), %rdi;"
        "call free;"

        // return ans;
        "movl -32(%rbp), %eax;"

        // restore stack
        "add $64, %rsp;"
        "movq %rbp, %rsp;"
        "popq %rbp;"
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

