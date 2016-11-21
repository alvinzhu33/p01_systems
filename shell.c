#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char*[] parse(char* in){
  strtok(in,"\n");
  char *array[50];
  char *s = in;
  
  int i = 0;
  while(s){
    array[i] = strsep(&s," ");
    i++;
  }

  array[i] = 0;
  return array;
  
}

void run(char *[] array) {
  execvp(array[0], array);
}

int main() {
  char s1[256];
  printf("~$ ");
  fgets(s1,sizeof(s1),stdin);
  char *a[50] = parse(s1);
  run(a);
  
  return 0;
}
