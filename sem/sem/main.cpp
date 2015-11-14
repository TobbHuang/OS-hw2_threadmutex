#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

int value=0;

void* ThreadRunner(void*){
    int k;
    for(k=0;k<10000;k++){
        sem_wait(&sem);
        value++;
        //printf("%d\n",value);
        sem_post(&sem);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    
    printf("%d\n",sem_init(&sem, 0, 1));
    
    pthread_t tid[3];
    int i;
    for(i=0;i<3;i++){
        pthread_create(&tid[i], NULL, ThreadRunner, 0);
    }
    
    for(i=0;i<3;i++){
        pthread_join(tid[i], NULL);
    }
    
    printf("end:%d\n",value);
    
    return 0;
}
