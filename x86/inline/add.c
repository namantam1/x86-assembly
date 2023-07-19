/*
auther: Naman Tamrakar
date: 2023-07-20
*/

#include <stdio.h>

__attribute__((naked)) 
int sum(int a, int b) {
    __asm__(
        "pushl %ebp;"
        "movl %esp, %ebp;"
        "movl 8(%ebp), %eax;"  // s = a
        "addl 12(%ebp), %eax;"  // s += b
        "movl %ebp, %esp;"
        "popl %ebp;"
        "ret;"
    );
}

int main() {
    printf("%d\n", sum(10, 20));
    return 0;
}
