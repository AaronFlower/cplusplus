CC=gcc

HDRS=$(wildcard *.h)

SRCS=$(wildcard *.c)

PROGS=$(patsubst  %.c, %, $(SRCS))

all: $(PROGS)

%:%.c $(HDRS)
	$(CC) -o $@ $<

.PHONY: clean

clean:
	rm $(PROGS)
