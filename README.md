# Assembly tutorial

This repo contains the code that I am learning from book **Prgramming from the Ground Up** by **Jonathan Bartlell**.

Using this book I am learning assembly language for x86 processors and GNU/Linux operating system. So to compile and link those program we can use command.

```bash
as main.s -o main.out
ld main.out -o main

# running the program
./main
```

Below I have documented some of the topic that are important to learn assembly language.

## How a assembly program works?

Operating system features are access through system calls. These system call are invoked by setting up registers in a special way and issue the instruction `int 0x80`. Kernal know which system call we want to access by what we store in __`%eax`__ register. Each system call has other requirements as to what needs to be stored in the other registers.

For example system call number 1 is the _exit_ system call, which required the status code to be placed in __`%ebx`__

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

## Data Accessing Methods

We can access data in different ways.

1. __Immediate mode:__ This is simplest mode in which data to access is embedded in the instruction itself. So, If we want to initialze a reigster to 0, we can write instruction as `movl $0, %eax`. In this $ indicates we want to use immediate mode addressing.

2. __Register addressing mode:__ In this instruction contains a register to access, rather than a memory location.

3. __Direct addressing mode:__ In this instruction contains the memory address to access. For example we can say, Please load this register with data at address at 200.

4. __Index addressing mode:__ In this instruction contains a memory address along with an index register which specifies the offset to that address.

5. __Indirect addressing mode:__ In this instruction contains a register that contains a pointer to where the data should be accessed.

6. __Base pointer addressing mode:__ Similar to indirect addressing mode, but it includes a numver called the offset to add to register's value before using it for lookup.
