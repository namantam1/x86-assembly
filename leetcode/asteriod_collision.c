/*
auther: Naman Tamrakar
date: 2023-07-20

level: medium
url: https://leetcode.com/problems/asteroid-collision/
description: We are given an array asteroids of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.
*/

#include <stdio.h>
#include <stdlib.h>

int* asteroidCollision_C(int* arr, int n, int* rs){
    int *v = malloc(n * sizeof(int));

    int i = 0;
    while (i < n) {
        v[i] = arr[i];
        i++;
    }

    i = 1;
    while (i < n) {
        int cur = v[i];
        if (cur < 0) {
            cur = -cur;
            int j = i - 1;

            while (j >= 0) {
                int pre = v[j];
                if (pre > 0) {
                    if (pre < cur) {
                        v[j] = 0;
                    }
                    else if (pre > cur) {
                        v[i] = 0;
                        break;
                    }
                    else {
                        v[i] = v[j] = 0;
                        break;
                    }
                }

                j--;
            }
        }
        i++;
    }

    i=0;
    int j=0;
    while (j < n) {
        if (v[j]) {
            v[i++] = v[j];
        }
        j++;
    }
    *rs = i;
    return v;
}

__attribute__((naked))
int* asteroidCollision(int* arr, int n, int* rs){
    __asm__(
        "pushq %rbp;"
        "movq %rsp, %rbp;"
        "sub $64, %rsp;"

        "movq %rdi, -8(%rbp);"  // *arr
        "movl %esi, -16(%rbp);" // n
        "movq %rdx, -24(%rbp);" // *rs

        // int *v = malloc(n * sizeof(int));
        "movl %esi, %edi;"
        "imul $4, %rdi;"
        "call malloc;"
        "movq %rax, -32(%rbp);"

        "movl $0, %edi;" // i = 0
        "movq -8(%rbp), %rdx;" // arr
    "l1:;"
        "cmpl -16(%rbp), %edi;" // i < n
        "je l1_end;"

        "movl (%rdx,%rdi,4), %ecx;" // arr[i]
        "movl %ecx, (%rax,%rdi, 4);" // v[i] = arr[i]

        "incl %edi;"
        "jmp l1;"

    "l1_end:;"
        "movl $1, %edi;"

    "l2:;"
        "cmpl -16(%rbp), %edi;" // i < n
        "je l2_end;"

        "movl (%rax,%rdi,4), %ecx;" // cur
    
    "l2_c0:;"
        "cmpl $0, %ecx;" // cur < 0
        "jge l2_c0_end;"

        "negl %ecx;" //  cur = -cur

        "movl %edi, %esi;"
        "decl %esi;" // j = i - 1

    "l2_c0_l1:;"
        "cmpl $0, %esi;" // j >= 0
        "jl l2_c0_l1_end;"

        "movl (%rax,%rsi,4), %edx;" // pre

    "l2_c0_l1_c0:;"
        "cmpl $0, %edx;" // pre > 0
        "jle l2_c0_l1_c0_end;"

        "cmpl %ecx, %edx;" // pre < cur
        "jl l2_c0_l1_c0_if;"
        
        "cmpl %ecx, %edx;" // pre > cur
        "jg l2_c0_l1_c0_else_if;"

        "movl $0, (%rax,%rdi,4);" // v[i] = 0
        "movl $0, (%rax,%rsi,4);" // v[j] = 0
        "jmp l2_c0_l1_end;"  // break

    "l2_c0_l1_c0_if:;"
        "movl $0, (%rax,%rsi,4);" // v[j] = 0
        "jmp l2_c0_l1_c0_end;" // back to j loop

    "l2_c0_l1_c0_else_if:;"
        "movl $0, (%rax,%rdi,4);" // v[i] = 0
        "jmp l2_c0_l1_end;" // break

    "l2_c0_l1_c0_end:;"
        "decl %esi;"
        "jmp l2_c0_l1;"

    "l2_c0_l1_end:;"
    "l2_c0_end:;"
        "incl %edi;"
        "jmp l2;"

    "l2_end:;"
        "movl $0, %edi;" // i = 0
        "movl $0, %esi;" // j = 0

    "l3:;"
        "cmpl -16(%rbp), %esi;" // j < n
        "jge l3_end;"

        "cmpl $0, (%rax,%rsi,4);"
        "jne l3_if;"

        "jmp l3_cont;"

    "l3_if:;"
        "movl (%rax,%rsi,4), %ecx;" // v[j]
        "movl %ecx, (%rax,%rdi,4);" // v[j] = v[i]
        "incl %edi;"


    "l3_cont:;"
        "incl %esi;"
        "jmp l3;"

    "l3_end:;"
        "movq -24(%rbp), %rcx;"
        "movl %edi, (%rcx);" // *rs = i
        "leave;"
        "ret;"
    );
}


int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    int ret_size = -1;
    int *res = asteroidCollision(arr, n, &ret_size);
    for (int i=0; i<ret_size; i++)
        printf("%d ", res[i]);
    free(res);
    return 0;
}

