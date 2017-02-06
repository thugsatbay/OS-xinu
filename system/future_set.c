#include <xinu.h>
#include <future.h>

syscall future_set(future *f, int *value){
intmask mask;
mask = disable();


	if (f->flag == FUTURE_EXCLUSIVE){
		if(f->state == FUTURE_EMPTY){

			f->value = value;
			f->state = FUTURE_VALID;
			restore(mask);
			return OK;

		}

		if(f->state == FUTURE_WAITING){
			f->state = FUTURE_VALID;
			f->value=value;
			resume(f->pid);
			restore(mask);
			return OK;
		}
	}




if (f->flag==FUTURE_SHARED){
	if(queueEmpty(&f->set_queue)==EMPTY){	
		if(f->state == FUTURE_EMPTY){
			f->value = value;
			f->state = FUTURE_VALID;
			fenqueue(getpid(),&f->set_queue);
			f->pid=getpid();
			restore(mask);    
			return OK;
		}
			
		if(f->state == FUTURE_WAITING){
			f->state = FUTURE_VALID;
			f->value=value;
			fenqueue(getpid(),&f->set_queue);	
			pid32 temp=fdequeue(&f->get_queue);		
			while(temp!=EMPTY){
				resume(temp);
				temp=fdequeue(&f->get_queue);
			}
			restore(mask);
			return OK;
		}
			  restore(mask);
		  	  return SYSERR;
	}
	else{
		restore(mask);
		return SYSERR;
	}
	
}



if (f->flag==FUTURE_QUEUE){
		

		if(f->state == FUTURE_VALID){
			fenqueue(getpid(),&f->set_queue);
			suspend(getpid());
			f->value = value;
			resume(f->pid);
			if(queueEmpty(&f->set_queue)==EMPTY){
				f->state=FUTURE_EMPTY;
			}
			restore(mask);    
			return OK;
		}


		if(f->state == FUTURE_EMPTY){
			fenqueue(getpid(),&f->set_queue);
			f->state = FUTURE_VALID;
			suspend(getpid());
			f->value = value;
			resume(f->pid);
			if(queueEmpty(&f->set_queue)==EMPTY){
				f->state=FUTURE_EMPTY;
			}
			restore(mask);    
			return OK;
		}
			
		if(f->state == FUTURE_WAITING){
			f->value=value;
			//f->pid=getpid();
			resume(fdequeue(&f->get_queue));
			//suspend(f->pid);
			if((queueEmpty(&f->get_queue)==EMPTY)&&(queueEmpty(&f->set_queue)==EMPTY))
				f->state = FUTURE_EMPTY;
			restore(mask);
			return OK;
		}
			  restore(mask);
		  	  return SYSERR;
}

}
