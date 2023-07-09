# Assembly tutorial

This repository provides the assembly programs I wrote while studying assembly programming from many different sources, including the book _"Programming from the Ground Up"_ by _Jonathan Bartlell_.

This book is a must-read if you want to understand how a CPU runs programs, how memory is allocated, and how it switches back and forth between RAM and the CPU to do calculations and save results. Additionally, you'll gain a thorough grasp of how high-level programs like C/C++ translate into machine code.

These assembly programs are 32-bit programs for an **x86 processor** and Linux operating system with **AT&T** syntax which can be compiled using _GNU/GCC compiler_.

> **❗Important Note:** As I am new to assembly programming, the information provided in this repository might not be entirely accurate or error-free, despite my best efforts to prevent them. The knowledge contained in this repository is the result of information I've learned from a variety of sources.
>
> Your comments are very appreciated if you discover any incorrect information. For it, you may create a PR. For further information, see the guidelines for your contributions.

The code can be compiled, linked, and executed as follows:

```bash
# compile
as -32 exit.s -o exit.out

# link
ld -m elf_i386 -s exit.out -o exit

# execute
./exit

# check if the exit code is correct
echo $? # prints exit code which the above program emits
```

> These programs can be executed directly on Linux, Mac (not tested), Windows(by installing WSL), or by using the pythonanywhere.com terminal.

# Chapters 📖

These chapters walk you through step-by-step assembly programming using concepts from other programming languages that you are likely already familiar with, including print, the **Hello World** program, conditions, loops, and functions.

You will learn it in these chapters along with an example of how it might appear in C.

## 1. First assembly program

Your first program would have been a **Hello World** program for the majority of programming languages you may have learned up to this point, but developing a **Hello World** program in assembly is a bit more difficult and is covered in later chapters.

So what will be the first assembly program we write?

_really straightforward, a program that configures some registers and checks to see if they are configured properly by setting exit code_

```asm
.section .text                     
.globl _start
           
_start:
 movl $1, %eax # sys call for exit
 movl $10, %ebx # exit status code
 int $0x80 # wake kernal to exit 
```

Similar code in C

```c
int main() {
 return 0;
}
```

To check the exit code run

```bash
echo $? # will output 10
```

## 2. Conditional Statement (if/else)

In this, you will get to know how you can write conditional statements in assembly programs.

```asm
.section .text                     
.globl _start
           
_start:
 movl $1, %eax
 movl $10, %ebx
 movl $9, %ecx

 cmpl %ebx, %ecx
 jge end

 

end:
 movl $1, %eax # sys call for exit
 movl $10, %ebx # exit status code
 int $0x80 # wake kernal to exit 
```

Similar C program

```c
int main() {
 int x = 10;
 if (x >= 9)
  return x;
 return 0;
}
```

___

Below are some topics that are very important to learn assembly language.

## How an assembly program works⚙️?

Operating system features are accessed through system calls. These system calls are invoked by setting up registers in a special way and issuing the instruction `int 0x80` where `int` stands for _interrupt_. Kernal knows which system call you want to access by what you store in __`%eax`__ register. Each system call has other requirements as to what needs to be stored in the different registers.

For example, system call number 1 is the _exit_ system call, which required the status code to be placed in __`%ebx`__.

```asm
movl $1,  %eax # system call
movl $10, %ebx # set exit status code
int $0x80      # interrupt kernel
```

A basic assembly program contains two sections, `.text` and `.data` (not necessarily required).

The data section contains the content or data that you can use in your program that's why this section is not necessary. 

The text section contains the logic for your program. It must define from where the execution should start by setting __`globl`__ instruction as `globl _start` which starts the program execution from `_start` sections.

## Registers 💻

On _x86 processors_, there are several general-purpose registers as

- `%eax`
- `%ebx`
- `%ecx`
- `%edx`
- `%edi`
- `%esi`

In addition to that, there are also several special-purpose registers as

- `%ebp`
- `%esp`
- `%eip`
- `%eflags`

## Assembly Instructions

- __`movl` :__ It has two operands, source and destination i.e. `movl $src_reg, %dest_reg`.

- __`addl` :__ Add the source operate to destination.

- __`subl` :__ Subract the source operand from destination.

- __`imull` :__ Multiply the source operant by destination.

- __`incl` :__ Increase the value by 1, like i++

- __`decl` :__ Descrese the value by 1, like i--

- __`idivl` :__ Requires that divident in `%eax` and `%edx` be zero, the quotient is then transferred to `%eax` and the remainder to `%edx`. However, the divisor can be any register or memory location.

- __`cmpl` :__ Used to compare two values. This compare instruction affects a register, the `%eflags` known as __status register__. The result of the comparison is stored in a status register. After this instruction, you can use flow control instruction to jump to other parts of the program.
  * `je`: Jump if values were equal.
  * `jg`: Jump if the second value is greater than the first.
  * `jge`: Jump if the second value is greater than or equal to the first.
  * `jl`: Jump if the second value is less than the first.
  * `jle`: Jump if the second value less than or equal to the first.
  * `jmp`: Jump no matter what. It does not need to be proceeded by a comparison.


## Data Accessing Methods

The general form of memory address reference is:

`address_Or_offset(base_Or_offset,index,multiplier)`

Above all the fields are options, To calculate the address use the formula:

`final_address = address_Or_offset + base_Or_offset + multiplier * index`

> `multiplier` and `address_Or_offset` both must be constant, while the other two must be registers. If any of the pieces are left out, it is just substituted with zero.

You can access data in different ways.

