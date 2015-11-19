#include <stdio.h>
#include <pthread.h>

void homemade_spin_lock(int *spinlock_addr) {
    asm(
        "spin_lock: \n\t"
        "xorl %%ecx, %%ecx \n\t"
        "incl %%ecx \n\t"
        "spin_lock_retry: \n\t"
        "xorl %%eax, %%eax \n\t"
        "lock; cmpxchgl %%ecx, (%0) \n\t" "jnz spin_lock_retry \n\t"
        : : "r" (spinlock_addr) : "ecx", "eax" );
}
void homemade_spin_unlock(int *spinlock_addr) {
    asm(
        "spin_unlock: \n\t" "movl $0, (%0) \n\t"
        : : "r" (spinlock_addr) : );
}

int spinlock=0;

int value=0;

int numOfThread=3;

void* ThreadRunner(void*){
    int k;
    for(k=0;k<10000000;k++){
        homemade_spin_lock(&spinlock);
        value++;
        homemade_spin_unlock(&spinlock);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    
    pthread_t tid[3];
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

