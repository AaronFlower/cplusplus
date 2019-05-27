CC = gcc

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c, %, $(SRCS))

all: $(PROGS)

%:%.c
	$(CC) -o $@ $^

.PHONY:clean

clean:
	rm -rf $(PROGS)
