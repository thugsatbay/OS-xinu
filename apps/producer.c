#include <xinu.h>
#include <prodcons.h>

void producer(int32 count) {
	int32 i=0;
	for(i=1;i<=count;++i){
        
       // sleep(1);
        
        wait(consumed);
        n++;
		printf("Produced : %d\n",n);
        
        signal(produced);
	}
}
