CC = g++

SRCS = $(wildcard *.cpp)

PROGS = $(patsubst %.cpp, %, $(SRCS))

all: $(PROGS)

%:%.cpp
	$(CC) -o $@ -std=c++11 $^

.PHONY:clean

clean:
	rm -rf $(PROGS)
