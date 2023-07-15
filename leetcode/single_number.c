#include <stdio.h>
#include <stdlib.h>

int singleNumber_c(int *arr, int n) {
    int i=0, ans=0;
    while (i<n) {
        ans ^= arr[i];
        i++;
    }
    return ans;
}

__attribute__((naked))
int singleNumber(int* arr, int n){
    __asm__(
            "mov $0, %rax;"
            "mov $0, %rcx;"
        "l1:;"
            "cmp %rsi, %rcx;"
            "je end;"

            "xor (%rdi,%rcx,4), %rax;"
            "inc %rcx;"

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
    printf("%d", singleNumber(arr, n));
    free(arr);
    return 0;
}
