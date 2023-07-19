/*
auther: Naman Tamrakar
date: 2023-07-19

level: easy
url: https://leetcode.com/problems/missing-number/
question: Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.
*/

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
            // int s = n * (n + 1) / 2;
            "movq %rsi, %rax;"
            "incq %rax;"    // n+1
            "imul %rsi, %rax;" // n * (n+1)
            "shr $1, %rax;" // divide by by right shift

            // int i = 0;
            "movl $0, %ecx;"

        "l1:;"
            // while (i < n) {
            "cmpl %esi, %ecx;"
            "je end;"

            // s -= arr[i];
            "subq (%rdi,%rcx,4), %rax;"
            // i++;
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

