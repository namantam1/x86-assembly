all:
	as -32 main.asm -o main.out
	ld -m elf_i386 -s main.out -o run
	rm *.out

link:
	as -32 main.asm -o main.out
	ld -dynamic-linker /lib/ld-linux.so.2 main.out -m elf_i386 -s -o run -lc
	rm *.out


e:
	echo $?

c:
	rm -rf *.out *.exe run
