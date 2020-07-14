#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t tid[100];
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut5 = PTHREAD_MUTEX_INITIALIZER;
int v2 = 0, v5 = 0;
//20:19-20:31
//     -20:35 until it actually works properly

void* func(){
        int nr = rand();
        if(nr % 2 == 0){
                pthread_mutex_lock(&mut2);
                v2++;
                pthread_mutex_unlock(&mut2);
        }
        if(nr % 5 == 0){
                pthread_mutex_lock(&mut5);
                v5++;
                pthread_mutex_unlock(&mut5);
        }
        printf("%ld generated %d\n", pthread_self(), nr);
}

int main(int argc, char** argv){
        int i, j;
        for(i = 0; i<4; i++){
                for(j=0; j<5; j++)
                        pthread_create(&tid[i], NULL, func, NULL);
        }
        for(i = 0; i<4; i++){
                for(j=0; j<5; j++)
                pthread_join(tid[i], NULL);
        }
        printf("v2=%d, v5=%d\n", v2, v5);
        return 0;
}