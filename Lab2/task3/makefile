all: exec

exec: menu.o
	gcc -g -Wall -o task3 menu.o

menu.o: menu.c
	gcc -g -Wall -c menu.c -o menu.o

.PHONY: clean
clean:
	rm -f *.o task3