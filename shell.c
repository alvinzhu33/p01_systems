#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "headers.h"

#define WHT "\x1B[0m"
#define BLU "\x1B[36m"
#define PUR "\x1B[35m"


void execute(char* in){
    strtok(in,"\n");
    char *commands[50];
    char *inputStr = in;

    int comCount = 0;
    while (commands[comCount] = strsep(&inputStr,";")) {
        comCount++;
    }

    int counter = 0;
    int forker;
    int index;
    for (counter; counter < comCount; counter++) {
        if (!strcmp(stripper(commands[counter]),"exit")) {
            exit(0);
        }
        forker = fork();
        if (forker == 0) {
            char *exeCom[50];
            char *comStr = stripper(commands[counter]);

            int wordCount = 0;
            int outChange = 0;
            int inChange = 0;
            int pipeTrue = 0;
            while (comStr && !inChange && !outChange && !pipeTrue) {
                char *part = strsep(&comStr," ");
                if (strcmp(part,">") != 0 && strcmp(part,"<") != 0 && strcmp(part,"|") != 0) {
                    exeCom[wordCount] = part;
                    wordCount++;
                }
                if (strcmp(part,">") == 0) {
                    outChange = 1;
                }
                if (strcmp(part,"<") == 0) {
                    inChange = 1;
                }
                if (strcmp(part,"|") == 0) {
                    pipeTrue = 1;
                }
            }
            exeCom[wordCount] = 0;

            if (outChange) {
                changeOutput(exeCom,comStr);
            }
            else if (inChange) {
                changeInput(exeCom,comStr);
            }
            else if (pipeTrue) {
                piper(exeCom, comStr);
            }
            else if (strcmp(exeCom[0],"cd") == 0) {
                chdir(exeCom[1]);
            }
            else {
                if (execvp(exeCom[0],exeCom) == -1) {
                    if (!strcmp(exeCom[0],"unicorn") || !strcmp(exeCom[0], "pegasus") || !strcmp(exeCom[0], "magic") || !strcmp(exeCom[0], "pretty")){
                        printf("               |))    |))\n .             |  )) /   ))\n \\   ^ ^      |    /      ))\n  \\(((  )))   |   /        ))\n   / G    )))  |  /        ))\n  |o  _)   ))) | /       )))\n   --' |     ))`/      )))\n    ___|              )))\n   / __\\             ))))`()))\n  /\\@   /             `(())))\n  \\/   /  /`_______/\\   \\  ))))\n       | |          \\ \\  |  )))\n       | |           | | |   )))\n       |_@           |_|_@    ))\n      /_/           /_/_/\n");
                    } else {
                        printf("%s: command not found\n",exeCom[0]);
                    }
                }
                raise(15);
            }
        }
        else {
            int status,r;
            r = wait(&status);
        }
    }
}


char* stripper(char* stripping){
    while(stripping[0] == ' '){
        *stripping++;
    }
    while(stripping[strlen(stripping)-1] == ' '){
        stripping[strlen(stripping)-1] = 0;
    }
    int counter = 0;
    int length = strlen(stripping)-1;
    for(counter; counter<length; counter++){
        if(stripping[counter] == ' ' && stripping[counter+1]==' '){
            int changer = counter;
            while(changer<length){
                stripping[changer]=stripping[changer+1];
                changer++;
            }
            counter--;
            stripping[length]=0;
            length--;
        }
    }

    char *stripped = stripping;
    return stripped;
}


void changeOutput(char *s[], char *f) {
    umask(000);
    remove(f);
    int fd = open(f,O_CREAT | O_RDWR, 0644);
    int copy = dup(1);
    dup2(fd,1);
    //the output turns into fd
    close(fd);
    if (execvp(s[0],s) == -1) {
        dup2(copy,1);
        printf("%s: command not found\n",s[0]);
        remove(f);
    }
    raise(15);
}


void changeInput(char *s[],char *f) {
    umask(000);
    int fd = open(f,O_CREAT | O_RDWR, 0644);
    dup2(fd,0);
    //the input turns into fd
    close(fd);
    if (execvp(s[0],s) == -1) {
        printf("%s: command not found\n",s[0]);
    }
    raise(15);
}


void piper(char *s[], char *f){
    char *command2[50];

    int wordCount = 0;
    while (command2[wordCount] = strsep(&f," ")) {
        wordCount++;
    }

    int child;

    child = fork();

    if (child == 0) {
        changeOutput(s,"Tunnel");
    }
    else {
        int status,c2;
        wait(&status);
        c2 = fork();
        if (c2 == 0) {
            changeInput(command2,"Tunnel");
        }
        else {
            int status;
            wait(&status);
            remove("Tunnel");
        }
    }
}


int main() {
    while (1) {
        char s1[256];
        char cwd[256];
        getcwd(cwd, sizeof(cwd));

        printf(BLU"%s"WHT"$ ", cwd);
        fgets(s1,sizeof(s1),stdin);
        execute(s1);
    }
    return 0;
}
