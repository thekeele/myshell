CFLAGS=-Wall -g

all: compile run clean

compile: 
	g++ myshell.c -o myshell

run:
	./myshell

clean:
	rm -f a.out
	rm -f myshell
	rm -f myshell.o
