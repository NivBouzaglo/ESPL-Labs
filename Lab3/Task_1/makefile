all:1a

1a:	1a.o
	gcc	-g	-Wall	-o	1a	1a.o

1a.o:	1a.c
	gcc	-g	-Wall	-c	-o	1a.o	1a.c

.PHONY: clean
clean:
	rm -f *.o 1a
