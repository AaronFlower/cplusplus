# standard compile options for the c++ executable

FLAGS = -fPIC -std=c++11

# the python interface through swig
PYTHONI= -I/usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m

all:
	g++ ${FLAGS} -c lr.cpp utils.cpp
	swig -c++ -python -o lr_wrap.cpp lr.i
	g++ ${FLAGS} -c lr_wrap.cpp ${PYTHONI}
	ld -bundle -flat_namespace -undefined suppress -o _liblr.so *.o
