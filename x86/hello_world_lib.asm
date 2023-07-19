.globl _start

.section .data

msg:
.ascii "Value of x is %d\n\0"

.section .text
_start:
pushl $10          # set second param as int value
pushl $msg         # set first param as formatted string
call printf        # call printf function

# exit program with success exit code
movl $1, %eax
movl $0, %ebx
int $0x80
