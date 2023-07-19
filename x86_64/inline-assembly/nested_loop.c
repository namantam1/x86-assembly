#include <stdio.h>

int sol_c(int m, int n) {
    int s = 0;
    int i=0;
    while (i<m) {
        int j=i+1;
        while (j<n) {
            s += i + j;
            j++;
        }
        i++;
    }
    return s;
}

__attribute__((naked))
int sol(int m, int n) {
    __asm__(
        "sub $64, %rsp;"
        "movl %edi, 16(%rsp);"
        "movl %esi, 24(%rsp);"

        "movl $0, %eax;"
        "movl $0, %edi;"

    "l1:;"
        "cmpl 16(%rsp), %edi;"
        "je end;"

        "movl %edi, %esi;"
        "incl %esi;"
    
    "l2:;"
        "cmpl 24(%rsp), %esi;"
        "je l2_end;"

        "addl %edi, %eax;"
        "addl %esi, %eax;"
        "incl %esi;"
        "jmp l2;"

    "l2_end:;"
        "incl %edi;"
        "jmp l1;"


    "end:;"
        "add $64, %rsp;"
        "ret;"
    );
}

int main() {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    printf("%d\n", sol(a, b));
}
