# auther: Naman Tamrakar
# date: 07.07.2023
# decription: Program to create a add function and execute it.

.globl _start
.section .text

_start:
 pushl $10              # push second value in stack register %esp first
 pushl $5               # push first value in stack register %esp second
 call  add              # call add function
 movl  %eax, %ebx       # push return value in register %eax into %ebx
 movl  $1, %eax         # exit sys call
 int   $0x80            # invoke kernal

.type add, @function    # define function

add:
 pushl %ebp            # push the old base pointer into stack
 movl  %esp, %ebp      # make current stack position base pointer
 
 movl  8(%ebp), %eax   # put first arg into %eax, we have to move 2 byte one for return
                       # postion and second one if for old base pointer that we pushed above.
 movl  12(%ebp), %ebx  # put second arg into %ebx
 addl  %ebx, %eax      # add value into %eax register, which is our return value by default

 movl  %ebp, %esp      # restore stack pointer as it was before this function call
 popl  %ebp            # pop base pointer this function
 ret                   # return
