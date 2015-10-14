#include <future.h>
#include <stddef.h>
#include <stdio.h>
#include <kernel.h>

  /*Global variable for producer consumer*/
  extern int n; /*this is just declaration*/
  extern sid32 produced, consumed;

  /*function Prototype*/
  void consumer();
  void producer();
  
  /*function Prototype for future producer and consumer*/
  uint future_prod(future *fut);
  uint future_cons(future *fut);


