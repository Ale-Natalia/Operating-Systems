#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//19:38 - 20:16
//apparently I didn't know to work with fifos very well

//program A

int main(int argc, char** argv){
        int n = 50;
        //close("/tmp/a2b", O_RDONLY);
        //close("/tmp/b2a", O_WRONLY);
        int fa2b = open("/tmp/manualfifo/a2b", O_WRONLY);
        int fb2a = open("/tmp/manualfifo/b2a", O_RDONLY);
        //dup2("/tmp/a2b", 1);
        //printf("%d", n);
        printf("A starts with %d\n", n);
        write(fa2b, &n, sizeof(int));
        while(1){
                if(read(fb2a, &n, sizeof(int))<=0)
                        break;
                n = n/2;
                printf("A: number %d\n", n);
                if(n/10 == 0)
                        break;
                write(fa2b, &n, sizeof(int));
        }
        close(fa2b);
        close(fb2a);
        return 0;
}