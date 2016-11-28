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

      char *store = commands[counter];
      printf("S: %s\n", commands[counter]);
      
      int wordCount = 0;
      int outChange = 0;
      int inChange = 0;
      while (comStr && !inChange && !outChange) {
	char *part = strsep(&comStr," ");
	if (strcmp(part,">") != 0 && strcmp(part,"<") != 0) {
	  exeCom[wordCount] = part;
	}
	if (strcmp(part,">") == 0) {
	  outChange = 1;
	}
	if (strcmp(part,"<") == 0) {
	  inChange = 1;
	}
	wordCount++;
      }
      exeCom[wordCount] = 0;


      if (outChange) {
	umask(000);
	int fd = open("test",O_CREAT | O_WRONLY);
	//The fd below hasn't been tested yet
	//int fd = open(comStr,O_CREAT | O_WRONLY);
	dup2(fd,1);
	close(fd);
	execvp(exeCom[0],exeCom);
      }
      //This has not yet been tested
      else if (inChange) {
	umask(000);
	int fd = open(comStr,O_RDONLY);
	dup2(fd,0);
	close(fd);
	execvp(exeCom[0],exeCom);
      }
      else if (strcmp(exeCom[0],"cd") == 0) {
	chdir(exeCom[1]);
      }
      else {
	execvp(exeCom[0],exeCom);
      }
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
