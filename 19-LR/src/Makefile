# standard compile options for the c++ executable

FLAGS = -fPIC -std=c++11

# the python interface through swig
# I installed python by homebrew in my mac, so the headers and lib
# in the /usr/local/Cellar/ directory.
PYTHONI= -I/usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m
PYTHONL= -L/usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/lib

all:
	g++ ${FLAGS} -c lr.cpp utils.cpp
	swig -c++ -python -o lr_wrap.cpp lr.i
	g++ ${FLAGS} -c lr_wrap.cpp ${PYTHONI}
	g++ -dynamiclib -lpython3.7 -larmadillo ${PYTHONL} *.o -o _LibLR.so
	python3 -c "import LibLR as lr; print(lr.__version__)"

.PHONY: clean, install, test

install:
	cp _LibLR.so ../python/
	cp LibLR.py ../python/

clean:
	rm -rf *.o *.py *.pyc lr_wrap.cpp _LibLR.so __pycache__

test:
	python3 -c "import LibLR as lr; print(lr.__version__)"
