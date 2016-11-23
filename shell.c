#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

//for each semicolon, fork and pass an array for the child process to do and ask parent to wait
void parse(char* in){
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
}


void func(char* in){
  strtok(in,"\n");
  char *commands[50];
  char *s = in;
  
  int i = 0;
  while (commands[i] = strsep(&s,";")) {
    i++;
  }

  int j = 0;
  int f;
  int index;
  for (j; j < i; j++) {
    f = fork();
    if (f == 0) {
      char *ar[50];
      char *t = commands[j];
      if (j != 0) {
	t++;
      }
      if (t[strlen(t)-1] == ' ') {
	t[strlen(t)-1] = 0;
      }

      // printf("Hello %s \n",t);  
      int k = 0;
      while (ar[k] = strsep(&t," ")) {
	k++;
      }
      ar[k] = 0;
    
      execvp(ar[0],ar);
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
    func(s1);
  }
  return 0;
}
