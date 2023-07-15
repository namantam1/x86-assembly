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
            "movl $0, %eax;"
        "l1:;"
            "movq %rax, %rdx;"
            "imul %rdx, %rdx;"

            "cmp %rdi, %rdx;"
            "jg end;"

            "incl %eax;"
            "jmp l1;"
        "end:;"
            "decl %eax;"
            "ret;"
    );
}

int main() {
    int k;
    scanf("%d", &k);
    printf("%d", mySqrt(k));
}
