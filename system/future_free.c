#include <xinu.h>
#include <future.h>

syscall future_free(future *f){
	return freemem((char *)f,sizeof(future));
}


syscall queue_free(queue* q){
	return freemem((char *)q,sizeof(queue));
}