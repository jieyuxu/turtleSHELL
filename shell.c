#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cd(char *pth){
    int BUFFERSIZE=50;
    char path[BUFFERSIZE];
    strcpy(path,pth);

    char cwd[BUFFERSIZE];
    if(pth[0] != '/')
    {// true for the dir in cwd
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,path);
        chdir(cwd);
    }else{//true for dir w.r.t. /
        chdir(pth);
    }
    return 0;
}

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
   // *strchr(buf, "\n") = NULL;
    for (i; command[i] = strsep(&bufadd, " "); i++);
    command[i] = 0;
    
    if (!(strcmp(command[0],"exit"))){
      exit(0);
    }
    char directories[30];
    if (!(strcmp(command[0],"cd"))){
      char* location = strchr(command[1], '\n');
      strcpy(directories, command[1]);
      cd(directories);
    }    
    else { 
        int pid = fork();
        if (pid == 0)
           execvp( command[0], command );]
        else
           wait(NULL);
   }
  }
}
