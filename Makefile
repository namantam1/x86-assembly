all:
	as main.s -o main.out
	ld main.out -o run
	rm *.out

e:
	echo $?

c:
	rm *.out run
