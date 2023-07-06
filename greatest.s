.section .data

data_items:
.long 3,67,34,222,45,75,43


.section .text
.globl _start

_start:
 movl $0, %edi
 movl data_items(,%edi,4), %eax
 movl %eax, %ebx

start_loop:
 cmpl $0, %eax
 je loop_exit
 inc %edi
 movl data_items(,%edi,4), %eax
 cmpl %ebx, %eax
 jle start_loop

 movl %eax, %ebx

 jmp start_loop

loop_exit:
 movl $1, %eax
 int $0x80
