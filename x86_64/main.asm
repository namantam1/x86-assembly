# auther: Naman Tamrakar
# date: 06.07.2023
# description: A sample program in 64-bit assembly to add a list and print sum to console


.section .data
array:
    .long 1,2,3,4,5   # Example array
array_end:
array_size = (array_end-array)/4

sum_msg:
    .asciz "Sum: %d\n"

.section .text
.globl _start

_start:
    # Iterate over the array
    movq $array, %rdx           # Load array address into rdx as address is 8 byte
    movl $array_size, %ecx      # Load array size into ecx as size is int (4 byte)

    # i = 0
    movl $0, %edi
    # Initialize sum to 0
    movl $0, %eax

sum_loop:
    cmpl %edi, %ecx             # check if i == size
    je sum_done                 # jump to end

    addl (%rdx,%rdi,4), %eax    # sum += arr[i]

    incl %edi                   # i++
    jmp sum_loop                # jump to loop start

sum_done:
    # Print the sum
    movq $sum_msg, %rdi
    movl  %eax, %esi
    call printf
    
    # Exit the program
    xor %rdi, %rdi              # Exit status 0
    movq $60, %rax              # System call number for exit
    syscall
