#include <stdio.h>
#include <pthread.h>
#include <spinlock.h>

pthread_spinlock_t spinlock;

int value=0;

void* ThreadRunner(void*){
    int k;
    for(k=0;k<10000;k++){
        value++;
        //printf("%d\n",value);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    
    
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
