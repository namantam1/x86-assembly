.globl _start
.section .text

_start:
 push $5                    # put first params into stack
 call fact                  # call function
 addl $4, %esp              # restore stack
 movl %eax, %ebx            # set exit code to return value of function
 movl $1, %eax              # exit sys call
 int $0x80                  # interrupt kernel

.type fact, @function       # define function

fact:
 push %ebp                  # push base pointer into stack
 movl %esp, %ebp            # point base pointer to stack

 movl 8(%ebp), %eax         # get first

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
