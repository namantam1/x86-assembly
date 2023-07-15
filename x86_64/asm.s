.section .data
array:
  .quad 1, 2, 3, 4, 5
sum_message:
  .asciz "Sum of array elements: %d\n"

.section .text
.globl _start
_start:
  mov $array, %rdi     # Pass the array address in %rdi
  mov $5, %rsi         # Pass the size of the array (e.g., 5) in %rsi
  call sum_array       # Call the function
  mov %rax, %rbx       # Store the returned sum in %rbx

  mov $sum_message, %rdi  # Pass the sum message address in %rdi
  mov %rbx, %rsi          # Pass the sum value in %rsi
  xor %rax, %rax          # Set %rax to 0 (file descriptor for stdout)
  mov $0x0F, %al          # System call number for sys_write
  xor %rdx, %rdx          # Clear %rdx (position parameter)
  mov $4, %rcx            # Message length
  syscall

exit:
  mov $60, %rax        # System call number for exit
  xor %rdi, %rdi       # Exit status code (0)
  syscall

sum_array:
  push %rbp            # Save the previous base pointer
  mov %rsp, %rbp       # Update the base pointer with the current stack pointer
  push %rsi            # Save the size on the stack

  xor %rax, %rax       # Initialize the sum to 0
  xor %ecx, %ecx       # Initialize the loop counter to 0

sum_loop:
  cmp %ecx, %esi       # Compare the loop counter with the size
  je sum_done          # Jump to sum_done if the loop counter equals the size

  addq (%rdi,%rcx,8), %rax  # Add the value at array[loop_counter] to the sum
  inc %ecx                 # Increment the loop counter
  jmp sum_loop             # Jump back to sum_loop

sum_done:
  pop %rsi             # Restore the size from the stack
  pop %rbp             # Restore the previous base pointer
  ret                  # Return from the subroutine
