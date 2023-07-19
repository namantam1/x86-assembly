/*
auther: Naman Tamrakar
date: 2023-07-19

description: A sample program to make a copy of 2d array
*/

#include <stdio.h>
#include <stdlib.h>

int **copy_2d_arr_C(int **arr, int m, int n) {
    int **v = malloc(m * sizeof(int *));
    int i = 0;
    while (i < m) {
        v[i] = malloc(n * sizeof(int));
        i++;
    }

    i = 0;
    while (i < m) {
        int j = 0;
        while (j < n) {
            v[i][j] = arr[i][j];
            j++;
        }
        i++;
    }

    return v;
}

__attribute__((naked))
int **copy_2d_arr(int **arr, int m, int n) {
    __asm__(
        "pushq %rbp;"
        "movq %rsp, %rbp;"
        "sub $40, %rsp;"


        "movq %rdi, -8(%rbp);"  // arr
        "movl %esi, -16(%rbp);" // m
        "movl %edx, -24(%rbp);" // n
        
        // **V = malloc(m * sizeof(int *))
        "movl -16(%rbp), %edi;"
        "imul $8, %rdi;"  // size of address is 8 byte
        "call malloc;"
        "movq %rax, -32(%rbp);" // v

        // i = 0
        "movl $0, %edi;"
    "l0:;"
        // while (i < m)
        "cmpl -16(%rbp), %edi;"
        "je l0_end;"

        "movl %edi, -40(%rbp);" // backup i to stack

        // // v[i] = malloc(n * sizeof(int))
        "movl -24(%rbp), %edi;"
        "imul $4, %rdi;"
        "call malloc;"

        "movl -40(%rbp), %edi;" // restore i from stack
        "movq -32(%rbp), %rdx;" // v
        "movq %rax, (%rdx,%rdi,8);"

        "incl %edi;"
        "jmp l0;"

    "l0_end:;"
        "movl $0, %edi;" // i = 0
        "movq -8(%rbp), %rcx;" // arr
        "movq -32(%rbp), %rdx;" // arr

    "l1:;"
        // while (i < m)
        "cmpl -16(%rbp), %edi;"
        "je end;"

        // j = 0
        "movl $0, %esi;"
        "movq (%rdx,%rdi,8), %r9;" // v[i]
    "l2:;"
        // while (j < n)
        "cmpl -24(%rbp), %esi;"
        "je l1_end;"

        "movq (%rcx,%rdi,8), %r8;" // arr[i]
        "movl (%r8,%rsi,4), %r8d;" // arr[i][j]
        "movl %r8d, (%r9,%rsi,4);" // v[i][j] = arr[i][j]

        "incl %esi;" // j++
        "jmp l2;"

    "l1_end:;"
        "incl %edi;" // i++
        "jmp l1;"

    "end:;"
        "mov -32(%rbp), %rax;" // save return value in %rax

        "addq $40, %rsp;"
        "movq %rbp, %rsp;"
        "popq %rbp;"
        "ret;"
    );
}

int main(int argc, char const *argv[])
{
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    int **arr = malloc(m * sizeof(int *));
    for (int i=0; i<m; i++) {
        arr[i] = malloc(n * sizeof(int));
        for (int j=0; j<n; j++)
            scanf("%d", &arr[i][j]);
    }

    int **res = copy_2d_arr(arr, m, n);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }

    for (int i=0; i<m; i++) {
        free(arr[i]);
        free(res[i]);
    }
    free(arr);
    free(res);
    return 0;
}
