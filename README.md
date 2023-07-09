# Assembly tutorial

This repository contains the assembly programs, I created while learning assembly programming from the book **Programming from the Ground Up** by **Jonathan Bartlell**.

These assembly programs are for an x86 32-bit processor and Linux operating system 
 with **AT&T** syntax. which can be compiled using GNU/GCC compiler.

The code can be compiled, linked, and executed as follows:

```bash
as exit.s -o exit.out
ld exit.out -o exit

# running the program
./exit

# check if the exit code is correct
echo $? # prints exit code which the above program emits
```

> If you are on a Windows OS, either you can install WSL or can use the pythonanywhere.com console to run these programs.

Below I have documented some of the topics that are very important to learn assembly language.

## How an assembly program works?

Operating system features are accessed through system calls. These system calls are invoked by setting up registers in a special way and issuing the instruction `int 0x80` where `int` stands for _interrupt_. Kernal knows which system call we want to access by what we store in __`%eax`__ register. Each system call has other requirements as to what needs to be stored in the different registers.

For example, system call number 1 is the _exit_ system call, which required the status code to be placed in __`%ebx`__.

```asm
movl $1,  %eax # system call
movl $10, %ebx # set exit status code
int $0x80      # interrupt kernel
```

A basic assembly program contains two sections, `.text` and `.data` (not necessarily required).

The data section contains the content or data that we use in our program that's why this section is not necessary. 

The text section contains the logic for our program. It must define from where the execution should start by setting __`globl`__ instruction as `globl _start` which starts the program execution from `_start` sections.

## Registers

On x86 processors, there are several general-purpose registers as

- %eax
- %ebx
- %ecx
- %edx
- %edi
- %esi

In addition to that, there are also several special-purpose registers as

- %ebp
- %esp
- %eip
- %eflags

## Assembly Instructions

- __`movl` :__ It has two operands, source and destination i.e. `movl $source, %dest_reigster`.

- __`addl` :__ Add the source operate to destination.

- __`subl` :__ Subract the source operand from destination.

- __`imull` :__ Multiply the source operant by destination.

- __`incl` :__ Increase the value by 1, like i++

- __`decl` :__ Descrese the value by 1, like i--

- __`idivl` :__ Requires that divident in `%eax` and `%edx` be zero, the quotient is then transferred to `%eax` and the remainder to `%edx`. However the divisor can be any register or memory location.

- __`cmpl` :__ Used to compare two values. This compare instruction affects a register, the `%eflags` known as __status register__. The result of comparision is stored in status register. After this instruction we can use flow control instruction to jump to other part of program.
  * `je`: Jump if values were equal.
  * `jg`: Jump if the second value greater than to the first.
  * `jge`: Jump if the second value greater than or quals to the first.
  * `jl`: Jump if the second value less than to the first.
  * `jle`: Jump if the second value less than or equal to the first.
  * `jmp`: Jump no matter what. It does not need to be proceeded by a comparison.


## Data Accessing Methods

The general form of memory address reference is:

`address_Or_offset(base_Or_offset,index,multiplier)`

Above all the fields are options, To calculate the address use the formula:

`final_address = address_Or_offset + base_Or_offset + multiplier * index`

> `multiplier` and `address_Or_offset` both must be constant, while the other two must be registers. If any of the pieces are left out, it is just substituted with zero.

We can access data in different ways.

1. __Immediate mode:__ This is the simplest mode in which data to access is embedded in the instruction itself. Example: 
   ```asm
   movl $0, %eax
   ```

   This load register %eax with a value of 0. `$` indicates we want to use immediate mode addressing.

1. __Register addressing mode:__ In this instruction contains a register to access, rather than a memory location. Example:
   ```asm
   movl %eax, %ebx
   ```

   Copy value stored in register `%eax` to register `%ebx`.

1. __Direct addressing mode:__ In this instruction contains the memory address to access. For example, we can say, Please load this register with data at the address at 200. Example:
   ```asm
   movl ADDR, %eax
   ```

   The above program loads the register %eax value at the memory address ADDR.

1. __Index addressing mode:__ In this instruction contains a memory address along with an index register that specifies the offset to that address.
   ```asm
   .section .data
     .int 1,2,3,4

   .
   .
   movl data_start(,%ecx, 2), %eax
   ```

   `Multiplier` is set as 2 here, as the size of int is 2 bytes. `%ecx` contains the index of data to access.

1. __Indirect addressing mode:__ In this instruction contains a register that contains a pointer to where the data should be accessed. If `%eax` held an address, we can move the value at that address to %ebx as
   ```asm
   movl (%eax), %ebx
   ```

1. __Base pointer addressing mode:__ Similar to indirect addressing mode, but it includes a number called the offset to add to the register's value before using it for lookup. For example, if you have a record where the value is 4 bytes into the record, and you have the address of the record in `%eax`, you can retrieve the value into `%ebx` as
   ```asm
   movl 4(%eax), %ebx
   ```

## Functions

## Files

### Opening a file with mode and permission

- %eax will hold 5 for the sys call
- address of the first character if filename should be stored in %ebx.
- Read/Write indentions represented as a number should be stored in %ecx. You can use 0 for files you want to read from and 03101 for files you want to write to.
- Files permission should be stored as a number in %edx. We can in general use 0666 for permissions.

```asm
movl $5,    %eax
movl $0,    %ebx
movl $0666, %ecx
int $0x80
```

The above instruction will return a file description in %eax. This number you can use to refer to this file throughout your program.


### Read/Write from/to a file using the file descriptor

- read and write is a system call 3 and 4 respectively.
- fd should be stored in %ebx.
- The address of a buffer for the data that is read stored in %ecx.
- The size of the buffer should be stored in %edx. `.bss.read` will return either number of bytes read or the error code. In the case of write, %eax will contain the number of bytes written or an error code.

### Close a file

The close system call is 6. The only parameter to `close` is the fd placed in %ebx.

> `.bss` section of the program is like the data section, except that it doesn't take space in the executable. This section can reserve storage, but you can't initialize it. In the `.data` section, you can't set an initial value.

__For Example :__

```asm
.section .bss
.lcomm my_buffer, 500 # It will reserve 500 bytes of storage which we
                      # can use as a buffer
```

### FD for standard and specific files

- STDIN:  0, it is a read-only file.
- STDOUT: 1, it is a write-only file.
- STDERR: 2, it is a write-only file.

## Order of programs to read

1. [exit.s](exit.s) - Program to show how to exit a program with an exit status code.
2. [greatest.s](greatest.s) - Program to get largest integer from a list. Uses loops and conditional statements.
