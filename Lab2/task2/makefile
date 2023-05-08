all: exec

exec: task2b.o
	gcc -g -Wall -o task2b task2b.o

task2b.o: task2b.c
	gcc -g	-Wall -c task2b.c -o task2b.o

.PHONY: clean
clean:
	rm -f *.o task2b