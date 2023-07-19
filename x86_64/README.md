
# Concepts

### Understanding Registers:

The x86_64 architecture provides a set of general-purpose registers, each 64 bits wide. The registers are named as follows: `%rax`, `%rbx`, `%rcx`, `%rdx`, `%rsi`, `%rdi`, `%rbp`, `%rsp`, `%r8-%r15`.

Additionally, there are eight `64-bit` SIMD (Single Instruction, Multiple Data) registers: `%xmm0-%xmm7`, which can be used for floating numbers.

| C declaration | Intel data type | GAS suffix | x86-64 Size (Bytes) |
| :-----------: | :-------------: | :--------: | :-----------------: |
|     char      |      Byte       |     b      |          1          |
|     short     |      Word       |     w      |          2          |
|      int      |      word       |     l      |          4          |
|   long int    |    Quad word    |     q      |          8          |
|    char *     |    Quad word    |     q      |          8          |

# References

- https://www.lri.fr/~filliatr/ens/compil/x86-64.pdf
- https://www.cs.cmu.edu/~fp/courses/15213-s07/misc/asm64-handout.pdf
- https://people.cs.rutgers.edu/~pxk/419/notes/frames.html