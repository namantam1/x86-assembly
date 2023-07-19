# auther: Naman Tamrakar
# date: 06.07.2023
# description: A sample program to show recursion by implementing a recursive power function.

.globl _start
.section .text

_start:
 pushl $3               # second param: power
 pushl $2               # first param : value
 call pow               # call function
 addl $8, %esp          # restore stack

 movl %eax, %ebx        # put return value as exit code
 movl $1, %eax          # exit sys call
 int $0x80              # interrupt kernel

.type pow, @function    # function definition
pow:
 pushl %ebp             # pust current base pointer into stack
 movl %esp, %ebp        # make base pointer as stack top(bottom)

 movl 8(%ebp), %eax     # first param : value
 movl 12(%ebp), %ebx    # second param: power
 movl %eax, %ecx        # take value as accumulator

loop:
 cmpl $1, %ebx          # check if power is 1
 je end_loop            # then break loop

 imul %ecx, %eax        # multiply value and save into accumulator
 decl %ebx              # decrease power by 1

 jmp loop               # jump to loop start

end_loop:
 # restore stack
 movl %ebp, %esp
 popl %ebp
 ret
