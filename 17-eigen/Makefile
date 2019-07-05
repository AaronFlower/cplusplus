CPPFLAGS=-std=c++17

a.out: main.cpp
	g++ ${CPPFLAGS} -o $@ $^

# .PHONY: config
# 	ln -s -f ~/code/cpp/eigen-3.3.7/Eigen Eigen

.PHONY: clean, config

config:
	ln -s -f ~/code/cpp/eigen-3.3.7/Eigen Eigen

clean:
	rm a.out
