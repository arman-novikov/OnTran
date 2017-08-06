#include "test.h"

using namespace std;


void isletTEST()
{
    char *y=new char; *y = 'щ';
    if(isRUletter('О')) cout<<"ok2 ";

    if(*y=='щ') cout<<"fuck\n";
    cout<<"\n\nщоdваddвытывлЭж";

    return;
}

void isENletterTEST()
{
    char x ='o';
    if (isENletter(x)) cout<<"ok";

    return;
}

void dictTEST()
{
    char str1[]= "winter\0";
    char *ptr1=new char; ptr1=str1;
    char *ptr2=new char[30];
    char *ptr3=new char[110];

    Dict ENRU;
    ENRU.forming();

    ENRU.getTran(ptr1,ptr2);
    cout<<"tran: "<<ptr2<<endl;

    ENRU.getDesc(ptr1,ptr3);
    cout<<"desc: "<<ptr3<<endl;

    ENRU.~Dict();
    delete [] ptr2;
    delete [] ptr3;

    return;
}

void mkWORDdirTEST()
{
    char str[] = "acted\0";
    char init[] = "act\0";

    char *Ishalldelete=str;
    char *temp=init;

    mkWORDdir(Ishalldelete,temp);

    return;
}

void myUSItostrTEST()
{
    char stri[] = "Alex\0";
    char *ptr = stri;
    char *in = new char[8];

    myUSItostr(crc16(ptr,mystrlen(ptr)),in);
    cout<<in<<endl;

    return;
}


void threadTest()
{
    Server Enru;

    cout<<" it's ok \n\n";

    thread descr_thread(&Server::push_descr, &Enru, DESCRPORT);
    thread trans_thread(&Server::push_trans, &Enru, TRANSLPORT);
    descr_thread.join();
    trans_thread.join();

    return;
}

void getTranTEST()
{
    char str[] = "Zak winters\0";
    char *ptr = str;
    char *xlam = new char[64];
    Dict Enru;
    Enru.forming();
    Enru.getTran(str,xlam);

    return;
}
