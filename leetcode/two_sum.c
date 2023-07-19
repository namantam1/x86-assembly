/*
auther: Naman Tamrakar
date: 2023-07-19

level: easy
url: https://leetcode.com/problems/two-sum/
question: Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.
*/

#include <stdio.h>
#include <stdlib.h>

int *sol(int *a, int n, int k, int *r) {
    *r = 2;
    int *ans = malloc(sizeof(int) * 2);
    int i=0;
    while (i < n) {
        int j = i+1;
        while (j < n) {
            if (a[i] + a[j] == k) {
                ans[0] = i;
                ans[1] = j;
                return ans;
            }
            j++;
        }
        i++;
    }
    return ans;
}

__attribute__((naked)) 
int* sum(int *a, int n, int k, int *r) {
    __asm__(

        "pushq %rbp;"
        "movq %rsp, %rbp;"
        "sub $32, %rsp;"

        // *r = 2;
        "movq $2, (%rcx);"

        // store rest params in stack
        "movq %rdi, -8(%rbp);"
        "movl %esi, -16(%rbp);"
        "movl %edx, -24(%rbp);"

        "movq $8, %rdi;"
        "call malloc;"
        "movq %rax, -32(%rbp);"

        // i=0
        "movl $0, %edi;"

    "l1:;"
        "cmpl -16(%rbp), %edi;"
        "je end;"

        "movl %edi, %esi;"
        "incl %esi;"

    "l2:;"
        "cmpl -16(%rbp), %esi;"
        "je l2_end;"

        "movq -8(%rbp), %rcx;" // a
        "movl (%rcx,%rdi,4), %eax;" // a[i]
        "addl (%rcx,%rsi,4), %eax;" // a[i] + a[j]

        "cmpl %eax, -24(%rbp);"
        "jne l2_c;"

        "movq -32(%rbp), %rdx;" // ans
        "movl %edi, (%rdx);" // ans[0] = i
        "movl %esi, 4(%rdx);" // ans[1] = j
        "jmp end;"
    
    "l2_c:;"
        // j++;
        "incl %esi;"
        "jmp l2;"

    "l2_end:;"
        // i++;
        "incl %edi;"
        "jmp l1;"

    "end:;"
        // ans
        "movq -32(%rbp), %rax;"

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
    int *arr = malloc(sizeof(int) * n);
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    int k;
    scanf("%d", &k);

    int r = -1;

    int *ans = sum(arr, n, k, &r);
    printf("%d %d\n", ans[0], ans[1]);
    free(arr);
    free(ans);
    return 0;
}
