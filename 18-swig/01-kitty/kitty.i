#include <stdio.h>

class kitty {
 public:
  kitty();
  ~kitty();

  void speak();  
  void speak2(){ printf("totes works\n"); }

 private:
  int variable;

};
%module kitty
%{
  #include "kitty.h"
%}

%include "kitty.h"
