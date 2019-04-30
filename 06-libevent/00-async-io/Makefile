CC=gcc

SRCS=$(wildcard *.c)

PROGS=$(patsubst %.c, %, $(SRCS))

all: $(PROGS)

%:%.c
	gcc -o $@ $^


.PHONY: clean

clean:
	rm -rf $(PROGS)
