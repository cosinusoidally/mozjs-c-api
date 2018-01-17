#include "mozjs-c.h"
int main(void){
  mjs_init();
  mjs_evaluate("'blah blah'+ 'hello'+'world, it is '+new Date()");
  mjs_evaluate("'woop blah'+ 'hello'+'world, it is '+Date.now()");
  mjs_evaluate("'ctypes object:'+ ctypes");
  mjs_shutdown();
  return 0;
}
