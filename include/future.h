//#include <sys/types.h>
//#include <stdio.h>

#ifndef _FUTURE_H_
#define _FUTURE_H_
 

// define states 
#define FUTURE_EMPTY	  0
#define FUTURE_WAITING 	  1         
#define FUTURE_VALID 	  2         

//modes of operation for future
#define FUTURE_EXCLUSIVE  1
#define FUTURE_SHARED  2
#define FUTURE_QUEUE 3

typedef struct queneFut
{
	struct queneFut *prev;
	pid32 pid;
	struct queneFut *next;
}queue;


typedef struct futent
{
   int *value;		
   int flag;		
   int state;         	
   pid32 pid;
   queue get_queue;
   queue set_queue;
} future;

//Interface for system call
future* future_alloc(int future_flags);
syscall future_free(future*);
syscall future_get(future*, int*);
syscall future_set(future*, int*);
pid32 fdequeue(queue*);
syscall fenqueue(pid32,queue*);
syscall queue_free(queue*);
queue* queue_alloc();
int queueEmpty(queue*);
int queueLen(queue*);

 
#endif 
// _FUTURE_H_ 


//Function Prototypes For Assignment 4
//uint future_prod(future *fut)
//uint future_cons(future *fut)

