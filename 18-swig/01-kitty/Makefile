# standard compile options for the c++ executable
FLAGS = -fPIC

# the python interface through swig
PYTHONI = -I/usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m

# default super-target
all:
	g++ -fPIC -c kitty.cpp -o kitty.o
	swig -c++ -python -o kitty_wrap.cxx kitty.i
	g++ $(FLAGS) $(PYTHONI) -c kitty_wrap.cxx -o kitty_wrap.o
	ld -bundle -flat_namespace -undefined suppress -o _kitty.so *.o
