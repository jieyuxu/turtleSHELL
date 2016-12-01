#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>
#include "t_rex.h"

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

/*
REDIRECTION USING >

*/
void rightRD(char * buf){

}

/*
REDIRECTION USING <
*/
void redirect(char * rest){
  int first=1;
  char *sin, *sout;
  char *fin, *fout;
  int fdin=-1;
  int fdout=-1;
  while ( (sin=strchr(rest, '<')) != NULL 
    ||  (sout=strchr(rest, '>')) != NULL ) {     
    //contains "<" or ">" 
      if (first && sin != NULL && sout==NULL){
      // only input
          bufadd = strsep(&rest , "<");
          fin = trim(rest);
      }
      if (first && sin == NULL && sout!=NULL){
      // only output
          bufadd = strsep(&rest , ">");
          fout = trim(rest);   
      }
      if (sin != NULL && sout!=NULL)
          bufadd = strsep(&rest , "<>");         
      if (!first && sin != NULL && sout==NULL){
      // > < 
          fout = trim(strsep(&rest , "<"));
          fin = trim(rest);
      }
      // < >
      if ( !first && sin == NULL && sout!=NULL){
          fin = strsep(&rest , ">");
          fout = rest;            
      }
      first = 0;

     if (fin != NULL) {
          fdin = open(fin, O_RDONLY);
     }
     if (fout != NULL) {
          fdout = open(fout, O_CREAT, 0666);
          close(fdout);
          fdout = open(fout, O_WRONLY);
     }       
  } 
}

/*
PIPE
*/
void pipe(char * buf){
  
}

int main() {
  while(1){
    char buf[50];
    char getcd[50];
    char hostname[50];
    if (gethostname(hostname, sizeof(hostname)) == -1)
      printf("%s ", getcwd(getcd, sizeof(getcd)));
    else
      printf("%s %s$ ", getcwd(getcd, sizeof(getcd)), getenv("USER"));
    //  printf("Enter commands separated by a single space: "); 

    int i=0;
    int first=1;
    char *rest = buf;
   // *strchr(buf, "\n") = NULL;
    char  *sin, *sout;
    char  *fin, *fout;
    int fdin=-1;
    int fdout=-1;
    
    while ( (sin=strchr(rest, '<')) != NULL 
      ||  (sout=strchr(rest, '>')) != NULL ) {     
      //contains "<" or ">" 
        if (first && sin != NULL && sout==NULL){
        // only input
            bufadd = strsep(&rest , "<");
            fin = trim(rest);
        }
        if (first && sin == NULL && sout!=NULL){
        // only output
            bufadd = strsep(&rest , ">");
            fout = trim(rest);   
        }
        if (sin != NULL && sout!=NULL)
            bufadd = strsep(&rest , "<>");         
        if (!first && sin != NULL && sout==NULL){
        // > < 
            fout = trim(strsep(&rest , "<"));
            fin = trim(rest);
        }
        // < >
        if ( !first && sin == NULL && sout!=NULL){
            fin = strsep(&rest , ">");
            fout = rest;            
        }
        first = 0;

       if (fin != NULL) {
            fdin = open(fin, O_RDONLY);
       }
       if (fout != NULL) {
            fdout = open(fout, O_CREAT, 0666);
            close(fdout);
            fdout = open(fout, O_WRONLY);
       }       
    } 
    
    bufadd = trim(bufadd);
  }
}
