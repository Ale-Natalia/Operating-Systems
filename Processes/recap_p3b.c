#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>                                                                                      //19:38
//program B
int main(int argc, char** argv){
        int n;
        //close("/tmp/a2b", O_RDONLY);
        //close("/tmp/b2a", O_WRONLY);
        int fa2b = open("/tmp/manualfifo/a2b", O_RDONLY);
        int fb2a = open("/tmp/manualfifo/b2a", O_WRONLY);
        //dup2("/tmp/a2b", 1);
        //printf("%d", n);
        //write(fa2b, &n, sizeof(int));
        while(1){
                if(read(fa2b, &n, sizeof(int))<=0)
                        break;
                n = n - 3;
                printf("B number %d\n", n);
                if(n/10 == 0)
                        break;
                write(fb2a, &n, sizeof(int));
        }
        close(fa2b);
        close(fb2a);
        return 0;
}