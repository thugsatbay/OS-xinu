#include <xinu.h>
#include <future.h>

syscall future_get(future *f, int *value){
intmask mask;
mask = disable();
f->pid = getpid();


	if(f->flag == FUTURE_EXCLUSIVE){
		if(f->state == FUTURE_VALID){
		    	*value = *(f->value);
		    	restore(mask);
    			return OK;
  		}

  		if(f->state == FUTURE_EMPTY){
		    	f->state = FUTURE_WAITING;
		    	f->pid = getpid();
		    	suspend(f->pid);
		    	*value = *(f->value);
		    	restore(mask);
		    	return OK;
  		}
	}


	if(f->flag==FUTURE_SHARED){
		if(f->state == FUTURE_VALID){
			*value = *(f->value);
			f->state = FUTURE_EMPTY;
			restore(mask);
			return OK;
		}
		
		if(f->state == FUTURE_EMPTY){
			f->state = FUTURE_WAITING;
			fenqueue(f->pid,&f->get_queue);
			//printf("PID%d\n",f->pid);
			//printf("Length Of Queue %d\n",queueLen(&f->get_queue));
			suspend(f->pid);
			*value = *(f->value);
			restore(mask);
			return OK;
		}


		if(f->state==FUTURE_WAITING){
			fenqueue(f->pid,&f->get_queue);
			//printf("PID%d\n",f->pid);
			//printf("Length Of Queue %d\n",queueLen(&f->get_queue));
			suspend(f->pid);
			*value = *(f->value);
			restore(mask);
			return OK;
		}
		
		restore(mask);
	  	return SYSERR;
	}




	if(f->flag==FUTURE_QUEUE){
		if(f->state == FUTURE_VALID){
			f->pid=getpid();
			resume(fdequeue(&f->set_queue));
			suspend(f->pid);
			*value = *(f->value);
			if((queueEmpty(&f->get_queue)==EMPTY)&&(queueEmpty(&f->set_queue)==EMPTY))
				f->state = FUTURE_EMPTY;
			restore(mask);
			return OK;
		}
		
		if(f->state == FUTURE_EMPTY){
			f->state = FUTURE_WAITING;
			fenqueue(getpid(),&f->get_queue);
			suspend(getpid());
			*value = *(f->value);
			if(queueEmpty(&f->get_queue)==EMPTY){
				f->state=FUTURE_EMPTY;
			}
			//resume(f->pid);
			restore(mask);
			return OK;
		}


		if(f->state==FUTURE_WAITING){
			fenqueue(getpid(),&f->get_queue);
			suspend(getpid());
			*value = *(f->value);
			if(queueEmpty(&f->get_queue)==EMPTY){
				f->state=FUTURE_EMPTY;
			}
			//resume(f->pid);
			restore(mask);
			return OK;
		}
		
		restore(mask);
	  	return SYSERR;
	}


restore(mask);
return SYSERR;

}
