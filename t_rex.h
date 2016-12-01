#ifndef T_REX
#define T_REX

int cd(char *pth);
char * trim();
void readin();
void parse(char ** cmd, char * buf);
void exec(char ** cmd, int fdin, int fdout);

#endif