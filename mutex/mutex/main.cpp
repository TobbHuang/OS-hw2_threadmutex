#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

int value=0;

int numOfThread=3;

void* ThreadRunner(void*){
    int k;
    for(k=0;k<10000000;k++){
        pthread_mutex_lock(&mutex);
        value++;
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    
    pthread_mutex_init(&mutex, NULL);
    
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
