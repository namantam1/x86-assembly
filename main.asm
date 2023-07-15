.section .data
array:
    .quad 1, 2, 3, 4, 5   # Example array

array_size = 5
sum_msg:
    .asciz "Sum: %d\n"

.section .text
.globl _start
_start:
    # Initialize sum to 0
    xor %rax, %rax

    # Iterate over the array
    mov $array, %rdi        # Load array address
    mov $array_size, %rcx  # Load array size

sum_loop:
    cmp $0, %rcx           # Compare array size with 0
    je sum_done            # If array size is 0, exit loop

    # Add current element to sum
    addq (%rdi), %rax

    # Move to the next element
    add $8, %rdi

    # Decrement array size
    sub $1, %rcx

    jmp sum_loop           # Jump to the beginning of the loop

sum_done:
    # Print the sum
    # Exit the program
    xor %rax, %rdi         # Exit status 0
    mov $60, %rax          # System call number for exit
    syscall
