CXX = g++
CXXFLAGS = -Wall -o3 -g -std=c++17 -pthread
LDFLAGS  = -lpthread

all: main

main: main.cpp task.h scheduler.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f main
