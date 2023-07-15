#include <stdio.h>
#include <stdlib.h>

char findTheDifference_c(char * s, char * t){
    int i=0;
    int ans=t[i];
    while (s[i]!='\0') {
        ans += t[i+1] - s[i];
        i++;
    }
    return ans;
}

// miss behaving
__attribute__((naked))
char findTheDifference(char * s, char * t){
    __asm__(
            "movl $0, %edx;"
            "movl (%rsi,%rdx,1), %eax;"

        "l1:;"
            "cmpl $0, (%rdi,%rdx,1);"
            "je end;"

            "subl (%rdi,%rdx,1), %eax;"
            "incl %edx;"
            "addl (%rsi,%rdx,1), %eax;"

            "jmp l1;"

        "end:;"
            "ret;"
    );
}

const int MAX_VAL = 1001;

int main() {
    char s[MAX_VAL], t[MAX_VAL];
    scanf("%s", s);
    scanf("%s", t);
    printf("%c", findTheDifference(s, t));
    return 0;
}

