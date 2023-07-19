# auther: Naman Tamrakar
# date: 06.07.2023
# description: A sample program to show how to make a write system call to print buffer in console.

.globl _start


.section .data
 msg:
  .ascii "Hello World\n"
 msg_end:

.equ msg_len, msg_end-msg

.section .text
_start:
 movl $4, %eax          # sys call for write
 movl $1, %ebx          # set fd which is 1 for stdout
 movl $msg, %ecx        # set buffer address
 movl $msg_len, %edx    # set msg size
 int $0x80              # interrupt kernel to make sys call

 # exit program with successfull status code
 movl $1, %eax
 movl $0, %ebx
 int $0x80
