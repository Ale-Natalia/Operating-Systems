#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
        int i, pid;
        int p[argc][2];
        char word[20];
        int len=20;
        int vowels=0;
        char len_char[20];

        for(i=1; i<argc; i++){
                pipe(p[i]);
                pid = fork();
                if(pid==0){
                        close(p[i][0]);
                        dup2(p[i][1], 1);
                        len=strlen(argv[i])+1;
                        write(p[i][1], &len, sizeof(int));//write the length
                        write(p[i][1], argv[i], len); //write the word
                        execl("./vowels.sh", "./vowels.sh",  argv[i], NULL);//the number of vowels is written to the pipe
                        printf("Error\n");
                        exit(1);
                }
                else
                        printf("Parent launched child %d > %s \n", pid, argv[i]);
        }
        for(i=1; i<argc; i++){
                close(p[i][1]);
                read(p[i][0], &len, sizeof(int));//read the length of the word
                read(p[i][0], word, len);//read the word
                //printf("word %s\n", word);
                word[len-1]='\0';
                read(p[i][0], &len_char, sizeof(char)*2);//read the number of vowels as a char string
                len=atoi(len_char); //turn the number of vowels into an integer
                printf("Word %s has %d vowels\n", word, len);
                close(p[i][0]);
        }
        for(i=1; i<argc; i++)
                wait(0);
        return 0;
}
                       