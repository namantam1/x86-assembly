# Assembly tutorial

This repository contains the assembly code that I am writing while learning assembly programming from the book **Programming from the Ground Up** by **Jonathan Bartlell**.

Using this book I am learning assembly language for x86 processors and GNU/Linux operating system. So, To compile and link these program we can use command.

```bash
as exit.s -o exit.out
ld exit.out -o exit

# running the program
./exit

# check if exit code is correct
echo $? # prints exit code which above program emits
```

Below I have documented some of the topic that are very important to learn assembly language.

## How a assembly program works?

Operating system features are access through system calls. These system call are invoked by setting up registers in a special way and issue the instruction `int 0x80` where `int` stands for _interrupt_. Kernal knows which system call we want to access by what we store in __`%eax`__ register. Each system call has other requirements as to what needs to be stored in the other registers.

For example system call number 1 is the _exit_ system call, which required the status code to be placed in __`%ebx`__.

A basic assembly program contains two sections, `.text` and `.data` (not necessarily require).

Data section contains the contant or data that we use in our program thats why this sections is not necessary. 

Text section contains the logic for our program. It must define from where the execution should start by setting __`globl`__ instruction as `globl _start` which start the program execution from `_start` sections.

## Registers

On x86 processors there are several general purpose registers as

- %eax
- %ebx
- %ecx
- %edx
- %edi
- %asi

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

- __`idivl` :__ Requires that divident in `%eax` and `%edx` be zero, the quotient is then transferred to `%eax` and the remainder to `%edx`. However the divisor can be any register or memory location.

- __`cmpl` :__ Used to compare two values. This compare instruction affects a register, the `%eflags` known as __status register__. The result of comparision is stored in status register. After this instruction we can use flow control instruction to jump to other part of program.
  * `je`: Jump if values were equal.
  * `jg`: Jump if the second value greater than to the first.
  * `jge`: Jump if the second value greater than or quals to the first.
  * `jl`: Jump if the second value less than to the first.
  * `jle`: Jump if the second value less than or equal to the first.
  * `jmp`: Jump no matter what. It does not need to be proceeded by a comparison.
 
- __`incl` :__ Increase the value 

## Data Accessing Methods

We can access data in different ways.

1. __Immediate mode:__ This is simplest mode in which data to access is embedded in the instruction itself. So, If we want to initialze a reigster to 0, we can write instruction as `movl $0, %eax`. In this $ indicates we want to use immediate mode addressing.

2. __Register addressing mode:__ In this instruction contains a register to access, rather than a memory location.

3. __Direct addressing mode:__ In this instruction contains the memory address to access. For example we can say, Please load this register with data at address at 200.

4. __Index addressing mode:__ In this instruction contains a memory address along with an index register which specifies the offset to that address.

5. __Indirect addressing mode:__ In this instruction contains a register that contains a pointer to where the data should be accessed.

6. __Base pointer addressing mode:__ Similar to indirect addressing mode, but it includes a numver called the offset to add to register's value before using it for lookup.

## Order of programs to read

1. [exit.s](exit.s) - Program to show how to exit a program wich an exit status code.
2. [greatest.s](greatest.s) - Program to get largest integer from a list. Uses loops and conditional statements.
