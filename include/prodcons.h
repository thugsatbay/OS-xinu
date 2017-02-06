#include <future.h>


extern int n;

//Function Prototypes For Assignment 2-3
void consumer(int count);
void producer(int count);
//Assignment 3 Semaphores
extern sid32 produced,consumed;

//Function Prototypes For Assignment 4
uint future_prod(future *fut);
uint future_cons(future *fut);
