#include <stdio.h>
#include <stdlib.h>

int *sol(int *a, int n, int k) {
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
            "push %rbp;"
            "mov %rsp, %rbp;"
            "sub $64, %rsp;"

            "movq $2, (%rcx);"

            "mov %rdi, 16(%rsp);"
            "mov %rsi, 24(%rsp);"
            "mov %rdx, 32(%rsp);"

            "mov $8, %rdi;"
            "call malloc;"

            "mov 16(%rsp), %rdi;"
            "mov 24(%rsp), %rsi;"
            "mov 32(%rsp), %rdx;"


            "mov $0, %r8;"

        "l1:;"
            "cmp %rsi, %r8;"
            "je end;"

            "mov %r8, %r9;"
            "add $1, %r9;"
            "jmp l2;"

        "l1_p:;"
            "add $1, %r8;"
            "jmp l1;"

        "l2:;"
            "cmp %rsi, %r9;"
            "je l1_p;"

            "mov (%rdi,%r8,4), %r10d;"
            "add (%rdi,%r9,4), %r10d;"

            "cmp %edx, %r10d;"
            "je done;"

            "add $1, %r9;"
            "jmp l2;"

        "done:;"
            "mov $0, %rsi;"
            "mov %r8, (%rax,%rsi,4);"
            "mov $1, %rsi;"
            "mov %r9, (%rax,%rsi,4);"

        "end:;"
            "add $64, %rsp;"
            "mov %rbp, %rsp;"
            "pop %rbp;"
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
    printf("%d %d %d", r, ans[0], ans[1]);
    free(arr);
    // free(ans);
    return 0;
}
