CPPFLAGS=-std=c++17
OPFLAGS=-O3

a.out: main.cpp
	g++ ${CPPFLAGS} ${OPFLAGS} -larmadillo -o $@ $^

.PHONY: clean

clean:
	rm a.out
