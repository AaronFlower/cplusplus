CXX = g++
CXXFLAGS = -std=c++17 -Wall -o3 -g -pthread
LDFLAGS  = -lpthread


EXECUTABLES = acc_thread_vs_async

all: ${EXECUTABLES}

acc_thread_vs_async: acc_thread_vs_async.cpp
	${CXX} ${CXXFLAGS} $^ -o $@ ${LDFLAGS}

clean:
	rm -f ${EXECUTABLES}
