CC=gcc
CFLAGS=-I.

hellomake: main.o say.o
	$(CC) -o say.2.o main.o say.o $(CFLAGS)