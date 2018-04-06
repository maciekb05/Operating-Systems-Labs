#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------

void *PrintHello(void *arg);
// ----------------------------------------------------------

int main(int argc, char *argv[]){
	for(int i = 0; i < 10; i++){
		pthread_t thread;
		int rc = pthread_create(&thread, NULL, PrintHello, &i);
		if (rc){
		     printf("Return code: %d\n", rc);
		     exit(-1);
		}
		sleep(1);
	}
     
    return 0;
}
// ----------------------------------------------------------

void *PrintHello(void *arg){
     printf("%d boring 'Hello World!' version!\n", *((int*)arg));
     return NULL;
}
