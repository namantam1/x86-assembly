# auther: Naman Tamrakar
# date: 06.07.2023
# description: Program to demonstrate factorial function in assembly.

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

 movl 8(%ebp), %eax         # get first param

 cmpl $1, %eax              # if value is 1 return from with this value only
 je fact_ret                # jump to function return block

 decl %eax                  # decrease value by 1
 pushl %eax                 # put this value on stack
 call fact                  # call function
 addl $4, %esp              # move stack pointer back, even if we do it, function will work 
                            # correctly as we have store stack refrence in %ebp which will restore stack in end correctly
 imull 8(%ebp), %eax        # multiply return value to current

fact_ret:
 # restore stack
 movl %ebp, %esp
 popl %ebp
 ret
