all: exec

exec: addresses.o
	gcc -g -Wall -o 1a addresses.o

addresses.o: addresses.c
	gcc -g	-Wall -c addresses.c -o addresses.o

.PHONY: clean
clean:
	rm -f *.o 1a