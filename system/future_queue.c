#include <xinu.h>
#include <future.h>

pid32 fdequeue(queue* q){
	intmask mask;
	mask = disable();
	pid32 retPID;
	if((queueLen(q)==0)){
		restore(mask);
		return EMPTY;
	}	
	queue *ptr=q;
	ptr=ptr->next;
	q=q->next=ptr->next;
	retPID=ptr->pid;
	queue_free(ptr);
	restore(mask);
	return retPID;
}


syscall fenqueue(pid32 pd,queue* q){
	intmask mask;
	mask = disable();
	if (isbadpid(pd)) {
		return SYSERR;
	}
	queue* ptr=queue_alloc();
	queue* move=q;
	while(move->next!=NULL){
		move=move->next;
	}
	move->next=ptr;
	ptr->prev=move;
	ptr->pid=pd;
	queue *ptr1=q;
	ptr1=ptr1->next;
	while(ptr1->next!=NULL){
		//printf("%d",ptr1->pid);
		ptr1=ptr1->next;
	}
	//printf("%d",ptr1->pid);
	//printf("\n");
	restore(mask);
	return OK;
}


int queueEmpty(queue* q){
	intmask mask;
	mask = disable();	
	if(q->next==NULL){
		return EMPTY;
	}
	restore(mask);
	return 0;
}         



int queueLen(queue* q){
	intmask mask;
	mask = disable();
	queue *ptr=q;
	int val=0;
	while(ptr->next!=NULL){
		ptr=ptr->next;
		++val;
	}
	restore(mask);
	return val;
}
