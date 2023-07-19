
.globl _start
.section .text

_start:
 pushl $9
 call sqr
 movl %eax, %ebx
 movl $1, %eax
 int $0x80


.type sqr, @function


sqr:
 pushl %ebp
 movl %esp, %ebp

 movl 8(%ebp), %eax
 imul %eax, %eax

 movl %ebp, %esp
 popl %ebp
 ret
