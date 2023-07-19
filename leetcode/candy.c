/*
auther: Naman Tamrakar
date: 2023-07-18

level: hard
url: https://leetcode.com/problems/candy/
question: There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.
*/

#include <stdio.h>
#include <stdlib.h>

int candy_c(int* v, int n){
    int *t = malloc(n * sizeof(int));
    int i=0;
    while (i<n) {
        t[i] = 1;
        i++;
    }
    i = 1;
    int j = n-2;
    while (i<n) {
        if (v[i]>v[i-1] && t[i]<=t[i-1]) {
            t[i] = t[i-1]+1;
        }
        
        if (v[j]>v[j+1] && t[j]<=t[j+1]) {
            t[j] = t[j+1]+1;
        }        
        i++;
        j--;
    }
    int ans=0;
    i = 0;
    while (i<n) {
        if (t[i]>1)
            ans += t[i];
        else
            ans += 1;
        i++;
    }
    free(t);
    return ans;
}


__attribute__((naked))
int candy(int* v, int n){
    __asm__(
        "pushq %rbp;"
        "movq %rsp, %rbp;"
        "sub $64, %rsp;"

        "movq %rdi, -8(%rbp);"
        "movl %esi, -16(%rbp);"
        
        // int *t = malloc(n * sizeof(int))
        "movl %esi, %edi;"
        "imul $4, %rdi;"
        "call malloc;"
        "movq %rax, -24(%rbp);"
        
        // int i=0;
        "movl $0, %ecx;"

    // while (i<n) {
    "l1:;"
        "cmpl -16(%rbp), %ecx;"
        "je l1_end;"

        // t[i] = 1;
        "movq -24(%rbp), %rdi;"
        "movl $1, (%rdi,%rcx,4);"

        // i++;
        "incl %ecx;"
        // }
        "jmp l1;"

    "l1_end:;"
        // i = 1;
        "movl $1, %ecx;"
        // int j = n-2;
        "movl -16(%rbp), %edx;"
        "subl $2, %edx;"

    // while (i<n) {
    "l2:;"
        "cmpl -16(%rbp), %ecx;"
        "je l2_end;"
        
        "movq -8(%rbp), %rsi;" // v
        "movq -24(%rbp), %rdi;" // t

        // if (v[i]>v[i-1] && t[i]<=t[i-1]) {
        //     t[i] = t[i-1]+1;
        // }
        "movl %ecx, %r8d;" 
        "decl %r8d;" // i - 1
        "movl (%rsi,%r8,4), %eax;" // v[i-1]

        "cmpl (%rsi,%rcx,4), %eax;"
        "jge l2_c1;"


        "movl (%rdi,%r8,4), %eax;" // t[i-1]

        "cmpl (%rdi,%rcx,4), %eax;"
        "jl l2_c1;"

        "incl %eax;"
        "movl %eax, (%rdi,%rcx,4);" // t[i] = t[i-1]

        
    "l2_c1:;"
        
        // if (v[j]>v[j+1] && t[j]<=t[j+1]) {
        //     t[j] = t[j+1]+1;
        // }
        "movl %edx, %r8d;" 
        "incl %r8d;" // j + 1

        "movl (%rsi,%r8,4), %eax;" // v[j+1]

        "cmpl (%rsi,%rdx,4), %eax;"
        "jge l2_c2;"

        "movl (%rdi,%r8,4), %eax;" // t[j+1]

        "cmpl (%rdi,%rdx,4), %eax;"
        "jl l2_c2;"

        "incl %eax;"
        "movl %eax, (%rdi,%rdx,4);" // t[j] = t[j+1]
    
    "l2_c2:;"
        // i++;
        "incl %ecx;"
        // j--;
        "decl %edx;"
        // }
        "jmp l2;"

    "l2_end:;"
        // int ans=0;
        "movl $0, %eax;"
        // i = 0;
        "movl $0, %ecx;"
        "movq -24(%rbp), %rsi;"

    // while (i<n) {
    "l3:;"
        "cmpl -16(%rbp), %ecx;"
        "je l3_end;"


        // if (t[i]>1)
        //     ans += t[i];
        // else
        //     ans += 1;
        "cmpl $1, (%rsi,%rcx,4);"
        "jg l3_if;"

        "incl %eax;"
        "jmp l3_c;"

    "l3_if:;"
        "addl (%rsi,%rcx,4), %eax;"
    
    "l3_c:;"
        // i++;
        "incl %ecx;"
        // }
        "jmp l3;"

    "l3_end:;"
        "movl %eax, -40(%rbp);"

        // free(t);
        "movq -24(%rbp), %rdi;"
        "call free;"
    
        // return ans;
        "movl -40(%rbp), %eax;"

        "add $64, %rsp;"
        "movq %rbp, %rsp;"
        "popq %rbp;"
        "ret;"
    );
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    printf("%d\n", candy(arr, n));
    return 0;
}

