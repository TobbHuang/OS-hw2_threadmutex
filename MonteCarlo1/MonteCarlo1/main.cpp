#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int num_of_thread=10;
int total_number_of_points=10000000;
int number_of_points_in_circle=0;

void* ThreadRunner(void*){
    int count=0;
    int total_number=total_number_of_points/num_of_thread;
    unsigned seed=(unsigned)time(NULL);
    while(1){
        if(total_number<=0){
            break;
        }
        
        total_number--;
        
        float num1=rand_r(&seed);
        num1 = num1 / (float)RAND_MAX * 2 - 1;
        float num2=rand_r(&seed);
        num2 = num2 / (float)RAND_MAX * 2 - 1;
        
        if(num1*num1+num2*num2<=1){
            count++;
        }
        
    }
    
    number_of_points_in_circle+=count;
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    if(argc<=1)
        return 0;
    
    total_number_of_points=atoi(argv[1]);
    
    pthread_t tid[10];
    int i;
    for(i=0;i<num_of_thread;i++){
        pthread_create(&tid[i], NULL, ThreadRunner, 0);
    }
    
    for(i=0;i<num_of_thread;i++){
        pthread_join(tid[i], NULL);
    }
    
    printf("%f\n",(float)number_of_points_in_circle/(total_number_of_points)*4);
    
    return 0;
}
