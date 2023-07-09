# auther: Naman Tamrakar
# date: 06.07.2023
# description: A sample program to get the greatest number out of given list of integers.
# data types: other data types are byte(8 bit), int(16 bit), ascii
# memory:
#  %edi - index
#  %ebx - largest value
#  %eax - current value at index


# data section to store data used in program
.section .data
 data_items: # integer values stored in 32 bit long with 0 at end to terminate
 .long 3,67,34,222,45,75,43,0


.section .text
.globl _start

_start:
 movl $0, %edi                   # start at 0 index
 movl data_items(,%edi,4), %eax  # load first value into %eax, beginaddre(,indexregister,wordsize)
 movl %eax, %ebx                 # current value is largest value

start_loop:
 cmpl $0, %eax                   # check if end of list
 je loop_exit                    # if so exit, where je is jump equals
 inc %edi                        # increase the index
 movl data_items(,%edi,4), %eax  # load value at current index
 cmpl %ebx, %eax                 # compare current with largest
 jle start_loop                  # jump to loop beginning if current value less 
                                 # than equal to largest value
 movl %eax, %ebx                 # else move that value to largest value register
 jmp start_loop                  # jump to loop beginning

loop_exit:
 movl $1, %eax                  # sys call to exit
 int $0x80                      # invoke kernal
