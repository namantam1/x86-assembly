all:
	as -32 main.asm -o main.out
	ld -m elf_i386 -s main.out -o run
	rm *.out

e:
	echo $?

c:
	rm -rf *.out *.exe run
