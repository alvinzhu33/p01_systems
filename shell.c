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

char* stripper(char* stripping){
  while(stripping[0] == ' '){
    *stripping++;
  }
  while(stripping[strlen(stripping)-1] == ' '){
    stripping[strlen(stripping)-1] = 0;
  }
  int counter = 0;

  char *stripped = stripping;
  return stripped;
}

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
    if (strstr(commands[counter],"exit")) {
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
	umask(000);
	remove(comStr);
	int fd = open(comStr,O_CREAT | O_RDWR, 0644);
	dup2(fd,1);
	close(fd);
	execvp(exeCom[0],exeCom);
      }
      else if (inChange) {
	umask(000);
	int fd = open(comStr,O_CREAT | O_RDWR, 0644);
	dup2(fd,0);
	close(fd);
	execvp(exeCom[0],exeCom);
      }
      //This is not yet functional and not tested
      else if (pipeTrue) {
	
	umask(000);
	remove(comStr);
	int fd = open("TUNNEL",O_CREAT | O_RDWR, 0644);
       

	
	char *command2[50];

	wordCount = 0;	
	while (command2[wordCount] = strsep(&comStr," ")) {
	  wordCount++;
	  printf("jceieibdeib\n");
	  printf("%s > \n",command2[wordCount-1]);
	}

	
	command2[wordCount] = 0;

	dup2(fd,1);
	close(fd);
	//pushes output into TUNNEL
	execvp(exeCom[0],exeCom);
	

	fd = open("TUNNEL",O_RDONLY);

	
	dup2(fd,0);
	//it should pushes TUNNEL to input here
	
	execvp(command2[0],command2);
	remove("TUNNEL");

	
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
