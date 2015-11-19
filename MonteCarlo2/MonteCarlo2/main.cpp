#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int numOfThread=10;
int total_number_of_points=1000000;
int number_of_points_in_circle=0;

pthread_mutex_t mutex;

void* ThreadRunner(void*){
    unsigned seed=(unsigned)time(NULL);
    while(1){
        pthread_mutex_lock(&mutex);
        if(total_number_of_points<=0){
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        total_number_of_points--;
        pthread_mutex_unlock(&mutex);
        
        float num1=rand_r(&seed);
        num1 = num1 / (float)RAND_MAX * 2 - 1;
        float num2=rand_r(&seed);
        num2 = num2 / (float)RAND_MAX * 2 - 1;
        
        if(num1*num1+num2*num2<=1){
            pthread_mutex_lock(&mutex);
            number_of_points_in_circle++;
			pthread_mutex_unlock(&mutex);
        }
        
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    if(argc<=1)
        return 0;
    
    total_number_of_points=atoi(argv[1]);
    
    int tmp=total_number_of_points;
    
    pthread_mutex_init(&mutex, NULL);
    
    pthread_t tid[numOfThread];
    int i;
    for(i=0;i<numOfThread;i++){
        pthread_create(&tid[i], NULL, ThreadRunner, 0);
    }
    
    for(i=0;i<numOfThread;i++){
        pthread_join(tid[i], NULL);
    }
    
    printf("%f\n",(float)number_of_points_in_circle/tmp*4);
    
    return 0;
}
