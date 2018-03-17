all: ex1open.o t.o
		gcc ex1open.o t.o -o wynik

ex1open.o: ex1open.c
		gcc ex1open.c -c -o ex1open.o
t.o: t.c t.h
		gcc t.c -c -o t.o
clean: ex1open.o
		rm ex1open.o
		
.PHONY: clean
