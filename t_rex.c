#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>

#include "t_rex.h"
#include "shell.h"

/*
T-REX:
Trim-Readin-Execute
*/

/*
Trim gets rid of the trailing and front spaces
*/
void prompt(){
  char getcd[50];
  char hostname[50];
  if (gethostname(hostname, sizeof(hostname)) == -1)
    printf("%s ", getcwd(getcd, sizeof(getcd)));
  else
    printf("%s %s$ ", getcwd(getcd, sizeof(getcd)), getenv("USER"));
}

int cd(char *pth){
    int BUFFERSIZE=256;
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

char *trim(char *str){
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

/*
Readin modifies a char * array and fills it with the input from fgets
*/
void readin(char * buf){
	fgets(buf, 256, stdin);	
	*(strchr(buf, '\n')) = '\0';
}

/*
Parse trims the buf, getting rid of any unneccessary space between and after and then modifies
the given char ** cmd, filling it with the input from buf
*/
void parse(char ** cmd, char * buf){
  char * new = (char *)malloc(256);
  printf("WHERE DID YOU BREAK5\n");
  new = strsep(&buf, ";");
  printf("WHERE DID YOU BREAK4\n");
  int i = 0;
  buf = trim(buf);
  printf("WHERE DID YOU BREAK6\n");
  //if multiple
  if (new){
    printf("WHERE DID YOU BREAK\n");
    trim(new);
    for (i; cmd[i] = strsep(&new, " "); i++);
    cmd[i] = 0;
    exec(cmd, -1, -1);
  }

  i = 0;
  //just one command
  for (i; cmd[i] = strsep(&buf, " "); i++);
  cmd[i] = 0;
  exec(cmd, -1, -1);
  printf("WHERE DID YOU BREAK2\n");
  free(new);
}

void exec(char** cmd, int fdin, int fdout){
    int saved_stdout;
    int saved_stdin;
    char directories[30];

    if (!(strcmp(cmd[0],"exit")))
      exit(0);
    
    if (!(strcmp(cmd[0],"cd"))){
      char* location = strchr(cmd[1], '\n');
      strcpy(directories, cmd[1]);
      cd(directories);
    }   

    else {
      if(fdin != -1){
          saved_stdin = dup(0);
          dup2(fdin, 0);
      }
      if(fdout!= -1) {
          saved_stdout = dup(1);
          dup2(fdout, 1);
      }

      int pid = fork();
      if (pid == 0)
         execvp( cmd[0], cmd );
      else
         wait(NULL);
      dup2(saved_stdout, 1);
      dup2(saved_stdin, 0);
   }
}
