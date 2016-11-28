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

//STILL NEED PIPING AND REDIRECTION
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
    if (strcmp(commands[counter]," exit ") == 0) {
      exit(0);
    }
    forker = fork();
    if (forker == 0) {
      char *exeCom[50];
      char *comStr = commands[counter];
      if (counter != 0) {
	comStr++;
      }
      if (comStr[strlen(comStr)-1] == ' ') {
	comStr[strlen(comStr)-1] = 0;
      }

      int wordCount = 0;
      while (exeCom[wordCount] = strsep(&comStr," ")) {
	wordCount++;
      }
      exeCom[wordCount] = 0;
      if (strcmp(exeCom[0],"cd") == 0) {
	chdir(exeCom[1]);
      }
      execvp(exeCom[0],exeCom);
    }
    else {
      int status,r;
      r = wait(&status);
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
