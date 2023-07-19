all:
	as -32 main.asm -o main.out
	ld -m elf_i386 -s main.out -o run

lib:
	as -32 main.asm -o main.out
	ld -dynamic-linker /lib/ld-linux.so.2 main.out -m elf_i386 -s -o run -lc

ln:
	ld -m elf_i386 -s a.out -o run

clean:
	rm -rf *.out *.exe run
