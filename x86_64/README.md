
# Concepts

### Understanding Registers:

The x86_64 architecture provides a set of general-purpose registers, each 64 bits wide. The registers are named as follows: `%rax`, `%rbx`, `%rcx`, `%rdx`, `%rsi`, `%rdi`, `%rbp`, `%rsp`, `%r8-%r15`.

Additionally, there are eight `64-bit` SIMD (Single Instruction, Multiple Data) registers: `%xmm0-%xmm7`, which can be used for floating numbers.

| C declaration | Intel data type | suffix | Size (Bytes) |
| :-----------: | :-------------: | :----: | :----------: |
|     char      |      Byte       |   b    |      1       |
|     short     |      Word       |   w    |      2       |
|      int      |      word       |   l    |      4       |
|   long int    |    Quad word    |   q    |      8       |
|    char *     |    Quad word    |   q    |      8       |

# References

- [Notes on x86-64 programming](https://www.lri.fr/~filliatr/ens/compil/x86-64.pdf)
- [x86-64 Machine-Level Programming](https://www.cs.cmu.edu/~fp/courses/15213-s07/misc/asm64-handout.pdf) by *Randal E. Bryant*
and *David R. O’Hallaron*
- [LINUX SYSTEM CALL TABLE FOR X86 64](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)

- [Error: invalid instruction suffix for `push`](https://stackoverflow.com/questions/21679131/error-invalid-instruction-suffix-for-push#:~:text=1%20Answer&text=The%20error%20you're%20getting,bit%20and%2064%2Dbit%20immediates).
- [Understanding Frame Pointers](https://people.cs.rutgers.edu/~pxk/419/notes/frames.html) with graphical example.****