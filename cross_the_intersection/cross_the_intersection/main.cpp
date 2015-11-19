#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int car[4];
int lock[4];
int isDeadlock[4];
int isFinish[4];
float timer=0.9;
float p=0.25;

pthread_mutex_t mutex;

void* ThreadRunnerN(void*){
    int i=0;
    while(i<car[0]){
        while(1){
            // first lock
            pthread_mutex_lock(&mutex);
            timer+=p;
            if(!lock[0]){
                lock[0]=1;
                pthread_mutex_unlock(&mutex);
                break;
            }
            pthread_mutex_unlock(&mutex);
            sleep(1);
        }
        
        while(1){
            // second lock
            sleep(1);
            
            pthread_mutex_lock(&mutex);
            timer+=p;
            if(!lock[2]){
                isDeadlock[0]=0;
                lock[2]=1;
                pthread_mutex_unlock(&mutex);
                break;
            } else{
                // 申请锁失败，用于检测死锁
                isDeadlock[0]=1;
                
                // 死锁啦
                if(isDeadlock[0]&&isDeadlock[1]&&isDeadlock[2]&&isDeadlock[3]){
                    pthread_mutex_unlock(&mutex);
                    break;
                }
                
            }
            pthread_mutex_unlock(&mutex);
        }
        // 死锁后释放资源
        if(isDeadlock[0]&&isDeadlock[1]&&isDeadlock[2]&&isDeadlock[3]){
            printf("A DEADLOCK HAPPENS at %d\n",(int)timer);
            lock[0]=0;
            isDeadlock[0]=0;
            sleep(1);
            continue;
        }
        
        // 过马路
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer+=p;
        pthread_mutex_unlock(&mutex);
        printf("N %d leaves at %d\n",i,(int)timer);
        i++;
        
        // release lock
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer+=p;
        lock[0]=0;
        lock[2]=0;
        pthread_mutex_unlock(&mutex);
        
        sleep(1);
        
    }
    
    isFinish[0]=1;
    
    // 计数器要继续运转…
    while(1){
        pthread_mutex_lock(&mutex);
        timer+=p;
        pthread_mutex_unlock(&mutex);
        if(isFinish[0]&&isFinish[1]&&isFinish[2]&&isFinish[3]){
            break;
        }
        sleep(1);
    }
    
    return 0;
}

void* ThreadRunnerE(void*){
    int i=0;
    while(i<car[1]){
        while(1){
            // first lock
            pthread_mutex_lock(&mutex);
            timer+=p;
            if(!lock[1]){
                lock[1]=1;
                pthread_mutex_unlock(&mutex);
                break;
            }
            pthread_mutex_unlock(&mutex);
            sleep(1);
        }
        
        
        
        while(1){
            // second lock
            sleep(1);
            
            pthread_mutex_lock(&mutex);
            timer+=p;
            if(!lock[0]){
                isDeadlock[1]=0;
                lock[0]=1;
                pthread_mutex_unlock(&mutex);
                break;
            } else{
                // 申请锁失败，用于检测死锁
                isDeadlock[1]=1;
                
                // 死锁啦
                if(isDeadlock[0]&&isDeadlock[1]&&isDeadlock[2]&&isDeadlock[3]){
                    pthread_mutex_unlock(&mutex);
                    break;
                }
                
            }
            pthread_mutex_unlock(&mutex);
        }
        // 死锁后释放资源
        if(isDeadlock[0]&&isDeadlock[1]&&isDeadlock[2]&&isDeadlock[3]){
            printf("A DEADLOCK HAPPENS at %d\n",(int)timer);
            lock[1]=0;
            isDeadlock[1]=0;
            sleep(1);
            continue;
        }
        
        // 过马路
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer+=p;
        pthread_mutex_unlock(&mutex);
        printf("E %d leaves at %d\n",i,(int)timer);
        i++;
        
        // release lock
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer+=p;
        lock[0]=0;
        lock[1]=0;
        pthread_mutex_unlock(&mutex);
        
        
        sleep(1);
        
    }
    
    isFinish[1]=1;
    
    // 计数器要继续运转…
    while(1){
        pthread_mutex_lock(&mutex);
        timer+=p;
        pthread_mutex_unlock(&mutex);
        if(isFinish[0]&&isFinish[1]&&isFinish[2]&&isFinish[3]){
            break;
        }
        sleep(1);
    }
    
    return 0;
}

