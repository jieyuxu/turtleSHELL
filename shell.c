#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main() {
  while(1){
    char buf[50];
    printf("what's good:\n");

    fgets(buf, sizeof(buf), stdin);

    char * bufadd = buf;

    bufadd = strsep(&bufadd, "\n");
    char *command[10];

    int i = 0;
    while (bufadd) {
      command[i] = strsep(&bufadd, " ");
      i++;
    }

    command[i] = 0;

    int pid = fork();
    if (pid == 0){
      execvp( command[0], command );
    }
    else
      wait(NULL);
  }
}

