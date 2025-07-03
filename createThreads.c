#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREAD_NO 10

void *mythread(void *arg) {
    int id =  *(int *)arg;
    printf("my id is %d\n", id);
    return arg;
}

int main(){
    pthread_t p[THREAD_NO];
    int i = 0;
    for(i=0; i<THREAD_NO; i++){
	//allocate space for thread variable
	int *var = malloc(sizeof(int));
	*var = (int)i;
        pthread_create(&p[i], NULL, mythread, var);
    }

    for(i=0; i<THREAD_NO; i++){
	//get thread variable returned so it can be freed
	int *ret;
	pthread_join(p[i], (void *)&ret);
	free(ret);
    }
    return 0;
}
