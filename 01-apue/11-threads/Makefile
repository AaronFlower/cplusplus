CC = gcc
FLAGS = -pthread


SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c, %, $(SRCS))

all: $(PROGS)

%:%.c
	$(CC) $(FLAGS) $^ -o $@

.PHONY:clean

clean:
	rm -rf $(PROGS)
