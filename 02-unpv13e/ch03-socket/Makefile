CC=gcc
FLAGS = -std=c99

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c, %, $(SRCS))

$(info PROGS = $(PROGS))

all: $(PROGS)

%: %.c
	$(CC) $(FLAGS) -o $@ $^

.PHONY: clean

clean:
	rm $(PROGS)
