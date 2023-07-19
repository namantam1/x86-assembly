# auther: Naman Tamrakar
# date: 06.07.2023
# description: A sample program to show recursion by implementing a recursive power function.

.globl _start
.section .text

_start:
 pushl $4                   # second param: power
 pushl $2                   # first param : value
 call pow                   # call pow function
 addl $8, %esp              # restore stack pointer

 movl %eax, %ebx            # set returned value as exit code
 movl $1, %eax              # exit sys call
 int $0x80                  # interrupt kernel

.type pow, @function        # pow function definition
pow:
 pushl %ebp                 # pust current base pointer into stack
 movl %esp, %ebp            # make base pointer as stack top(bottom)

 movl 8(%ebp), %eax         # first param : value
 movl 12(%ebp), %ebx        # second param: power

 cmpl $1, %ebx              # if power is 1 return value as it is
 je pow_ret                 # jump to end

 decl %ebx                  # otherwise decrese value by 1
 pushl %ebx                 # second param: power
 pushl %eax                 # first param : value
 call pow                   # call function
 addl $8, %esp              # restore stack
 imull 8(%ebp), %eax        # multiply current value with return value

pow_ret:
 # restore stack
 movl %ebp, %esp
 popl %ebp
 ret
