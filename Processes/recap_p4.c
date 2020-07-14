#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//19:06 - 19:26
//      - 19:35 until it fully works :')

int main(int argc, char** argv){
        int p2c[2], c2p[2];
        pipe(p2c);
        pipe(c2p);
        if(fork() == 0){
                close(p2c[1]);
                close(c2p[0]);
                while(1){
                        char strc[15];
                        int lenc;
                        if(read(p2c[0], &lenc, sizeof(int))<=0)
                                break;
                        if(read(p2c[0], strc, sizeof(char)*lenc)<=0)
                                break;
                        //strc[lenc-1] = NULL;
                        printf("Child received %s\n", strc);
                        strcpy(strc, strc+1);
                        lenc -=1;
                        printf("Child created %s\n", strc);
                        if(lenc-1 <= 3)
                                break;
                        write(c2p[1], &lenc, sizeof(int));
                        write(c2p[1], strc, sizeof(char)*lenc);
                }
                close(p2c[0]);
                close(c2p[1]);
                exit(0);
        }
        char str[15];
        close(p2c[0]);
        close(c2p[1]);
        scanf("%s", str);
        int len;
        len =strlen(str)+1;
        write(p2c[1], &len, sizeof(int));
        write(p2c[1], str, sizeof(char)*len);
        while(1){
                if(read(c2p[0], &len, sizeof(int))<=0)
                                break;
                if(read(c2p[0], str, sizeof(char)*len)<=0)
                                break;
                str[len-2] = NULL;
                len -=1;
                printf("Parent created %s\n", str);
                if(len-1 <=3)
                                break;
                write(p2c[1], &len, sizeof(int));
                write(p2c[1], str, sizeof(char)*len);
        }
        close(p2c[1]);
        close(c2p[0]);
        //printf("%s\n", str);
        wait(0);
        return 0;
}