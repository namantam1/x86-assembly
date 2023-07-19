/*
auther: Naman Tamrakar
date: 2023-07-19

description: A sample program to show how you can write a function implementation in assembly 

which takes an array and return its sum. `Sum_C` is c implementation of this function, its curresponding 
assembly instruction in explained how an instruction in c can be written in assembly.
*/

#include <stdio.h>
#include <stdlib.h>

int sum_C(int *a, int n) {
    int s = 0;
    int i = 0;
    while (i < n) {
        s += a[i];
        i++;
    }
    return s;
}

__attribute__((naked)) 
int sum(int *a, int n) {
    __asm__(
        // s = 0
        "movl $0, %eax;"
        // i = 0
        "movl $0, %ecx;"

    "loop:;"
        // if i == n then jump to end
        "cmpl %esi, %ecx;"
        "je end;"

        // s += a[i]
        "addl (%rdi, %rcx, 4), %eax;"

        // i++
        "incl %ecx;"
        // jump to loop start
        "jmp loop;"

    "end:"
        // when done return as result already saved in %eax register
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
