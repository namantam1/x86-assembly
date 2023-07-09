.globl _start

.section .data
arr:
 .long 1,12,11,19
n:
 .long 4
sum:
 .long 12

.section .text

_start:
 movl $0, %edi # i

loop_i:
 cmpl n, %edi
 je loop_end

 movl arr(,%edi,4), %eax
 incl %edi
 movl %edi, %esi # j

loop_j:
 cmpl n, %esi
 je loop_i

 movl arr(,%esi,4), %ebx
 incl %esi

 addl %eax, %ebx
 cmpl %ebx, sum
 je loop_end

loop_end:
 addl %edi, %esi
 movl %esi, %ebx
 movl $1, %eax
 int $0x80


