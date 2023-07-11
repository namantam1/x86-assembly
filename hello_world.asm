.globl _start


.section .data
 msg:
  .ascii "Hello World\n"


.section .text
_start:
 movl $4, %eax
 movl $1, %ebx
 movl $msg, %ecx
 movl $12, %edx
 int $0x80

 movl $1, %eax
 movl $0, %ebx
 int $0x80
