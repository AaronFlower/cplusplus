CC=gcc

All: build

build: 01-fork.c 02-fork.c
	$(CC) -o 1.out 01-fork.c
	$(CC) -o 2.out 02-fork.c

.PHONY: clean

clean:
	rm *.out
