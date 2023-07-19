all:
	as main.asm -o main.out
	ld main.out -o run

lib:
	as main.asm -o main.out
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 main.out -o run -lc

ln:
	ld a.out -o run

clean:
	rm -rf *.out *.exe run
