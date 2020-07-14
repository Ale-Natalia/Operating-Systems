#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>

int main(int argc, char** argv){
        int nrplayers=6;
        srand(time(0));
        int start=rand()%nrplayers;
        printf("%d\n", start);
        int p[6][2], i;
        char letter = 'A';
        for(i=0; i<6; i++){
                pipe(p[i]);
        }
        for(i=0; i<nrplayers; i++){
                if(fork()==0){
                        int j, from, to;
                        if(i==0){
                                from=nrplayers-1; to=i;
                        }
                        else {
                                from=i-1; to=i;
                        }
                        for(j=0; j<nrplayers; j++){
                                if(j!=from)
                                        close(p[j][0]);
                                if(j!=to)
                                        close(p[j][1]);
                        }
                        //printf("Child %d reads from pipe %d and writes to pipe %d\n", i, from, to);
                        if(i == start){
                                write(p[to][1], &letter, sizeof(char));
                                printf("Child %d sent letter %c\n", i, letter);
                        }
                        while(1){
                                if(read(p[from][0], &letter, sizeof(char))<0){
                                        printf("Child %d no longer received a letter\n", i);
                                        break;
                                }
                                printf("Child %d received letter %c...", i, letter);
                                if(letter == 'Z'){
                                        printf("The game finishes at child %d because (s)he received letter Z\n", i);
                                        break;
                                }
                                letter += 1;
                                write(p[to][1], &letter, sizeof(char));
                                printf("Child %d sent letter %c\n", i, letter);
                        }
                        close(p[from][0]); close(p[to][1]);
                        printf("Child %d finished\n", i);
                        exit(0);
                }
        }
        for(i=0; i<nrplayers; i++)
                wait(0);
        return 0;
}