void* ThreadRunnerS(void*){
    int i=0;
    while(i<car[2]){
        while(1){
            // first lock
            pthread_mutex_lock(&mutex);
            timer+=p;
            if(!lock[3]){
                lock[3]=1;
                pthread_mutex_unlock(&mutex);
                break;
            }
            pthread_mutex_unlock(&mutex);
            sleep(1);
        }
        
        
        
        while(1){
            // second lock
            sleep(1);
            
            pthread_mutex_lock(&mutex);
            timer+=p;
            if(!lock[1]){
                isDeadlock[2]=0;
                lock[1]=1;
                pthread_mutex_unlock(&mutex);
                break;
            } else{
                // 申请锁失败，用于检测死锁
                isDeadlock[2]=1;
                
                // 死锁啦
                if(isDeadlock[0]&&isDeadlock[1]&&isDeadlock[2]&&isDeadlock[3]){
                    pthread_mutex_unlock(&mutex);
                    break;
                }
                
            }
            pthread_mutex_unlock(&mutex);
        }
        // 死锁后释放资源
        if(isDeadlock[0]&&isDeadlock[1]&&isDeadlock[2]&&isDeadlock[3]){
            printf("A DEADLOCK HAPPENS at %d\n",(int)timer);
            lock[3]=0;
            isDeadlock[2]=0;
            sleep(1);
            continue;
        }
        
        // 过马路
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer+=p;
        pthread_mutex_unlock(&mutex);
        printf("S %d leaves at %d\n",i,(int)timer);
        i++;
        
        // release lock
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer+=p;
        lock[1]=0;
        lock[3]=0;
        pthread_mutex_unlock(&mutex);
        
        sleep(1);
        
    }
    
    isFinish[2]=1;
    
    // 计数器要继续运转…
    while(1){
        pthread_mutex_lock(&mutex);
        timer+=p;
        pthread_mutex_unlock(&mutex);
        if(isFinish[0]&&isFinish[1]&&isFinish[2]&&isFinish[3]){
            break;
        }
        sleep(1);
    }
    
    return 0;
}

void* ThreadRunnerW(void*){
    int i=0;
    while(i<car[3]){
        while(1){
            // first lock
            pthread_mutex_lock(&mutex);
            timer+=p;
            if(!lock[2]){
                lock[2]=1;
                pthread_mutex_unlock(&mutex);
                break;
            }
            pthread_mutex_unlock(&mutex);
            sleep(1);
        }
        
        
        
        while(1){
            // second lock
            sleep(1);
            
            
            pthread_mutex_lock(&mutex);
            timer+=p;
            if(!lock[3]){
                isDeadlock[3]=0;
                lock[3]=1;
                pthread_mutex_unlock(&mutex);
                break;
            } else{
                // 申请锁失败，用于检测死锁
                isDeadlock[3]=1;
                
                // 死锁啦
                if(isDeadlock[0]&&isDeadlock[1]&&isDeadlock[2]&&isDeadlock[3]){
                    pthread_mutex_unlock(&mutex);
                    break;
                }
                
            }
            pthread_mutex_unlock(&mutex);
        }
        // 死锁后释放资源
        if(isDeadlock[0]&&isDeadlock[1]&&isDeadlock[2]&&isDeadlock[3]){
            printf("A DEADLOCK HAPPENS at %d\n",(int)timer);
            lock[2]=0;
            isDeadlock[3]=0;
            sleep(1);
            continue;
        }
        
        // 过马路
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer+=p;
        pthread_mutex_unlock(&mutex);
        printf("W %d leaves at %d\n",i,(int)timer);
        i++;
        
        // release lock
        sleep(1);
        pthread_mutex_lock(&mutex);
        timer+=p;
        lock[2]=0;
        lock[3]=0;
        pthread_mutex_unlock(&mutex);
        
        
        sleep(1);
        
    }
    
    isFinish[3]=1;
    
    // 计数器要继续运转…
    while(1){
        pthread_mutex_lock(&mutex);
        timer+=p;
        pthread_mutex_unlock(&mutex);
        if(isFinish[0]&&isFinish[1]&&isFinish[2]&&isFinish[3]){
            break;
        }
        sleep(1);
    }
    
    return 0;
}


int main(int argc, const char * argv[]) {
    
    if(argc<5)
        return 0;
    
    car[0]=atoi(argv[1]);
    car[1]=atoi(argv[2]);
    car[2]=atoi(argv[3]);
    car[3]=atoi(argv[4]);
    
    int i;
    for(i=0;i<4;i++){
        lock[i]=0;
        isDeadlock[i]=0;
        if(car[i]==0){
            isFinish[i]=1;
        } else{
            isFinish[i]=0;
        }
    }
    
    pthread_mutex_init(&mutex, NULL);
    
    pthread_t tid[4];
    pthread_create(&tid[0], NULL, ThreadRunnerW, 0);
    pthread_create(&tid[1], NULL, ThreadRunnerE, 0);
    pthread_create(&tid[2], NULL, ThreadRunnerS, 0);
    pthread_create(&tid[3], NULL, ThreadRunnerN, 0);
    
    for(i=0;i<4;i++)
        pthread_join(tid[i], NULL);
    
    
    return 0;
}
