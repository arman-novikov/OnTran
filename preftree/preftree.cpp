#include "preftree.h"

using namespace std;

void mystrcpy(char *in,char *from)
{
    char *ptr1 = in, *ptr2=from;

    while(*ptr2!='\0')
    {
        *ptr1=*ptr2;
        ptr1++;
        ptr2++;
    }
    *ptr1='\0';
}

short int mystrlen(char* x)
{
    char *temp = x;
    short int res=0;
    while(*temp!='\0')
    {
        temp++;
        res++;
    }
    return res;
}


unsigned short int crc16(char *odno_slovo,int dlina_slova)
// в качестве аргументов использую указатель на слово и длину этого слова
{
    char *temp = odno_slovo;
    unsigned short int crc; //это будет результатом данной функции
    crc = 0xFFFF;  //== 1111111111111111 в двоичной
    while(dlina_slova--) {
        crc = ((crc>>8)^*temp++)&0xFF ^ (crc<<8);
        crc ^= 0xFFFF;

    }
    return crc;
}


char myUSItoch(int x)
{
    if      (x==0) return '0';
    else if (x==1) return '1';
    else if (x==2) return '2';
    else if (x==3) return '3';
    else if (x==4) return '4';
    else if (x==5) return '5';
    else if (x==6) return '6';
    else if (x==7) return '7';
    else if (x==8) return '8';
    else if (x==9) return '9';
    else return 'e';
}

void myUSItostr(unsigned short int from,char *in)
{
    char *temp = in;
    unsigned short int int_temp = from;

    *temp = myUSItoch(int_temp/10000);
    int_temp = int_temp%10000;
    temp++;
    *temp = myUSItoch(int_temp/1000);
    int_temp = int_temp%1000;
    temp++;
    *temp = myUSItoch(int_temp/100);
    int_temp = int_temp%100;
    temp++;
    *temp = myUSItoch(int_temp/10);
    int_temp = int_temp%10;
    temp++;
    *temp = myUSItoch(int_temp);
    temp++;
    *temp = '\0';

}


void mkWORDdir(char *word_to_dict, char *initial_form)
{
    char * path = new char[100];
    char temp[] = DICTDIR;
    char *path_ptr = path;
    char *x_ptr = word_to_dict;

    mystrcpy(path,temp);

    while(*path_ptr != '\0') path_ptr++;

    for (; *x_ptr != '\0'; x_ptr++)
    {
        *path_ptr = '/';
        path_ptr++;
        *path_ptr = *x_ptr;
        path_ptr++;
        *path_ptr = '\0';
    }

    system(path);

//===================================================================

    char temp1[] = DICTWOR;
    char *write = new char[70];
    x_ptr = path;
    char *write_ptr = write;

    mystrcpy(write, temp1);


    while(*write_ptr != '\0') write_ptr++;
    while(*x_ptr != '~') x_ptr++;

    for(;*x_ptr != '\0'; x_ptr++)
    {
        *write_ptr = *x_ptr;
        write_ptr++;
        *write_ptr = '/';
    }
    write_ptr++;
    *write_ptr = '\0';


    for(x_ptr = word_to_dict; *x_ptr != '\0'; x_ptr++)
    {
        *write_ptr = *x_ptr;
        write_ptr++;
        *write_ptr = '\0';
    }


    *write_ptr = '.';
    write_ptr++;
    *write_ptr = 't';
    write_ptr++;
    *write_ptr = 'x';
    write_ptr++;
    *write_ptr = 't';
    write_ptr++;
    *write_ptr = '\0';

    system(write);

//========================================

    unsigned short int int_crc = crc16(initial_form,mystrlen(initial_form));
    char *crc_str = new char[8];
    myUSItostr(int_crc, crc_str);

    char *tofile = new char[60];

    char ftemp[] = DICTFIL;
    x_ptr = ftemp;
    path_ptr = tofile;

    mystrcpy(path_ptr,x_ptr);

    x_ptr = write;
    do{x_ptr++;} while(*x_ptr != '~');
    x_ptr++;

    while(*path_ptr != '\0') path_ptr++;

    for(;*x_ptr != '\0';x_ptr++ )
    {
        *path_ptr=*x_ptr;
        path_ptr++;
        *path_ptr='\0';
    }

    ofstream fout(tofile);
    fout << crc_str;
    fout << '\n';
    fout << initial_form;
    fout.close();


    delete [] tofile;
    delete [] path;
    delete [] write;
    delete [] crc_str;
    return;
}


void mypause()
{
    char delay;
    cout<<"\ninput smth to exit\n";
    cin>>delay;
}
