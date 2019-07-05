## SWIG tutorial for mac

### build

```bash
$ swig -python example.i
$ gcc -c example.c example_wrap.c -I/usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m
$ ld -bundle -flat_namespace -undefined suppress -o _example.so *.o
```

### test

```bash
❯ py
Python 3.7.3 (default, Jun 19 2019, 07:38:49)
[Clang 10.0.1 (clang-1001.0.46.4)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import example
>>> dir(example)
['_SwigNonDynamicMeta', '__builtin__', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', '_example', '_swig_add_metaclass', '_swig_getattr', '_swig_python_version_info', '_swig_repr', '_swig_setattr', '_swig_setattr_nondynamic', '_swig_setattr_nondynamic_class_variable', '_swig_setattr_nondynamic_instance_variable', 'cvar', 'fact', 'get_time', 'my_mod']
>>> example.fact(3)
6

```
