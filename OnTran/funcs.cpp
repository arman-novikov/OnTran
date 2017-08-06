#include "funcs.h"

using namespace std;

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

void mypause()
{
    char delay;
    cout<<"\ninput smth to exit\n";
    cin>>delay;
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
    int_temp %= 10000;
    temp++;
    *temp = myUSItoch(int_temp/1000);
    int_temp %= 1000;
    temp++;
    *temp = myUSItoch(int_temp/100);
    int_temp %= 100;
    temp++;
    *temp = myUSItoch(int_temp/10);
    int_temp %= 10;
    temp++;
    *temp = myUSItoch(int_temp);
    temp++;
    *temp = '\0';

}

void mystrcpy(char *in, char *from)
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

short int mystrlen(char *x)
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

void mystrclean(char *str, short int i)
{
    char *ptr = str;
    for(int j=0;j<i;j++)
    {
        *(++ptr)='\0';
    }

}

bool mystrcmp(char *first, char *second)
{
    char *tempf = first;
    char *temps = second;

    do
    {
        if (*tempf != *temps) return 0;

        tempf++;
        temps++;
    }
    while (*tempf != '\0' && *temps != '\0');

    return 1;
}

bool isENletter(char x)
{
    if(   x == 'a' || x == 'b' || x == 'c' || x == 'd' || x == 'e' || x == 'f'
       || x == 'g' || x == 'h' || x == 'i' || x == 'j' || x == 'k' || x == 'l'
       || x == 'm' || x == 'n' || x == 'o' || x == 'p' || x == 'q' || x == 'r'
       || x == 's' || x == 't' || x == 'u' || x == 'v' || x == 'w' || x == 'x'
       || x == 'y' || x == 'z' || x == 'A' || x == 'B' || x == 'C' || x == 'D'
       || x == 'E' || x == 'F' || x == 'G' || x == 'H' || x == 'I' || x == 'J'
       || x == 'K' || x == 'L' || x == 'M' || x == 'N' || x == 'O' || x == 'P'
       || x == 'Q' || x == 'R' || x == 'S' || x == 'T' || x == 'U' || x == 'V'
       || x == 'W' || x == 'X' || x == 'Y' || x == 'Z' || x== '-') return 1;

    else return 0;
}

bool isRUletter(char x)
{
    if(   x == 'а' || x == 'б' || x == 'в' || x == 'г' || x == 'д' || x == 'е'
       || x == 'ё' || x == 'ж' || x == 'з' || x == 'и' || x == 'й' || x == 'к'
       || x == 'л' || x == 'м' || x == 'н' || x == 'о' || x == 'п' || x == 'р'
       || x == 'с' || x == 'т' || x == 'у' || x == 'ф' || x == 'х' || x == 'ц'
       || x == 'ч' || x == 'ш' || x == 'щ' || x == 'ъ' || x == 'ы' || x == 'ь'
       || x == 'э' || x == 'ю' || x == 'я' || x == 'А' || x == 'Б' || x == 'В'
       || x == ' ' || x == 'Д' || x == 'Е' || x == 'Ё' || x == 'Ж' || x == 'З'
       || x == 'И' || x == 'Й' || x == 'К' || x == 'Л' || x == 'М' || x == 'Н'
       || x == 'О' || x == 'П' || x == 'Р' || x == 'С' || x == 'Т' || x == 'У'
       || x == 'Ф' || x == 'Х' || x == 'Ц' || x == 'Ч' || x == 'Ш' || x == 'Щ'
       || x == 'Ъ' || x == 'Ы' || x == 'Ь' || x == 'Э' || x == 'Ю' || x == 'Я'
       || x == '-') return 1;

      else return 0;
}

void mkWORDdir(char *word_to_dict, char *initial_form)
{
    if(0)
    { //it's for future crossplatforming
        char *temp = new char[50];
        getcwd(temp,50);
        char *path = new char[mystrlen(temp)+1];
        mystrcpy(path,temp);
        delete [] temp;
    }

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
    fout.close();


    delete [] tofile;
    delete [] path;
    delete [] write;
    delete [] crc_str;
    return;
}

void show_dir_path()
{
    char *y=new char[50];
    cout<<getcwd(y,50);
    delete [] y;

}

void enstrTOint(char *str, int *arr)
{
    char *temp = str;
    delete arr;
    arr = new int[mystrlen(str)];
    int i=0;

    while(*temp!='\0')
    {
        if      (*temp=='a')arr[i]=1;
        else if (*temp=='b')arr[i]=2;
        else if (*temp=='c')arr[i]=3;
        else if (*temp=='d')arr[i]=4;
        else if (*temp=='e')arr[i]=5;
        else if (*temp=='f')arr[i]=6;
        else if (*temp=='g')arr[i]=7;
        else if (*temp=='h')arr[i]=8;
        else if (*temp=='i')arr[i]=9;
        else if (*temp=='j')arr[i]=10;
        else if (*temp=='k')arr[i]=11;
        else if (*temp=='l')arr[i]=12;
        else if (*temp=='m')arr[i]=13;
        else if (*temp=='n')arr[i]=14;
        else if (*temp=='o')arr[i]=15;
        else if (*temp=='p')arr[i]=16;
        else if (*temp=='q')arr[i]=17;
        else if (*temp=='r')arr[i]=18;
        else if (*temp=='s')arr[i]=19;
        else if (*temp=='t')arr[i]=20;
        else if (*temp=='u')arr[i]=21;
        else if (*temp=='v')arr[i]=22;
        else if (*temp=='w')arr[i]=23;
        else if (*temp=='x')arr[i]=24;
        else if (*temp=='y')arr[i]=25;
        else if (*temp=='z')arr[i]=26;
        else if (*temp=='-')arr[i]=49;
        else if (*temp==' ')arr[i]=0;
        else
        {
            cout<<"unknown literal "<<(*temp);
            return;
        }
       i++;
       temp++;
    }
}

