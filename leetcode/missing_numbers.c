#include <stdio.h>
#include <stdlib.h>

int missingNumber_c(int *arr, int n) {
    int s = n * (n + 1) / 2;
    int i = 0;
    while (i < n) {
        s -= arr[i];
        i++;
    }
    return s;
}

__attribute__((naked))
int missingNumber(int* arr, int n){
    __asm__(
            "mov %rsi, %rax;"
            "add $1, %rax;"
            "imul %rsi, %rax;"
            "shr $1, %rax;"

            "movl $0, %ecx;"

        "l1:;"
            "cmpl %esi, %ecx;"
            "je end;"

            "sub (%rdi,%rcx,4), %rax;"
            "incl %ecx;"
            "jmp l1;"

        "end:;"
            "ret;"
    ); 
}


int main() {
    int n;
    scanf("%d", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    printf("%d", missingNumber(arr, n));
    free(arr);
    return 0;
}

