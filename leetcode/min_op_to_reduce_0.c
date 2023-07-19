/*
auther: Naman Tamrakar
date: 2023-07-19

level: medium
url: https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/
question: You are given a positive integer n, you can do the following operation any number of times:

Add or subtract a power of 2 from n.
Return the minimum number of operations to make n equal to 0.

A number x is power of 2 if x == 2i where i >= 0.
*/

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
        // call recursive function and return its value
        "call minop;"
        "ret;"

    // define recursive function first
    "minop:;"
        "pushq %rbp;"
        "movq %rsp, %rbp;"
        "sub $32, %rsp;"

        "movl %edi, -8(%rbp);"

        // int ans = 1;
        "movl $1, %eax;"
        // int i=0;
        "movl $0, %esi;"
        // int k = 1;
        "movl $1, %ecx;"
    "l1:;"
        // while (k < n) {
        "cmpl %edi, %ecx;"
        "jge l1_end;"

        //     k <<= 1;
        "sal $1, %ecx;"
        //     i++;
        "incl %esi;"
        "jmp l1;"

    "l1_end:;"
        // if (k == n)
        "cmp %edi, %ecx;"
        "je end;"

        "movl %ecx, -16(%rbp);"

        // int a = minOperations(k-n);
        "subl -8(%rbp), %ecx;"
        "movl %ecx, %edi;"
        "call minop;"
        "movl %eax, -24(%rbp);"

        // int b = minOperations(n-(k/2));
        "movl -16(%rbp), %ecx;"
        "sar $1, %ecx;"
        "movl -8(%rbp), %edi;"
        "subl %ecx, %edi;"
        "call minop;"
        "movl %eax, -32(%rbp);"

        "movl $1, %eax;"        // k
        "movl -24(%rbp), %ecx;" // a
        "movl -32(%rbp), %edx;" // b
    
        // if (a < b)
        "cmpl %ecx, %edx;"
        "jl if1;"

        // else
        // ans += b;
        "addl %ecx, %eax;"
        "jmp end;"

    "if1:;"
        //     ans += a;
        "addl %edx, %eax;"
        "jmp end;"

    "end:;"
        // restore stack
        "add $32, %rsp;"
        "movq %rbp, %rsp;"
        "popq %rbp;"
        "ret;"
    );
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", minOperations(n));
}