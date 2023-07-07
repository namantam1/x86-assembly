.globl _start
.section .text

_start:
 pushl $3
 pushl $2
 call pow
 addl $8, %esp

 pushl %eax

 pushl $2
 pushl $5
 call pow
 addl $8, %esp

 popl %ebx

 addl %eax, %ebx
 movl $1, %eax
 int $0x80

.type pow, @function

pow:
 pushl %ebp
 movl %esp, %ebp

 movl 8(%ebp), %eax
 movl 12(%ebp), %ebx
 movl %eax, %ecx

loop:
 cmpl $1, %ebx
 je end_loop

 imul %ecx, %eax
 decl %ebx

 jmp loop

end_loop:
 movl %ebp, %esp
 popl %ebp
 ret
