/*
auther: Naman Tamrakar
date: 2023-07-18

level: easy
url: https://leetcode.com/problems/climbing-stairs/
question: You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/

#include <stdio.h>
#include <stdlib.h>


int climbStairs_c(int n) {
    // int *t = malloc((n+1) * sizeof(int));
    // t[0] = t[1] = 1;
    // int i = 2;
    // while (i <= n) {
    //     t[i] = t[i-1] + t[i-2];
    //     i++;
    // }
    // int ans = t[n];
    // free(t);
    // return ans;


    int pre_pre = 1, pre = 1, i = 2;
    while (i<=n) {
        int tmp = pre + pre_pre;
        pre_pre = pre;
        pre = tmp;
        i++;
    }
    return pre;
}

__attribute__((naked))
int climbStairs(int n) {
    // __asm__(
    //     "pushq %rbp;"
    //     "movq %rsp, %rbp;"
    //     "sub $24, %rsp;"

    //     "mov %rdi, -8(%rbp);"

    //     // int *t = malloc((n+1) * sizeof(int));
    //     "add $1, %rdi;"
    //     "imul $4, %rdi;"
    //     "call malloc;"
    //     "mov %rax, -16(%rbp);"


    //     // t[0] = t[1] = 1;
    //     "movl $1, (%rax);"
    //     "movl $1, 4(%rax);"
    //     // i = 2
    //     "movl $2, %edx;"

    // "l1:;"
    //     // while (i <= n) {
    //     "cmpl -8(%rbp), %edx;"
    //     "jg l1_end;"
        

    //     //     t[i] = t[i-1] + t[i-2];
    //     "movl %edx, %ecx;"
    //     "decl %ecx;"
    //     "movl (%rax,%rcx,4), %esi;"
        
    //     "decl %ecx;"
    //     "add (%rax,%rcx,4), %esi;"
    //     "movl %esi, (%rax,%rdx,4);"

    //     // i--
    //     "incl %edx;"
    //     // }
    //     "jmp l1;"

    // "l1_end:;"
    //     // int ans = t[n];
    //     "movl -8(%rbp), %edx;"
    //     "movl (%rax,%rdx,4), %esi;"
    //     // save the result on stack
    //     "movl %esi, -24(%rbp);"

    //     // free(t);
    //     "mov -16(%rbp), %rdi;"
    //     "call free;"

    //     // return ans;
    //     "movl -24(%rbp), %eax;"

    //     "add $24, %rsp;"
    //     "movq %rbp, %rsp;"
    //     "popq %rbp;"
    //     "ret;"
    // );


    __asm__(
        // int pre_pre = 1, pre = 1, i = 2;
        "movl $1, %eax;"
        "movl $1, %ecx;"
        "movl $2, %edx;"
    "l1:;"
        // while (i<=n) {
        "cmpl %edi, %edx;"
        "jg end;"

        // int tmp = pre + pre_pre;
        "movl %eax, %esi;"
        "addl %ecx, %esi;"
        // pre_pre = pre;
        "movl %eax, %ecx;"
        // pre = tmp;
        "movl %esi, %eax;"

        // i++;
        "incl %edx;"
        // }
        "jmp l1;"

    "end:;"
        // return pre;
        "ret;"
    );
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", climbStairs(n));
}
