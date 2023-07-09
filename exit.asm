# auther: Naman Tamrakar
# date: 06.07.2023
# description: A sample program to exits with a certain exit code
#              exit code can be in range [0, 255].
# memory:
#    %eax - store sys call
#    %ebx - store exist status for this sys call


.section .text
.globl _start

_start:
    movl $1, %eax # sys call for exit
    movl $10, %ebx # exit status code
    int $0x80 # wake kernal to exit
