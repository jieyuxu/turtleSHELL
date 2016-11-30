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

char * readin(){
	char buf[50];
	//printf("what's good:\n");
	fgets(buf, sizeof(buf), stdin);	
	char * bufadd = (char *)malloc(sizeof(buf));
	bufadd = buf;
	bufadd = strsep(&bufadd, "\n");
	//printf("%s", bufadd);
	return bufadd;
}


char * parse(char * input){
  int i = 0;
  char * command[20];
  input = trim(input);
  for (i; command[i] = strsep(&input, " "); i++);
  command[i] = 0;
  //char * ret = command;
  printf("command: %s\n", command);
 // printf("ret: %s\n", *ret);
  return *command;
}


int main(){
  // char buf[50];
  // fgets(buf, sizeof(buf), stdin);
  // char * bufadd = buf;
  // parse(bufadd);
  
  //execvp(bufadd[0], bufadd);
	printf("hi: %s", readin());
	return 0;
}