.globl _start
.section .text

_start:
 push $5
 call fact
 addl $4, %esp
 movl %eax, %ebx
 movl $1, %eax
 int $0x80

.type fact, @function

fact:
 push %ebp
 movl %esp, %ebp

 movl 8(%ebp), %eax

 cmpl $1, %eax
 je fact_ret

 decl %eax
 pushl %eax
 call fact

 imull 8(%ebp), %eax

fact_ret:
 movl %ebp, %esp
 popl %ebp
 ret
