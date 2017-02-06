/* xsh_hello.c */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_hello - Print an Hello Message.
 *------------------------------------------------------------------------
 */

shellcmd xsh_hello(int nargs, char *args[]) {
	if (nargs==2){
		if((strncmp(args[1],"--help",7)==0)||(strncmp(args[1],"-h",3)==0)){
			printf("Welcome To Xinu!!! FALL2016 OS DJv1.0\n");
			printf("This is the most basic command that welcomes you to Xinu.\n");
			printf("Just type \"%s <Your Name>\" to allow Xinu To welcome you.\n",args[0]);
		}
		else{
			printf("Hello %s, Welcome to the world of Xinu!\n", args[1]);
		}
		return 0;
	}
	if (nargs == 1){
		printf("No Arguments Given! ERROR\n");	
		printf("Try \"%s --help\" to get more information how to use the command.\n",args[0]);
		return 0;
	}
	else{
		printf("Too many Arguments! ERROR\n");	
		printf("Try \"%s --help\" to get more information how to use the command.\n",args[0]); 
		return 0;
	}

}
