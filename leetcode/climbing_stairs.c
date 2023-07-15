#include <stdio.h>
#include <stdlib.h>

__attribute__((naked))
int climbStairs(int n) {
    // int *t = malloc((n+1) * sizeof(int));

    // t[0] = t[1] = 1;
    // for (int i=2; i<=n; i++)
    //     t[i] = t[i-1] + t[i-2];
    
    // int ans = t[n];
    // free(t);
    // return ans;


    // __asm__(
    //     "sub $64, %rsp;"
    //     "mov %rdi, 16(%rsp);"

    //     "add $1, %rdi;"
    //     "imul $4, %rdi;"
    //     "call malloc;"
    //     "mov %rax, 24(%rsp);"

    //     "movl $1, (%rax);"
    //     "movl $1, 4(%rax);"
    //     "movl $2, %edx;"

    // "l1:;"
    //     "cmpl 16(%rsp), %edx;"
    //     "jg l1_end;"

    //     "movl %edx, %ecx;"
    //     "decl %ecx;"
    //     "movl (%rax,%rcx,4), %esi;"
        
    //     "decl %ecx;"
    //     "add (%rax,%rcx,4), %esi;"
    //     "movl %esi, (%rax,%rdx,4);"

    //     "incl %edx;"
    //     "jmp l1;"

    // "l1_end:;"
    //     "movl 16(%rsp), %edx;"
    //     "movl (%rax,%rdx,4), %esi;"
    //     "movl %esi, 32(%rsp);"

    //     "mov 24(%rsp), %rdi;"
    //     "call free;"

    //     "movl 32(%rsp), %eax;"

    //     "add $64, %rsp;"
    //     "ret;"
    // );

    // int pre_pre = 1, pre = 1, i = 2;
    // while (i<=n) {
    //     int tmp = pre + pre_pre;
    //     pre_pre = pre;
    //     pre = tmp;
    //     i++
    // }
    // return pre;

    // __asm__(
    //     "movl $1, %eax;"
    //     "movl $1, %ecx;"
    //     "movl $2, %edx;"
    // "l1:;"
    //     "cmpl %edi, %edx;"
    //     "jg end;"

    //     "movl %eax, %esi;"
    //     "addl %ecx, %esi;"
    //     "movl %eax, %ecx;"
    //     "movl %esi, %eax;"

    //     "incl %edx;"
    //     "jmp l1;"

    // "end:;"
    //     "ret;"
    // );
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", climbStairs(n));
}
