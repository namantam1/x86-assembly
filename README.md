[![License](https://img.shields.io/github/license/namantam1/x86-assembly)](https://github.com/namantam1/x86-assembly)
![GitHub last commit (by committer)](https://img.shields.io/github/last-commit/namantam1/x86-assembly)

<!-- omit from toc -->
# Table of Contents

- [Introduction](#introduction)
- [✨Some Basics✨ (Very Very Important)](#some-basics-very-very-important)
- [Compiling and Execution](#compiling-and-execution)
- [Chapters 📖](#chapters-)
    - [First assembly program](#first-assembly-program)
    - ["Hello World!" Program 👋](#hello-world-program-)
    - [Conditional Statement (if/else)](#conditional-statement-ifelse)
    - [Loops (for/while/do while)](#loops-forwhiledo-while)
    - [Functions](#functions)
    - [Using `C` library functions](#using-c-library-functions)
    - [Writing Inline assembly in `C`](#writing-inline-assembly-in-c)
- [Important topics](#important-topics)
    - [Assembly Instructions](#assembly-instructions)
    - [Data Accessing Methods](#data-accessing-methods)
    - [File handling](#file-handling)
      - [Opening a file with mode and permission](#opening-a-file-with-mode-and-permission)
      - [Read/Write from/to a file using the file descriptor](#readwrite-fromto-a-file-using-the-file-descriptor)
      - [Closing files](#closing-files)
      - [FD for standard and specific files](#fd-for-standard-and-specific-files)
- [Assembly program for _x86\_64 processor_ (64-bit)](#assembly-program-for-x86_64-processor-64-bit)
- [Leetcode](#leetcode)
- [Why learn assembly language](#why-learn-assembly-language)
- [Conclusion](#conclusion)
- [References](#references)



# Introduction

This repository contains the assembly programs I implemented while studying assembly programming from many different sources, including the book _"Programming from the Ground Up"_ by _Jonathan Bartlell_.

This book is highly recommended if you want to understand how a computer runs programs, how memory is allocated, and how data moves back and forth between RAM and the CPU (registers) to do calculations and save results. Additionally, you'll gain a thorough grasp of how high-level programs like C/C++ compile down to machine code which computers can understand and execute.

These assembly programs in this repository are 32-bit and 64-bit programs for an **x86 processor** and Linux operating system with **AT&T** syntax which can be compiled using _GNU/GCC compiler_.

> 👉 **Important❗** As I am new to assembly programming, the information provided in this repository might not be entirely accurate or error-free, despite my best efforts to prevent them. The knowledge contained in this repository is the result of information I've learned from a variety of sources.
>
> Your comments are very appreciated if you discover any incorrect information. For it, you may create a PR. For further information, see the [contribution guidelines](./CONTRIBUTING.md) for your contributions.
>
> 👉 The reader is assumed to have a fundamental understanding of C/C++ in order to follow this assembly programming lesson. You can relate to the idea discussed in this guide more if you are proficient in C/C++. To comprehend the notion in the upcoming context, we will use the C programming language as base language.
>
> 👉 The programs in this repository can be executed using GCC compiler on Linux and Windows(by installing WSL).

# ✨Some Basics✨ (Very Very Important)

What does a basic program look like in C?

1. variable definition (char, int, long, array).
2. some if/else conditions.
3. some loops.
4. calling functions.

That's it, almost every programming language has at least these four things that we can do, but the question is how the computer interprets and run it. 

Every program requires CPU and RAM to run, I'm not saying only these two are required, but for understanding the basics we need to focus on these two only.

Every CPU has some general purpose registers and some special registers, We can think of these registers as memory locations in the CPU. For example, the _x86 32-bit processor_ has the general-purpose register such as `%eax`, `%ebx`, `%ecx`, `%edx`, `%edi` and `%esi`

In addition to these, there are also some special-purpose registers, including:

- `%ebp`: Base pointer register
- `%esp`: Stack pointer register
- `%eip`: Instruction pointer register
- `%eflags`: status register

Depending on the CPU architecture, each register can hold data of size either `32-bit` for a *32-bit processor* or `64-bit` for a *64-bit processor*. Since the number of variables used can be more than the number of registers, We need to store data somewhere else.

RAM enters the picture at this point. Data can be kept in RAM and pointed to a register using its RAM address. As a result, during program execution, data may transfer from RAM to CPU and, following processing, may return to RAM.

> **✨Note:** In the incoming sections, you will learn assembly for *32-bit* processor. Once you are comfortable with *32-bit* assembly programming you can move to *64-bit* assembly pragramming [here](./x86_64/README.md).

Operating system features are accessed through system calls. These system calls are invoked by setting up registers in a special way and issuing the instruction `int $0x80` where int stands for interrupt. Kernal knows which system call you want to access by what you store in `%eax` register. Each system call has other requirements as to what needs to be stored in the different registers.

Conditional statements, loops and functions are discussed in detail in upcoming topics.

# Compiling and Execution

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

# Chapters 📖

These chapters walk you through step-by-step assembly programming using concepts from other programming languages that you are likely already familiar with such as conditions, loops, functions, printing to console and many others.

You will learn it in these chapters along with the example of how you write it in `C` language.

### First assembly program

Your first program would have been a **Hello World** program for the majority of programming languages you may have learned up to this point, but developing a **Hello World** program in assembly is a bit more difficult and is covered in later chapters.

So what will be the first assembly program we write?

We will write a very simple program that exits with a certain exit code. You can write a C program for it as:

```c
int main() {
 return 0;
}
```

To accomplish the same in assembly

```s
.section .text                     
.globl _start
           
_start:
 movl $1, %eax # sys call for exit
 movl $10, %ebx # exit status code
 int $0x80 # wake kernal to exit 
```

- The First line in the above code tells the compiler that the logic of the program starts from there which is `.text` section. There can be other sections in the program such as `.data` section and `.bss` section which is discussed later.

- `.globl _start` tells from which block of code execution of the program should start.

- `_start:` tells `_start` block starts here.

- The `movl` is an assembly instruction with two `operands` that says the data to move from first to second. Check more instructions in the [assembly instructions](#assembly-instructions) section.

- `$` sign before the first operand indicated we want to use immediate addressing mode which embeds the data into the instruction itself. Please check [data accessing [methods](#data-accessing-methods) for a details discussion on it.

- 1 is set into `%eax` register for the exit syscall and `%ebx` is set with an exit code value that is 10.

- `int $0x80` is used to interrupt the kernel and issue the system call.


To verify the exit code of the above program run

```bash
echo $? # will output 10
```

### "Hello World!" Program 👋

Exit status codes were previously used as a program's output, however, they shouldn't be used for this. You must be aware by this point that a system call, such as the one you just made by setting the `%eax` register to 1, is required to execute any type of I/O. In the same way, you would need to make a system call to print something to the console. 

To accomplish this, set the `%eax` register to 4 to initiate a **write** system call. You need to set the `%ebx` register to the file descriptor value, which is 1 for `stdout`, the `%ecx` register to the location of the buffer, and the `%edx` register to the size of the message to print.

For a thorough description of opening, closing, reading, and writing files, refer to the [files](#files) section.

Here is an example of an assembly program

```s
.globl _start


.section .data
 msg:
  .ascii "Hello World\n"

.section .text
_start:
 movl $4, %eax          # sys call for write
 movl $1, %ebx          # set fd which is 1 for stdout
 movl $msg, %ecx        # set buffer address
 movl $12, %edx         # set msg size
 int $0x80              # interrupt kernel to make sys call

 # exit program with successfull status code
 movl $1, %eax
 movl $0, %ebx
 int $0x80
```

### Conditional Statement (if/else)

Programming relies heavily on condition statements, such as the if, if-else, and else statements. To do this in assembly, use the **jump** instruction to jump to another section of the program. With the use of **jump**, you can make several branches that help in managing the program's workflow.

We must first compare some values using the `cmpl` instruction, which saves the outcome in a specially designated register called the `%eflags` register, before we may conditionally jump. Below is the list of instructions to jump based on the result of compare.

* `je`: Jump if values were equal.
* `jg`: Jump if the second value is greater than the first.
* `jge`: Jump if the second value is greater than or equal to the first.
* `jl`: Jump if the second value is less than the first.
* `jle`: Jump if the second value less than or equal to the first.
* `jmp`: Jump no matter what. It does not need to be proceeded by a comparison.

For example:

```c
int main() {
 int x = 10;
 if (x >= 9)
  return x;
 return 0;
}
```

We can write the corresponding assembly code as:

```s
.globl _start
.section .text

_start:
 movl $1, %eax   # exit sys call
 movl $10, %ebx  # put value in %ebx, which is exit status of register also
 movl $9, %ecx   # put value to compare in condition in %ecx

 cmpl %ecx, %ebx # compare 10 with 9 if its greater than equal to
 jge end_block   # if condition meet jump to the end
 movl $0, %ebx   # otherwise set 0 in exit status register
end_block:
 int $0x80       # interrupt kernel
```


### Loops (for/while/do while)

Similar to if/else conditions you can use **jump** instruction to create a loop in the assembly.

For example:

```c
int main() {
  int sum = 0;
  int i = 10;
  while (i > 0) {
    sum += i;
    i--;
  }

  return sum;
}
```

The corresponding assembly program can be written as:

```s
.globl _start  
.section .text

_start:
 movl $1, %eax   # set sys call
 movl $0, %ebx   # initialze %ebx (status code register) to 0
 movl $10, %ecx  # store 10 in %ecx

loop:
 addl %ecx, %ebx # add current value to %ebx
 decl %ecx       # decrease %ecx by 1

end:
 cmpl $0, %ecx   # check if greater than 0
 jg loop         # if so jump to loop until the condition is made

 int $0x80       # interrupt kernel
```

### Functions

Functions are a crucial component of programming that helps in the development of code that is reusable, modular, and maintained. You must have been taught that when we call a function stack is used internally to keep track of data used from where it is called and of functions while studying functions in other programming languages. You will see how this is done in assembly.

We only have a limited amount of registers, thus when calling a function, you must keep local variables (in registers) where they won't be lost because the function may mutate and utilize the same register. Additionally, you need to have a structured manner to store data so that you can simply restore it after running the function. `%esp`, a unique register that is referred to as a stack register, is used to help with this.

A program should use the `pushl` instruction to push all of the function's parameters onto the stack before the function is executed, in the opposite order that they are listed in the documentation. Then issue a `call` instruction specifying which function name to call. It initially pushes the return address, which is the address of the following instruction, into the stack. After that, it changes the instruction pointer `%eip` to refer to the function's start.

> **Note:** Computer stack expands downward until it reaches the text or data portions of programs, at which point it crash programs due to a stack overflow error.

In a function, you can access all of the data by using a base pointer using a different offset from `%ebp`. `%ebp` was made specifically for this purpose which is why it is called the _base pointer_.

**✨Important✨:** Following are the step to set up function parameters, define a function, call the function, and give control back to the point where it is called.

1. push function parameters in reverse order using `pushl` instruction.
1. call the function by issuing a `call` instruction with the function name.
1. define function anywhere in the program file as `.type <function_name>, @function`.
1. start the function block with the function name.
1. Now the first two instructions should be to store the old base pointer in the stack and make the stack current position your base point.
   ```asm
   pushl %ebp            # save old base pointer
   movl  %esp, %ebp      # make stack pointer the base pointer
   ```
1. Get the function parameter by using the `%ebp` register in base pointer addressing mode.
1. Do calculations.
1. store the return value in `%eax`.
1. reset the stack to what it was when it was called by using the instructions `movl %ebp %esp` and `popl %ebp`.
1. return control back to wherever it was called from by using `ret` instruction.


For example:

```c
int sum(int a, int b) {
  return a + b;
}

int main() {
  int s = sum(10, 20);
  return s;
}
```

The corresponding assembly program will look like this:

```s
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

### Using `C` library functions

The **"Hello World"** program mentioned above uses the system call `write` to print a message to the console, although this is not advised because it is difficult to fill up each block of buffer with an ASCII value if you wish to display a dynamic message.

Therefore, we can utilize the standard `printf` function with signature `int printf(const char *restrict format, ...);` provided by `libc` rather than making a direct sys call.

For example:

```c
#include <stdio.h>

int main() {
  printf("Value of x is %d\n", 10);
  return 0;
}
```

We can write the corresponding assembly code as:

```s
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
```

To compile the above code you need to tell the linker to link `libc` so that you can utilize the `printf` function provided by it. We can compile, link and execute the above code as:

```bash
as -32 main.asm -o main.out
ld -dynamic-linker /lib/ld-linux.so.2 main.out -m elf_i386 -s -o run -lc

./run
# output: Value of x is 10
```

You can see that the format string is terminated with a `NULL` since `printf` requires a string buffer and assumes that the buffer's endpoint is terminated with a `NULL`.

> 👉 Similary, You can use other functions provided in `libc`, and to get their signature you can check their **man** page.

### Writing Inline assembly in `C`



# Important topics

### Assembly Instructions

- __`movl` :__ It has two operands, source and destination i.e. `movl $src_reg, %dest_reg`.

- __`addl` :__ Add the source operand to the destination.

- __`subl` :__ Subract the source operand from the destination.

- __`imull` :__ Multiply the source operant by the destination.

- __`incl` :__ Increase the value by 1, like `i++`

- __`decl` :__ Decrease the value by 1, like `i--`

- __`idivl` :__ Requires that dividend in `%eax` and `%edx` be zero, the quotient is then transferred to `%eax` and the remainder to `%edx`. However, the divisor can be any register or memory location.


### Data Accessing Methods

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

   This load registers `%eax` with a value of 0. `$` indicates you want to use immediate mode addressing.

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

1. __Base pointer addressing mode:__ Similar to indirect addressing mode, it includes a number called the offset to add to the register's value before using it for lookup. For example, if you have a record where the value is 4 bytes into the record, and you have the address of the record in `%eax`, you can retrieve the value into `%ebx` as
   ```asm
   movl 4(%eax), %ebx
   ```

### File handling

#### Opening a file with mode and permission

- `%eax` will hold 5 for the sys call
- address of the first character if the filename should be stored in `%ebx`.
- Read/Write indentions represented as a number should be stored in `%ecx`. You can use 0 for files you want to read from and **03101** for files you want to write to.
- Files permission should be stored as a number in `%edx`. You can in general use **0666** for permissions.

```asm
movl $5,    %eax
movl $0,    %ebx
movl $0666, %ecx
int $0x80
```

The above instruction will return a file description in `%eax`. This number you can use to refer to this file throughout your program.


#### Read/Write from/to a file using the file descriptor

- read and write is a system call with values 3 and 4 respectively.
- fd should be stored in `%ebx`.
- The address of a buffer for the data that is to be read is stored in `%ecx`.
- The size of the buffer should be stored in `%edx`. `.bss.read` will return either number of bytes read or the error code. In the case of write, `%eax` will contain the number of bytes written or an error code.

#### Closing files

The close system call is 6. The only parameter to `close` is the fd placed in `%ebx`.

> `.bss` section of the program is like the data section, except that it doesn't take space in the executable. This section can reserve storage, but you can't initialize it. In the `.data` section, you can't set an initial value.

__For Example :__

```asm
.section .bss
.lcomm my_buffer, 500 # It will reserve 500 bytes of storage which you
                      # can use as a buffer
```

#### FD for standard and specific files

- STDIN:  0, it is a read-only file.
- STDOUT: 1, it is a write-only file.
- STDERR: 2, it is a write-only file.

# Assembly program for _x86_64 processor_ (64-bit)

Since writing assembly in `32-bit` mode is simple, up until now, our main focus has been on learning assembly programs and developing some fundamental programming skills.

When developing assembly programs, there are no significant differences between `32-bit` and `64-bit` modes. Check out the 'x86_64' directory and accompanying [instructions](./x86_64/README.md#inline-assembly-in-c) to learn assembly in '64-bit' mode.

# Leetcode

Once you have mastered `x86_64` assembly, you can write `inline assembly` in `C` to solve problems on `leetcode`. The `leetcode` directory contains some solutions along with their explanations.

# Why learn assembly language

# Conclusion


# References

- https://www.lri.fr/~filliatr/ens/compil/x86-64.pdf
- https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
- https://developer.arm.com/documentation/100067/0612/Compiler-specific-Function--Variable--and-Type-Attributes/--attribute----naked---function-attribute
- https://godbolt.org/
- https://www.geeksforgeeks.org/compile-32-bit-program-64-bit-gcc-c-c/
- https://gist.github.com/mishurov/6bcf04df329973c15044

- https://stackoverflow.com/questions/21679131/error-invalid-instruction-suffix-for-push#:~:text=1%20Answer&text=The%20error%20you're%20getting,bit%20and%2064%2Dbit%20immediates.
