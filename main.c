#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>

#include "t_rex.h"
#include "shell.h"

int main(){
	while(1){
		int fdin, fdout;
		fdin = fdout = -1;
		char buf[256];
		char * command[20];
		prompt();
		readin(buf);
		parse(command, buf);
	}
	return 0;
}