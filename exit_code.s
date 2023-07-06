
.section .text

.globl _start

_start:
    movl $1, %eax # sys call for exit
    movl $10, %ebx # exit status code
    int $0x80 # wake kernal to exit



