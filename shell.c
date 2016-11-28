#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "headers.h"

//for each semicolon, fork and pass an array for the child process to do and ask parent to wait
/*void parse(char* in){
  strtok(in,"\n");
  char *array[50];
  char *s = in;

  int i = 0;
  while(s){
  array[i] = strsep(&s," ");
  i++;
  }

  array[i] = 0;
  //return array;
  execvp(array[0], array);
  }*/

//


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

      // printf("Hello %s \n",t);
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

/*
  char * stripLastSpace(char *s) {
  char *l = s;
  while (*(l+1)) {
  l++;
  }
  if (*l == " ") {
  *l = "\0";
  }
  return s;
*/

int main() {
  while (1) {
    char s1[256];
    printf("~$ ");
    fgets(s1,sizeof(s1),stdin);
    //parse(s1);
    //run(a);
    execute(s1);
  }
  return 0;
}
