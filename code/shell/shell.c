#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void welcome(){
    printf("maybe this is a shell, who knows\n");
}

void help(){
    printf("come on, you got this\n");
}

void execute(char **args);

#define MAX_LINE 500

#define STR_EQUAL(s1, s2) strcmp(s1, s2)==0

#define pfatal(msg) do{perror(msg);exit(1);}while(0)

#define MAX_ARGS 10
void parseArgs(char *line, char**args, int max_args);

int main(int argc, char **argv){
    welcome();

    char line[MAX_LINE];
    char *result;
    while(1){
        printf("0rz>> ");

        if((result = fgets(line, MAX_LINE, stdin)) == NULL)
            printf("can't read shit");
        line[strlen(line)-1] = '\0';

        if(STR_EQUAL(line, "mamba out")){
            exit(0);
        }

        char **args = malloc(sizeof(char*) * MAX_ARGS);
        parseArgs(line, args, MAX_ARGS);
        execute(args);
    }
    return 0;
}

#define MAX_ARGS 10
void parseArgs(char *line, char**args, int max_args){
    char *str;
    int i=0;
    str = strtok(line, " ");
    while (str != NULL) {
        if(i >= max_args){
            pfatal("damn, so many args");
        }
        args[i++] = str;
        str = strtok(NULL, " ");
    }
}

void execute(char **args) {
    int pid = fork();
    if (pid < 0) {
        pfatal("fuck, no i mean fork!\n");
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            pfatal("damn, execvp failed");
        }
    } else {
        wait(NULL);
    }
}