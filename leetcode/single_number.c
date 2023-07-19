/*
auther: Naman Tamrakar
date: 2023-07-19

level: easy
url: https://leetcode.com/problems/single-number/
question: Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.
*/

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
        // int i=0, ans=0;
        "mov $0, %rax;"
        "mov $0, %rcx;"
    "l1:;"
        // while (i<n) {
        "cmp %rsi, %rcx;"
        "je end;"

        // ans ^= arr[i];
        "xor (%rdi,%rcx,4), %rax;"
        // i++;
        "inc %rcx;"
        "jmp l1;"
    "end:;"
        // return ans;
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
