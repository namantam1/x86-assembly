/*
auther: Naman Tamrakar
date: 2023-07-19

level: easy
url: https://leetcode.com/problems/sqrtx/
question: Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.
*/

#include <stdio.h>
#include <stdlib.h>

int mySqrt_c(int x){
    long int i = 0;
    while (i*i <= x)
        i++;
    return i-1;
}

__attribute__((naked))
int mySqrt(int x){
    __asm__(
            // long int i = 0;
            "movl $0, %eax;"
        "l1:;"
            // while (i*i <= x)
            "movq %rax, %rdx;"
            "imul %rdx, %rdx;"

            "cmp %rdi, %rdx;"
            "jg end;"

            //     i++;
            "incl %eax;"
            "jmp l1;"
        "end:;"
            // return i-1;
            "decl %eax;"
            "ret;"
    );
}

int main() {
    int k;
    scanf("%d", &k);
    printf("%d", mySqrt(k));
}
