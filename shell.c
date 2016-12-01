#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>

#include "shell.h"
#include "t_rex.h"


/*
REDIRECTION USING >

*/
void rightRD(char * buf){

}

/*
REDIRECTION USING <
*/


// int main() {
//   while(1){
//     char buf[50];
//     char getcd[50];
//     char hostname[50];
//     if (gethostname(hostname, sizeof(hostname)) == -1)
//       printf("%s ", getcwd(getcd, sizeof(getcd)));
//     else
//       printf("%s %s$ ", getcwd(getcd, sizeof(getcd)), getenv("USER"));
//     //  printf("Enter commands separated by a single space: "); 

//     int i=0;
//     int first=1;
//     char *rest = buf;
//    // *strchr(buf, "\n") = NULL;
//     char  *sin, *sout;
//     char  *fin, *fout;
//     int fdin=-1;
//     int fdout=-1;
    
//     while ( (sin=strchr(rest, '<')) != NULL 
//       ||  (sout=strchr(rest, '>')) != NULL ) {     
//       //contains "<" or ">" 
//         if (first && sin != NULL && sout==NULL){
//         // only input
//             bufadd = strsep(&rest , "<");
//             fin = trim(rest);
//         }
//         if (first && sin == NULL && sout!=NULL){
//         // only output
//             bufadd = strsep(&rest , ">");
//             fout = trim(rest);   
//         }
//         if (sin != NULL && sout!=NULL)
//             bufadd = strsep(&rest , "<>");         
//         if (!first && sin != NULL && sout==NULL){
//         // > < 
//             fout = trim(strsep(&rest , "<"));
//             fin = trim(rest);
//         }
//         // < >
//         if ( !first && sin == NULL && sout!=NULL){
//             fin = strsep(&rest , ">");
//             fout = rest;            
//         }
//         first = 0;

//        if (fin != NULL) {
//             fdin = open(fin, O_RDONLY);
//        }
//        if (fout != NULL) {
//             fdout = open(fout, O_CREAT, 0666);
//             close(fdout);
//             fdout = open(fout, O_WRONLY);
//        }       
//     } 
    
//     bufadd = trim(bufadd);
//   }
// }
