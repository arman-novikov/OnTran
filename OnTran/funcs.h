#include "iostream"
#include "fstream" //system("mkdir -p ~/tmp/a/9");
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>  // for :  char *getcwd(char *buf, size_t size); for close(sock)
#include <sys/socket.h>
#include <netinet/in.h>


#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

//data
#define DICTDIR    "mkdir -p ~/KRPR\0"
#define DICTWOR    "touch \0"
#define DICTFIL    "/home/arman\0"
#define DESCRPORT  3711
#define TRANSLPORT 3800
#define HALT 1



//functions
void mypause();

unsigned short int crc16(char *odno_slovo,int dlina_slova);

short int mystrlen(char *x);
void mystrcpy(char *x, char *y);
void mystrclean(char *str, short int i);

bool isENletter(char x);
bool isRUletter(char x);
bool mystrcmp(char *first, char *second);

void enstrTOint(char *str, int *arr);
void mkWORDdir(char *word_to_dict, char *initial_form);
char myUSItoch(int x);
void myUSItostr(unsigned short int from,char *in);


#endif // FUNCS_H_INCLUDED
