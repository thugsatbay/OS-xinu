
#include <xinu.h>
#include <prodcons.h>

void consumer(int32 count) {
	
    // Assignment 2
    /*while(n <= count){
     printf("Consumed : %d\n", n);
     if(n == count){
        break;
     }
    }*/

    //Assignment 3
    while(n <= count){
      // sleep(1);
        
        wait(produced);
        
        printf("consumed : %d\n", n);
        
        if(n == count){
            break;
        }
        
        signal(consumed);
        
    }		    
    semdelete(produced);
    semdelete(consumed);
}
