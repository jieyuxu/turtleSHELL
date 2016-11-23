#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {

}

char * parse(){
  char buf[100];
  printf("Enter command separated by a single space"); 
  fgets(buf, sizeof(buf), stdin);
  char * bufadd = buf;
  char *command[50];
  int i = 0;
  /*while (bufadd) {
    command[i] = strsep(&bufadd," ");
    i++;
  }*/
  *strchr(buf, "\n") = NULL;
  for (i; command[i] = strsep(&buffadd, " "); i++);
  command[i] = 0;
  return command;
}

void exec(char * command){
  fork();
  execvp(command[0], command);
}
