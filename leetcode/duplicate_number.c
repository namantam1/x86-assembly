#include <stdio.h>
#include <stdlib.h>

int findDuplicate_c(int* nums, int n){
    int k = 0;
    while (1) {
        int t = nums[k];
        if (t < 0)
            return k;
        nums[k] = -t;
        k = t;
    }
    return -1;
}

__attribute__((naked))
int findDuplicate(int* nums, int n){

    __asm__(
            "movl $0, %eax;"
        "l1:"
            "movl (%rdi,%rax,4), %ecx;"

            "cmpl $0, %ecx;"
            "jl end;"

            "movl %ecx, %edx;"
            "negl %ecx;"
            "movl %ecx, (%rdi,%rax,4);"
            "movl %edx, %eax;"

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
    printf("%d", findDuplicate(arr, n));
    free(arr);
    return 0;
}

