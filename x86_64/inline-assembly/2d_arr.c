#include <stdio.h>
#include <stdlib.h>


int sol_c(int **arr, int m, int n) {
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
// int sol(int **arr, int m, int n) {
//     __asm__(
//         "push %rbp;"
//         "movq %rsp, %rbp;"

//         "movq %rdi, -8(%rbp);"
//         "movl %esi, -16(%rbp);"
//         "movl %edx, -24(%rbp);"

//         "movl $0, %eax;"
//         "movl $0, %ecx;"

//     "l1:;"
//         "cmpl -16(%rbp), %ecx;"
//         "jge end;"

//         "movl $0, %edx;"
    
//     "l2:;"
//         "cmpl -24(%rbp), %edx;"
//         "jge l1_end;"

//         "movq -8(%rbp), %rdi;"
//         "movq (%rdi,%rcx,8), %rdi;" // i
//         "movl (%rdi,%rdx,4), %edi;" // j
//         "addl %edi, %eax;"

//         "incl %edx;"
//         "jmp l2;"

//     "l1_end:;"
//         "incl %ecx;"
//         "jmp l1;"

//     "end:;"
//         "leave;"
//         "ret;"
//     );
// }


__attribute__((naked))
int **malloc_2d(int a, int b) {
    // int **arr = malloc(a * sizeof(int *));
    // int c = 1;
    // for (int i=0; i<a; i++) {
    //     arr[i] = malloc(b * sizeof(int));
    //     for (int j=0; j<b; j++) {
    //         arr[i][j] = c++;
    //     }
    // }
    // return arr;

    __asm__(
        "push %rbx;"
        "sub $40, %rsp;"
        "movl %edi, 8(%rsp);"
        "movl %esi, 16(%rsp);"
        
        "movl 8(%rsp), %edi;"
        "imul $8, %rdi;"
        "call malloc;"
        "movq %rax, 24(%rsp);"

        "movl $0, %ebx;"
    "l0:;"
        "cmpl 8(%rsp), %ebx;"
        "je l0_end;"

        "movl 16(%rsp), %edi;"
        "imul $4, %rdi;"
        "call malloc;"
        "movq 24(%rsp), %rdi;"
        "movq %rax, (%rdi,%rbx,8);"

        "incl %ebx;"
        "jmp l0;"

    "l0_end:;"
        "movl $1, %eax;"
        "movl $0, %ecx;"

    "l1:;"
        "cmpl 8(%rsp), %ecx;"
        "je end;"

        "movl $0, %edx;"
    "l2:"
        "cmpl 16(%rsp), %edx;"
        "je l1_end;"

        "movq 24(%rsp), %rdi;"
        "movq (%rdi,%rcx,8), %rdi;"
        "movl %eax, (%rdi,%rdx,4);"

        "incl %eax;"
        "incl %edx;"
        "jmp l2;"

    "l1_end:;"
        "incl %ecx;"
        "jmp l1;"

    //     "movl $0, %ebx;"

    // "l3:;"
    //     "cmpl 8(%rsp), %ebx;"
    //     "je end;"

    //     "movq 24(%rsp), %rdi;"
    //     "movq (%rdi,%rbx,8), %rdi;"
    //     "call free;"

    //     "incl %ebx;"
    //     "jmp l3;"

    "end:;"
        // "movq 24(%rsp), %rdi;"
        // "call free;"

        "mov 24(%rsp), %rax;"

        "add $40, %rsp;"
        "pop %rbx;"
        "ret;"
    );
}

int main() {
    int m, n;
    scanf("%d", &m);
    scanf("%d", &n);
    // int **arr = malloc(m * sizeof(int *));
    // for (int i=0; i<m; i++) {
    //     arr[i] = malloc(n * sizeof(int));
    //     for (int j=0; j<n; j++)
    //         scanf("%d", &arr[i][j]);
    // }
    // printf("%d", sol(arr, m, n));

    int **arr = malloc_2d(m, n);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    for (int i=0; i<m; i++)
        free(arr[i]);
    free(arr);

}

