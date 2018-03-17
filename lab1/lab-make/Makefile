hello: hw_hello.o hw_power.o hw_defs.h hw_hello.h hw_power.h
		gcc -Wall -ansi -pedantic -lm hw_main.c hw_hello.o hw_power.o -o hello
		echo hello: zbudowane!

hw_hello.o: hw_hello.c hw_defs.h 
		gcc -c -Wall -ansi -pedantic hw_hello.c

hw_power.o: hw_power.c hw_defs.h 
		gcc -c -Wall -ansi -pedantic hw_power.c
