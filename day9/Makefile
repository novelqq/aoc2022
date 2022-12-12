CC=gcc
CFLAGS=-Wall -g

all: main

main: main.c hash.o
	$(CC) $(CFLAGS) -o main main.c hash.c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c

clean:
	rm -f main *.o
