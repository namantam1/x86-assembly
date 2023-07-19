all:
	as main.asm -o main.out
	ld main.out -o run
	rm *.out

link:
	as main.asm -o main.out
	ld -dynamic-linker /lib/ld-linux.so.2 main.out -o run -lc
	rm *.out

clean:
	rm -rf *.out *.exe run
