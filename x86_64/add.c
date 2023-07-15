#include <stdio.h>

__attribute__((naked)) 
int sum(int a, int b) {
    __asm__(
        "movl %edi, %eax;"
        "add %esi, %eax;"
        "ret;"
    );
}

int main() {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    printf("%d", sum(a, b));
    return 0;
}