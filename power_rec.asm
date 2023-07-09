.globl _start
.section .text

_start:
 pushl $4 # power
 pushl $2 # value
 call pow
 addl $8, %esp

 movl %eax, %ebx
 movl $1, %eax
 int $0x80

.type pow, @function

pow:
 pushl %ebp
 movl %esp, %ebp

 movl 8(%ebp), %eax
 movl 12(%ebp), %ebx

 cmpl $1, %ebx
 je pow_ret

 decl %ebx
 pushl %ebx
 pushl %eax
 call pow
 addl $8, %esp
 imull 8(%ebp), %eax

pow_ret:
 movl %ebp, %esp
 popl %ebp
 ret
