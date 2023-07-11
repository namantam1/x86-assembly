.globl _start


.section .data
 msg:
  .ascii "Hello World\n"
 msg_end:

.equ msg_len, msg_end-msg

.section .text
_start:
 movl $4, %eax
 movl $1, %ebx
 movl $msg, %ecx
 movl $msg_len, %edx
 int $0x80

 movl $1, %eax
 movl $0, %ebx
 int $0x80
