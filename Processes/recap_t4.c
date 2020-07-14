#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

//21:48-21:57

pthread_t tid[100];
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut5 = PTHREAD_MUTEX_INITIALIZER;
int v2=0, v5=0;

void* func(void* attr){
        int nr = *(int*)attr;
        if(nr%5 == 0){
                pthread_mutex_lock(&mut5);
                v5++;
                pthread_mutex_unlock(&mut5);
        }
        if(nr%2 == 0){
                pthread_mutex_lock(&mut2);
                v2++;
                pthread_mutex_unlock(&mut2);
        }
}

int main(int argc, char** argv){
        int i;
        for(i=1; i<argc; i++){
                int nr = *argv[i];
                pthread_create(&tid[i], NULL, func, (void*)&nr);
        }
        for(i=1; i<argc; i++){
                pthread_join(tid[i], NULL);
        }
        printf("v2=%d, v5=%d\n", v2, v5);
        return 0;
}