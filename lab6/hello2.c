#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------

void *PrintHello(void *arg);
// ----------------------------------------------------------

int main(int argc, char *argv[]){
	pthread_t thread[10];
	int tid[10];
	for(int i = 0; i < 10; i++){
		tid[i] = i;
		int rc = pthread_create(&thread[i], NULL, PrintHello, &tid[i]);
		if (rc){
		     printf("Return code: %d\n", rc);
		     exit(-1);
		}
		//sleep(1);
	}
     for(int i = 0; i < 10; i++){
     	int rv = pthread_join(thread[i],NULL);
	 if (rv){
	      printf("Return code: %d\n", rv);
	      exit(-1);
	 }
     }
     printf("End of the main thread!\n");
     return 0;
}
// ----------------------------------------------------------

void *PrintHello(void *arg){
	sleep(1);
    printf("%d Next boring 'Hello World!' version!\n",*((int*)arg));
    return NULL;
}
