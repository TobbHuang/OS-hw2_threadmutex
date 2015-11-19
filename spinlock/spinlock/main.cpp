#include <stdio.h>
#include <pthread.h>

pthread_spinlock_t spinlock;

int value=0;

int numOfThread=3;

void* ThreadRunner(void*){
    int k;
    for(k=0;k<10000000;k++){
        pthread_spin_lock(&spinlock);
        value++;
        pthread_spin_unlock(&spinlock);
    }
    return 0;
}

int main(int argc, const char * argv[]) {

    pthread_spin_init(&spinlock,0);

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
