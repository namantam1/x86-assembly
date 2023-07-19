/*
auther: Naman Tamrakar
date: 2023-07-19

level: easy
url: https://leetcode.com/problems/plus-one/
question: You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.
*/

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
        "pushq %rbp;"
        "movq %rsp, %rbp;"
        "sub $40, %rsp;"

        "mov %rdi, -8(%rbp);"
        "movl %esi, -16(%rbp);"
        "mov %rdx, -24(%rbp);"

        // *rs = n;
        "movl %esi, (%rdx);"
        // int *ans = malloc(sizeof(int) * n);
        "mov %rsi, %rdi;"
        "imul $4, %rdi;"
        "call malloc;"
        "mov %rax, -32(%rbp);"

        // int c = 1, i = n-1;
        "movl $1, %ecx;"
        "movl -16(%rbp), %edi;"
        "decl %edi;"

    "l1:;"
        // while (i>=0) {
        "cmpl $0, %edi;"
        "jl l1_end;"

        // c += arr[i];
        "mov -8(%rbp), %rsi;"
        "addl (%rsi,%rdi,4), %ecx;"

        // ans[i] = c % 10;
        // c /= 10;
        "xor %rdx, %rdx;"
        "mov %rcx, %rax;"
        "mov $10, %rsi;"
        "idiv %rsi;"
        // quotient in %rax and remainder in %rdx

        "mov -32(%rbp), %rsi;"
        "movl %edx, (%rsi,%rdi,4);"
        "movl %eax, %ecx;"

        // i--;
        "decl %edi;"
        "jmp l1;"

    "l1_end:;"
        // if (c) {
        "cmp $0, %ecx;"
        "je end;"

        // store value of c in stack
        "movl %ecx, -40(%rbp);"

        // *rs = n + 1;
        "movl -16(%rbp), %esi;"
        "incl %esi;"
        "mov -24(%rbp), %rdx;"
        "movl %esi, (%rdx);"
        
        // ans = realloc(ans, sizeof(int) * (n+1));
        "mov -32(%rbp), %rdi;"
        "imul $4, %rsi;"
        "call realloc;"
        "mov %rax, -32(%rbp);"

        //     ans[n] = 0;
        //     ans[0] = c;
        "movl -16(%rbp), %esi;"
        "movl $0, (%rax,%rsi,4);"

        "movl -40(%rbp), %ecx;"
        "movl %ecx, (%rax);"

    "end:;"
        // return ans;
        "mov -32(%rbp), %rax;"

        "add $40, %rsp;"
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
    
    int rs = -1;
    int *res = plusOne(arr, n, &rs);

    // printf("%p\n", res);
    printf("%d\n", rs);
    for (int i=0; i<rs; i++)
        printf("%d ", res[i]);

    free(arr);

    return 0;
}
