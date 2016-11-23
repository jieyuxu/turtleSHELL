#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main() {
  while(1){
    char buf[50];
    printf("> ");
    //  printf("Enter commands separated by a single space: "); 

    fgets(buf, sizeof(buf), stdin);

    char * bufadd = buf;

    bufadd = strsep(&bufadd, "\n");
    char *command[10];

    int i = 0;
    /* while (bufadd) {
      command[i] = strsep(&bufadd, " ");
      i++;
    }*/
    *strchr(buf, "\n") = NULL;
    for (i; command[i] = strsep(&buffadd, " "); i++);
    command[i] = 0;
    
    if (!(strcmp(command[0],"exit"))){
      exit(0);
    }
    
    int pid = fork();
    if (pid == 0){
      execvp( command[0], command );
    }
    else
      wait(NULL);
  }
}

