#include "mozjs-c.h"
int main(void){
  init();
  evaluate("'blah blah'+ 'hello'+'world, it is '+new Date()");
  evaluate("'woop blah'+ 'hello'+'world, it is '+Date.now()");
  quit_js();
  return 0;
}
