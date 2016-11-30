#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>


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

void readin(char * buf){
	fgets(buf, 50, stdin);	
	*(strchr(buf, '\n')) = '\0';
}


void parse(char ** cmd, char * buf){
  int i = 0;
  buf = trim(buf);
  //printf("buf: %s\n", buf);
  for (i; cmd[i] = strsep(&buf, " "); i++);
  cmd[i] = 0;
}

void exec(char ** cmd){
	execvp(cmd[0], cmd);
}

int main(){
	char buf[50];
	char * command[20];
	readin(buf);
	parse(command, buf);
	exec(command);
	return 0;
}