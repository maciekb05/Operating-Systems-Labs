prog.o: prog.c
		gcc -Wall -ansi -pedantic prog.c -o prog.o

prog.c: ex2sysconf.sh
		./ex2sysconf.sh > prog.c
