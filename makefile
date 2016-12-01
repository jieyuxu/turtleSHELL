GCC = gcc -g

all: shell.o trex.o
	$(GCC) shell.o trex.o -o shell.out

shell.o: shell.c shell.h
	$(GCC) shell.c

trex.o: t_rex.c t_rex.h
	$(GCC) t_rex.c

run: 
	./shell.out

clean:
	rm -rf *~
