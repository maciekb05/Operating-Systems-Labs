#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------

#define MAXVAL 10

int globalvariable = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* increment(void*);
void* printinfo(void*);
// ----------------------------------------------------------

int main(){

     pthread_t t1, t2, t3;
     pthread_attr_t attr;

     // mutex initialization
     pthread_mutex_init(&mutex, NULL);

     // conditional initialization
     pthread_cond_init(&cond, NULL);

     pthread_attr_init(&attr);
     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int i = 1;
	int j = 2;
     pthread_create(&t1, &attr, increment, &i); 
     pthread_create(&t2, &attr, increment, &j);
     pthread_create(&t3, &attr, printinfo, NULL);  

     
     pthread_join(t3, NULL);
     printf("t3 finished!\n");
     pthread_cancel(t1);
     printf("t1 finished!\n");
     pthread_cancel(t2);
     printf("t2 finished!\n");


     printf("Finishing...\n");
     return 0;
}
// ----------------------------------------------------------

void* increment(void* arg) {
	while(1==1){
		pthread_mutex_lock(&mutex);
		globalvariable++;
		printf("GlobalVar: %d, ktory watek inkrementowal: %d\n",globalvariable,*((int *)arg));
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
     pthread_exit((void*) 0);
}
// ----------------------------------------------------------

void* printinfo(void* arg) {
	pthread_mutex_lock(&mutex)==0;
	while(globalvariable < MAXVAL){
		pthread_cond_wait(&cond,&mutex);
	}
	printf("Osiagnieto MAXVALUE\n");
	pthread_mutex_unlock(&mutex);
     pthread_exit((void*) 0);
}
// ----------------------------------------------------------
