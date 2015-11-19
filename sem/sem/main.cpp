#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int numOfThread=3;

sem_t sem;

int value=0;

void* ThreadRunner(void*){
    int k;
    for(k=0;k<10000000;k++){
        sem_wait(&sem);
        value++;
        sem_post(&sem);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    
    sem_init(&sem, 0, 1);
    
    pthread_t tid[numOfThread];
    int i;
    for(i=0;i<numOfThread;i++){
        pthread_create(&tid[i], NULL, ThreadRunner, 0);
    }
    
    for(i=0;i<numOfThread;i++){
        pthread_join(tid[i], NULL);
    }
    
    printf("%d\n",value);
    
    return 0;
}
