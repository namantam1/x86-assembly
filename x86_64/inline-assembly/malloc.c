/*
auther: Naman Tamrakar
date: 2023-07-19

decription: program to show how malloc can be use used to allocate memory
*/

#include <stdio.h>
#include <stdlib.h>

int *copy_arr_C(int *arr, int n) {
    int *v = malloc(n * sizeof(int));
    int i = 0;
    while (i < n) {
        v[i] = arr[i];
        i++;
    }
    return v;
}

__attribute__((naked))
int *copy_arr(int *arr, int n) {
    __asm__(
        "pushq %rbp;"
        "movq %rsp, %rbp;"
        "sub $64, %rsp;"

        "movq %rdi, -8(%rbp);"
        "movl %esi, -16(%rbp);"

        // int *v = malloc(n * sizeof(int));
        "movq %rsi, %rdi;"
        "imul $4, %rdi;"
        "call malloc;"
        "mov %rax, -24(%rbp);" // v

        // i = 0
        "movl $0, %edi;"
        "movq -8(%rbp), %rdx;" // arr
    "l1:;"
        "cmpl -16(%rbp), %edi;"
        "je end;"

        "movl (%rdx,%rdi,4), %ecx;" // arr[i]
        "movl %ecx, (%rax,%rdi,4);" // v[i] = arr[i]

        "incl %edi;" // i++
        "jmp l1;"

    "end:;"
        // restore stack
        "add $64, %rsp;"
        "movq %rbp, %rsp;"
        "popq %rbp;"
        // return result already in %rax register
        "ret;"
    );
}


int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    int *res = copy_arr(arr, n);
    for (int i=0; i<n; i++)
        printf("%d ", res[i]);
    free(res);
    return 0;
}
