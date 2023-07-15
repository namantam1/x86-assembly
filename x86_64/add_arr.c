#include <stdio.h>
#include <stdlib.h>

__attribute__((naked)) 
int sum(int *a, int n) {
    __asm__(
        "movl $0, %eax;"
        "movl $0, %ecx;"

    "loop:;"
        "cmpl %esi, %ecx;"
        "je end;"

        "addl (%rdi, %rcx, 4), %eax;"
        "incl %ecx;"
        "jmp loop;"

    "end:"
        "ret;"
    );
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    printf("%d", sum(arr, n));
    free(arr);
    return 0;
}
