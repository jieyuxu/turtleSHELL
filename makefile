make: shell.c
	gcc shell.c -o shell.out
run: 
	./shell.out
clean:
	rm -rf *~
