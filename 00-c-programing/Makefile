CC = gcc

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c, %, $(SRCS))

all: $(PROGS)

%:%.c
	$(CC) -Wall -O2 -o $@.out $^

.PHONY:clean

clean:
	rm -rf $(PROGS)
