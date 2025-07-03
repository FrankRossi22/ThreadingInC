#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ARRAY_SIZE 1000000
#define THREAD_NO 10

int sum = 0;

//create mutex lock
pthread_mutex_t mutex;

void *runner(void *param);
int main(){
    int num[THREAD_NO][ARRAY_SIZE/THREAD_NO];

    //Setup pthreads
    pthread_t tid[THREAD_NO];
    pthread_attr_t attr;

    //initialize attribute and set scope & sched
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setschedpolicy(&attr, SCHED_OTHER);


    srand(100);
    //initialize arrays
    for(int i=0; i< THREAD_NO; i++){
	for(int j=0; j< ARRAY_SIZE/THREAD_NO; j++){
            num[i][j] = rand() % 100;
	}
	//Create thread for each array
	pthread_create(&tid[i], &attr, runner, (void *)&num[i]);
    }

    //Join threads so sum is complete when it prints
    for(int i = 0; i < THREAD_NO; i++) {
	int *ret;
	pthread_join(tid[i],(void *) &ret);
    }

    printf("sum = %d\n", sum);
    
    return 0;


}

//Thread function to add sum of given param array to sum
void *runner(void *param) {
	int i;
	int j;
	int *arr = ((int*)param);
	int numLocks = 10;
	int chunkSize = (ARRAY_SIZE/THREAD_NO) / numLocks;
	//go through array in 10 chunks to reduce number of locks/unlocks from 10^6 -> 10^2
	//but increasing operations per lock from 1 -> 10,000
	for(j = 0; j < numLocks; j++) {
		int offset = (chunkSize * j);
		pthread_mutex_lock(&mutex);
		for(i = 0; i < chunkSize; i++) {
			sum += arr[i + offset];
		}
		pthread_mutex_unlock(&mutex);
	}
	int *count = 0;
	pthread_exit((void *)count);
}


