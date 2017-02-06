#include <xinu.h>
#include <future.h>

future* future_alloc(int future_flag){
	future *ret;
	intmask mask;
	mask=disable();
	ret=(char *)getmem(sizeof(future));
	if (ret==SYSERR){
		restore(mask);
		return NULL;
	}
	ret->set_queue.pid=EMPTY;
	ret->set_queue.next=NULL;
	ret->set_queue.prev=NULL;
	ret->get_queue.pid=EMPTY;
	ret->get_queue.next=NULL;
	ret->get_queue.prev=NULL;
	ret->state=FUTURE_EMPTY;
	ret->flag=future_flag;
	restore(mask);
	return ret;
}



queue* queue_alloc(){
	queue *ret;
	intmask mask;
	mask=disable();
	ret=(char *)getmem(sizeof(queue));
	if (ret==SYSERR){
		restore(mask);
		return NULL;
	}
	ret->prev=NULL;
	ret->next=NULL;
	restore(mask);
	return ret;
}

