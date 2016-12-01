#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>
#include "t_rex.h"
/*
Trim gets rid of the trailing and front spaces
*/
char *trim(char *str)
{
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
	fgets(buf, 50, stdin);	
	*(strchr(buf, '\n')) = '\0';
}

/*
Parse trims the buf, getting rid of any unneccessary space between and after and then modifies
the given char ** cmd, filling it with the input from buf
*/
void parse(char ** cmd, char * buf){
  int i = 0;
  buf = trim(buf);
  //printf("buf: %s\n", buf);
  for (i; cmd[i] = strsep(&buf, " "); i++);
  cmd[i] = 0;
}

void exec(char** cmd, int fdin, int fdout){
    int saved_stdout;
    int saved_stdin;
    if (!(strcmp(cmd[0],"exit"))){
      exit(0);
    }
    char directories[30];
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
}


int main(){
	char buf[50];
	char * command[20];
	readin(buf);
	parse(command, buf);
	exec(buf, command);
	return 0;
}
