CC=gcc

SRCS=$(wildcard *.c)

PROGS = $(patsubst %.c, %, $(SRCS))

$(info PROGS=$(PROGS))

all: $(PROGS)

%: %.c
	$(CC) -o $@ $^

# %.o: %c
# 	$(CC) -o $@ $<

.PHONY: clean

clean:
	rm $(PROGS)
