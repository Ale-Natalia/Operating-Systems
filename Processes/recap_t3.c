#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//21:22-21:34
//     -21:44 until everything works


pthread_t tid[100];
pthread_mutex_t mutv = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutn = PTHREAD_MUTEX_INITIALIZER;
int n=0, v=0;


void* func(void* param){
        char* str = (char*)param;
        printf("%ld...> %s\n", pthread_self(), str);
        int i, len;
        char* vowels="aeiouAEIOU";
        char* digits = "1234567890";
        len = strlen(str);
        for(i=0; i<len; i++){
                if(strchr(vowels, str[i])!=0){
                        pthread_mutex_lock(&mutv);
                        v++;
                        pthread_mutex_unlock(&mutv);
                }
                if(strchr(digits, str[i])!=0){
                        pthread_mutex_lock(&mutn);
                        n++;
                        pthread_mutex_unlock(&mutn);
                }
        }
}

int main(int argc, char** argv){
        int i, nrt=0;
        char* str = malloc(sizeof(char));
        while(1){
                scanf("%s", str);
                printf("read string::: %s\n", str);
                if(strcmp(str, "stop") == 0){
                        break;
                }
                pthread_create(&tid[nrt], NULL, func, str);
                nrt++;
        }
        for(i=0; i<nrt;i++){
                pthread_join(tid[i], NULL);
        }
        printf("%d vowels, %d digits\n", v, n);
        return 0;
}