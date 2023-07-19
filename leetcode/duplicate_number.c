/*
auther: Naman Tamrakar
date: 2023-07-18

level: medium
url: https://leetcode.com/problems/find-the-duplicate-number/
question: Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and uses only constant extra space.
*/

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
            // int k = 0;
            "movl $0, %eax;"
        "l1:"
            // int t = nums[k];
            "movl (%rdi,%rax,4), %ecx;"

            // if (t < 0)
            "cmpl $0, %ecx;"
            "jl end;"

            // nums[k] = -t;
            "movl %ecx, %edx;"
            "negl %ecx;"
            "movl %ecx, (%rdi,%rax,4);"
            // k = t;
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

