CC=gcc
CFLAGS=-I.
DEPS = say.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: main.o say.o
	gcc -o say.3.o main.o say.o -I.