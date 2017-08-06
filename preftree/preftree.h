#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>


#ifndef PREFTREE_H_INCLUDED
#define PREFTREE_H_INCLUDED

#define DICTDIR "mkdir -p ~/KRPR\0"
#define DICTWOR "touch \0"
#define DICTFIL "/home/arman\0"


void mkWORDdir(char *word_to_dict, char *initial_form);

void mystrcpy(char *in,char *from);
short int mystrlen(char* x);

unsigned short int crc16(char *odno_slovo,int dlina_slova);

char myUSItoch(int x);
void myUSItostr(unsigned short int from,char *in);

void mypause();

#endif // PREFTREE_H_INCLUDED
