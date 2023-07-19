/*
auther: Naman Tamrakar
date: 2023-07-19

level: easy
url: https://leetcode.com/problems/fibonacci-number/
question: The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,
*/

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
        // if (n == 0)
        "cmpl $0, %edi;"
        "je l0;"

        // a_0 = 0
        "movl $0, %ecx;"
        // a_1 = 1
        "movl $1, %edx;"
        // i = 2;
        "movl $1, %esi;"
    "l1:"
        // while (i <= n) {
        "cmpl %edi, %esi;"
        "je end;"

        // int t = a_1 + a_0;
        "movl %ecx, %eax;"
        "addl %edx, %eax;"
        // a_0 = a_1;
        "movl %edx, %ecx;"
        // a_1 = t;
        "movl %eax, %edx;"

        // i++;
        "incl %esi;"
        "jmp l1;"

    "l0:"
        // return 0;
        "movl $0, %edx;"
        "jmp end;"

    "end:;"
        // return a_1;
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
