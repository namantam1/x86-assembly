.globl _start

.section .text

_start:
 pushl $10
 pushl $5
 call add
 movl %eax, %ebx
 movl $1, %eax
 int $0x80

.type add, @function

add:
 pushl %ebp
 movl %esp, %ebp
 #subl $4, %esp

 movl 8(%ebp), %eax
 movl 12(%ebp), %ebx
 addl %ebx, %eax

 movl %ebp, %esp
 popl %ebp
 ret
