#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

int value=0;

void* ThreadRunner(void*){
    int k;
    for(k=0;k<1000000;k++){
        pthread_mutex_lock(&mutex);
        value++;
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    
    pthread_mutex_init(&mutex, NULL);
    
    pthread_t tid[3];
    int i;
    for(i=0;i<3;i++){
        pthread_create(&tid[i], NULL, ThreadRunner, 0);
    }
    
    for(i=0;i<3;i++){
        pthread_join(tid[i], NULL);
    }
    
    printf("%d\n",value);
    
    return 0;
}
