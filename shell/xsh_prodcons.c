#include <xinu.h>
#include <prodcons.h>
#include <future.h>

//Definition of gloabl variable and will be placed on heap so its accessible to
//all processes
int32 n;

//Assignment 3
sid32 produced,consumed;

shellcmd xsh_prodcons(int32 nargs,char *args[])
{
	//local variable to hold count
	int32 count=2000;
	int32 len=0;
	int32 loop=0;
	int32 result=0;

	if ((nargs==2) && ((strncmp(args[1],"--help",7)==0) || (strncmp(args[1],"-h",3)==0))){
		printf("This is a function in xinu that produces and consumes items entered by the user or default is 2000\n");
		return 0;
	}
	
	else if((nargs==2) && ((strncmp(args[1],"-f",3)==0))){
		future *f_exclusive, *f_shared, *f_queue;
 
		  f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
		  f_shared = future_alloc(FUTURE_SHARED);
		  f_queue = future_alloc(FUTURE_QUEUE);
		 
		// Test FUTURE_EXCLUSIVE
		  resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
		  resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
		
		// Test FUTURE_SHARED
		  resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
		  resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
		  resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
		  resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
		  resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );
		
		// Test FUTURE_QUEUE
		  resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
		  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		  resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
		  resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
  			resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
		return 0;
	}

	else if(nargs==2){
		char *command=args[1];
		len=strlen(args[1]);
		for(loop=0;loop<len;loop++){
			result=result*10+(command[loop]-'0');
		}
		count=result;
	}
	else if(nargs>2){
		printf("Too many arguments, try \"%s --help to get more information\n",args[0]);
		return 0;
	}

	//Assignment 3
	produced = semcreate(0);
	consumed = semcreate(1);

	//create the 2 processes producer and consumer
	n=0;
	resume(create(producer,1024,20,"producer",1,count));
	resume( create(consumer, 1024, 20, "consumer", 1, count));
	return 0;
}
