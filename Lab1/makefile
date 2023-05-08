all:encoder

encoder:	encoder.o
	gcc	-g	-Wall	-o	encoder	encoder.o

encoder.o:	task2.c
	gcc	-g	-Wall	-c	-o	encoder.o	task2.c

.PHONY: clean
clean:
	rm -f *.o encoder
