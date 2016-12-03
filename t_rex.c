#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>

#include "t_rex.h"

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


char* trim(char* input)                                         
{
    int j;
    char *output=input;
    printf("input - %s\n", input);
    int i =0;
    while (input[i]==' ')
    {        
       i++;                                     
    }
    input = (input+i);
    
    int k=0;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    { 
        //if (input[i]!=' ')                           
           // output[j]=input[i];                     
       // else
           // j--;
       
}
    //output[j]=0;
    printf("input - %s\n", input);
// *input = output;
    return input;
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

/*char* trim(char **str){
printf("in trim %s\n", *str);

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
}*/

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
void parse(char * buf){
  char * semi = NULL;
  printf("WHERE DID YOU BREAK5 %s\n", buf);
  int i = 0;
  buf= trim(buf);
  printf("WHERE DID YOU BREAK6 %s\n", buf);
  //if multiple commands
  if (strchr(buf, ';')) {
      char* semi = (char *)malloc(256);
      while ( semi = strsep(&buf, ";") ) {
         printf("WHERE DID YOU BREAK\n");
         semi= trim(semi);
         exec_1com(semi, NULL, NULL);
       }
       if (semi !=NULL)
          free(semi);
  }
  else {
       //just one command

       exec_1com(buf, NULL, NULL);
         }
}

void exec_1com(char* buf, char *fin, char *fout){
    char * cmd[20];
    int i; 
    char bufsave[50];
    strcpy(bufsave, buf);
    for (i=0; cmd[i] = strsep(&buf, " "); i++);
    cmd[i] = 0;

    //char * redir = (char *)malloc(256);
    printf("bufsave %s\n", bufsave);
    if (strchr(bufsave, '<') || strchr(bufsave, '>') )  
         redirect(bufsave);
    else
         exec(cmd, fin, fout); 
}

void redirect(char * bufadd) {
    int i=0;
    int first=1;
    char *rest = bufadd;
    char  *sin=NULL; 
    char  *sout=NULL;
    char  *fin=NULL;
    char *fout=NULL;
    
    while (1) { 
       sin=strchr(rest, '<');
       sout=strchr(rest, '>');
       printf("!!in=%s, out=%s\n", sin, sout);
       if (sin == NULL &&  sout == NULL )
           break; 
    
      //contains "<" or ">" 
        if (first && sin != NULL && sout==NULL){
        // only input
            bufadd = strsep(&rest , "<");
            fin = trim(rest);
printf("1\n");
        }
        if (first && sin == NULL && sout!=NULL){
        // only output
            bufadd = strsep(&rest , ">");
            fout = trim(rest);
printf("2\n");   
        }
        if (sin != NULL && sout!=NULL) {
            char *buf1, *buf2;
            char* r1, *r2;
            r1 = malloc(30*sizeof(char));
            r2 = malloc(30*sizeof(char));
            strcpy( r1, rest);
            strcpy( r2, rest);
            buf1 = strsep(&r1 , "<");
            buf2 = strsep(&r2 , ">");
            if ( strlen(r1) > strlen(r2) ) {
               bufadd = buf1;
               rest = trim(r1);
            }
            else {
               bufadd = buf2;
               rest = trim(r2); 
            }
            printf("buf=%s, rest=%s\n", bufadd, rest);
        }         
        if (!first && sin != NULL && sout==NULL){
        // > < 
            fout = trim(strsep(&rest , "<"));
            fin = trim(rest);
printf("4\n");   
        }
        // < >
        if ( !first && sin == NULL && sout!=NULL){
            fin = strsep(&rest , ">");
            fout = trim(rest);  
printf("5\n");             
        }
        first = 0;
  } 
  printf("in=%s, out=%s\n", fin, fout);
  
  bufadd= trim(bufadd);
  exec_1com(bufadd, fin, fout);
    

}


void exec(char** cmd, char *fin, char *fout){
    int saved_stdout = 1;
    int saved_stdin = 0;
    char directories[30];
    int fdin=-1;
    int fdout=-1;
  
    printf("fin %s fout%s\n", fin, fout);
    if (fin != NULL) 
       fdin = open(fin, O_RDONLY, 0666);
    if (fout != NULL) {
       fdout = open(fout, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    } 
      
    if (!(strcmp(cmd[0],"exit")))
      exit(0);
    printf("cmd %s<- %s\n", cmd[0], cmd[1]);

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
     
      
      int tpid;
      int stat=0;
      int chpid = fork();
      printf("cmd ->%s<- ->%s<-\n", cmd[0], cmd[1]);
      if (chpid == 0) 
         execvp( cmd[0], cmd );
      else {
         do { 
           tpid = wait(&stat);
           printf("id %d\n", tpid);
         } while(tpid != -1);
      } 
      printf("fdin %d fdout%d\n", fdin, fdout);
      if(fdin != -1){          
          //close(fdin);
          dup2(saved_stdin, 0);

      }
      if(fdout!= -1) {
          //close(fdout);
          dup2(saved_stdout, 1);  
          
      }
      printf("finished");
  }
}
