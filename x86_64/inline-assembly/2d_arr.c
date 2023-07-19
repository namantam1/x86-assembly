/*
auther: Naman Tamrakar
date: 2023-07-19

description: A sample program to add values in 2 array
*/

#include <stdio.h>
#include <stdlib.h>

int sol_C(int **arr, int m, int n) {
    int s = 0, i = 0;
    while (i < m) {
        int j = 0;
        while (j < n) {
            s += arr[i][j];
            j++;
        }
        i++;
    }
    return s;
}

__attribute__((naked))
int sol(int **arr, int m, int n) {
    __asm__(
        "push %rbp;"
        "movq %rsp, %rbp;"

        "movq %rdi, -8(%rbp);"
        "movl %esi, -16(%rbp);"
        "movl %edx, -24(%rbp);"

        // int s = 0
        "movl $0, %eax;"
        // i = 0;
        "movl $0, %ecx;"

    "l1:;"
        // while (i < m) {
        "cmpl -16(%rbp), %ecx;"
        "jge end;"

        // j = 0;
        "movl $0, %edx;"
    
    "l2:;"
        // while (j < n) {
        "cmpl -24(%rbp), %edx;"
        "jge l1_end;"

        // s += arr[i][j];
        "movq -8(%rbp), %rdi;"      // arr
        "movq (%rdi,%rcx,8), %rdi;" // arr[i]
        "movl (%rdi,%rdx,4), %edi;" // arr[i][j]
        "addl %edi, %eax;"

        // j++;
        "incl %edx;"
        "jmp l2;"

    "l1_end:;"
        //     i++;
        "incl %ecx;"
        "jmp l1;"

    "end:;"
        // return s;
        "movq %rbp, %rsp;"
        "popq %rbp;"
        "ret;"
    );
}




int main() {
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    int **arr = malloc(m * sizeof(int *));
    for (int i=0; i<m; i++) {
        arr[i] = malloc(n * sizeof(int));
        for (int j=0; j<n; j++)
            scanf("%d", &arr[i][j]);
    }
    printf("%d", sol(arr, m, n));

    for (int i=0; i<m; i++)
        free(arr[i]);
    free(arr);
}

