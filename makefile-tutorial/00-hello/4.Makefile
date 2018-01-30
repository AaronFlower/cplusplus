CC=gcc
CFLAGS=-I.
DEPS = say.h
OBJ = main.o say.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	gcc -o say.4.o $^ $(CFLAGS)