1. __Immediate mode:__ This is the simplest mode in which data to access is embedded in the instruction itself. Example: 
   ```asm
   movl $0, %eax
   ```

   This load register %eax with a value of 0. `$` indicates you want to use immediate mode addressing.

1. __Register addressing mode:__ In this instruction contains a register to access, rather than a memory location. Example:
   ```asm
   movl %eax, %ebx
   ```

   Copy value stored in register `%eax` to register `%ebx`.

1. __Direct addressing mode:__ In this, the instruction contains the memory address to access. For example, you can say, Please load this register with data at the address at 200. Example:
   ```asm
   movl ADDR, %eax
   ```

   The above program loads the register `%eax` value at the memory address ADDR.

1. __Index addressing mode:__ In this instruction contains a memory address along with an index register that specifies the offset to that address.
   ```asm
   .section .data
     .int 1,2,3,4

   .
   .
   movl data_start(,%ecx, 2), %eax
   ```

   **Multiplier** is set as 2 here, as the size of int is 2 bytes. `%ecx` contains the index of data to access.

1. __Indirect addressing mode:__ In this instruction contains a register that contains a pointer to where the data should be accessed. If `%eax` held an address, you can move the value at that address to `%ebx` as
   ```asm
   movl (%eax), %ebx
   ```

1. __Base pointer addressing mode:__ Similar to indirect addressing mode, but it includes a number called the offset to add to the register's value before using it for lookup. For example, if you have a record where the value is 4 bytes into the record, and you have the address of the record in `%eax`, you can retrieve the value into `%ebx` as
   ```asm
   movl 4(%eax), %ebx
   ```

## Functions

In the CPU we have a limited number of registers to store variables, you need to have some way to store local values in a structural way while calling functions to avoid loss of data as those functions can also call other functions. 

This is where the computer's _stack_ comes into the picture. To get the current top of the stack, the stack register `%esp` is used.

> **Note:** The computer stack grows downwards until it touches the data or text section of programs and crashed with a stack overflow error.

**Important points to remember:**

- To push value to stack use `pushl` instruction, `%esp` gets subtracted by 4 to point to new top of stack.
  ```asm
  pushl $4 # push value 4 into stack
  ```

- To remove something from the stack, use `popl` instruction, `%esp` gets added by 4.
  ```asm
  popl %eax # pop the top value into %eax
  ```

- To simply access the value on the top of the stack without removing it, you can use `%esp` in indirect addressing mode.
  ```asm
  movl (%esp), %eax
  ```

**How to execute a function in assembly?**

Before executing a function, a program should push all of the parameters for the function onto the stack in the reverse order that they are documented. Then the program issues a `call` instruction indicating which function to call. It does two things, it first pushes the address of the next instruction which is the return address onto the stack. Then it modifies the instruction pointer `%eip` to start of the function.

In a function, you can access all of the data by using a base pointer using a different offset from `%ebp`. `%ebp` was made specifically for this purpose which is why it is called the _base pointer_.

When a function is done executing it should:

- store return value in `%eax`.
- reset stack to what it was when it was called.
- return control back to wherever it was called from by using `ret` instruction.


This is how all the function and its execution looks like in general. Below is an example of a sum function:

```asm
pushl $10        # push second arg
pushl $20        # push first arg
call  fun_name   # call function, which stores the result in %eax register
addl  $8, %esp   # reset stack (function cleanup)

# get the result as exit code
movl  %eax, %ebx
movl  $1, %eax
int   $0x80


# tell compiled that fun_name is a function
.type fun_name, @function

# function definition
.fun_name:
pushl %ebp            # save old base pointer
movl  %esp, %ebp      # make stack pointer the base pointer

movl  8(%ebp), %ebx   # get first arg
movl  12(%ebp), %ecx  # get second arg
movl  %ebx, %eax      # copy first val to res
movl  %ecx, %eax      # add second val to res

# restore stack before returning
movl  %ebp, %esp      # restore stack pointer
popl  %ebp            # restore base pointer
ret
```

## Files

### Opening a file with mode and permission

- `%eax` will hold 5 for the sys call
- address of the first character if filename should be stored in `%ebx`.
- Read/Write indentions represented as a number should be stored in `%ecx`. You can use 0 for files you want to read from and **03101** for files you want to write to.
- Files permission should be stored as a number in `%edx`. You can in general use **0666** for permissions.

```asm
movl $5,    %eax
movl $0,    %ebx
movl $0666, %ecx
int $0x80
```

The above instruction will return a file description in `%eax`. This number you can use to refer to this file throughout your program.


### Read/Write from/to a file using the file descriptor

- read and write is a system call with values 3 and 4 respectively.
- fd should be stored in `%ebx`.
- The address of a buffer for the data that is to be read is stored in `%ecx`.
- The size of the buffer should be stored in `%edx`. `.bss.read` will return either number of bytes read or the error code. In the case of write, `%eax` will contain the number of bytes written or an error code.

### Close a file

The close system call is 6. The only parameter to `close` is the fd placed in `%ebx`.

> `.bss` section of the program is like the data section, except that it doesn't take space in the executable. This section can reserve storage, but you can't initialize it. In the `.data` section, you can't set an initial value.

__For Example :__

```asm
.section .bss
.lcomm my_buffer, 500 # It will reserve 500 bytes of storage which you
                      # can use as a buffer
```

### FD for standard and specific files

- STDIN:  0, it is a read-only file.
- STDOUT: 1, it is a write-only file.
- STDERR: 2, it is a write-only file.

## Order of programs to read

1. [exit.s](exit.s) - Program to show how to exit a program with an exit status code.
2. [greatest.s](greatest.s) - Program to get largest integer from a list. Uses loops and conditional statements.
