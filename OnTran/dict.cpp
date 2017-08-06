#include "dict.h"
#include <cstring>

#define COUTDICTCRC cout<<i++<<"  "<<crcint<<"   "; dictionary[crcint].show(); cout<<endl;

using namespace std;

char dictSources[26][13]
{
    "En-Ru/A.txt\0",
    "En-Ru/B.txt\0",
    "En-Ru/C.txt\0",
    "En-Ru/D.txt\0",
    "En-Ru/E.txt\0",
    "En-Ru/F.txt\0",
    "En-Ru/G.txt\0",
    "En-Ru/H.txt\0",
    "En-Ru/I.txt\0",
    "En-Ru/J.txt\0",
    "En-Ru/K.txt\0",
    "En-Ru/L.txt\0",
    "En-Ru/M.txt\0",
    "En-Ru/N.txt\0",
    "En-Ru/O.txt\0",
    "En-Ru/P.txt\0",
    "En-Ru/Q.txt\0",
    "En-Ru/R.txt\0",
    "En-Ru/S.txt\0",
    "En-Ru/T.txt\0",
    "En-Ru/U.txt\0",
    "En-Ru/V.txt\0",
    "En-Ru/W.txt\0",
    "En-Ru/X.txt\0",
    "En-Ru/Y.txt\0",
    "En-Ru/Z.txt\0"
};


Dict::Dict()
{
    std::cout<<"allocating memory for the dict\n";

}

Dict::~Dict()
{
    Word * Ptr=dictionary;
    for (int i=0; i<dictSize; i++)
    {
        if((Ptr->isReserved()))
        {
            Ptr+=i;
            bitreeDelete(Ptr);
        }
    }

}

void Dict::forming()
{
    dictionary = new Word[dictSize];
    Word *Wtemp = new Word;

    union forcri critemp;
    unsigned short int crcint,i=0; // i is for COUTDICTCRC

    char ch;
    char *temp = new char[110];
    char *temp_ptr;



    for (int i=0;i<26;i++)
    {
        //here we open dictionary file #i
        ifstream fin(dictSources[i]);

        if(fin.is_open())
        {
            while (fin.get(ch))
            {
                //here we begin take a word from the file
                if(ch=='%')
                {
                    temp_ptr=temp;
                    *temp_ptr='\0';

                    fin.get(ch);

                    while(ch!='%')
                    {
                        *temp_ptr=ch;
                        temp_ptr++;
                        fin.get(ch);
                    }
                    *temp_ptr='\0';
                    //^here we have a *word;

                    // write int representation of the word[0]
                    critemp.y = temp[0];

                    // count hash of the word
                    crcint=crc16(temp,mystrlen(temp));

                    //begin to work with cell of dictionary #crcint
                    Wtemp = &(dictionary[crcint]);

                    //write it into the Dict cell #crcint
                    if(!(*Wtemp).isReserved())
                    {
                        (*Wtemp).reservedWrite(1);
                        (*Wtemp).wordWrite(temp, mystrlen(temp));
                    }

                    //or in a branch if the cell/it's branches are reserved
                    else
                    {
                        bitreeWrite(Wtemp,critemp.x);

                        (*Wtemp).reservedWrite(1);
                        (*Wtemp).wordWrite(temp, mystrlen(temp));
                    }
                }

                //here we begin take a word's translation from the file
                //and write it into the Dict
                if(ch=='*')
                {
                    temp_ptr=temp;
                    *temp_ptr='\0';

                    fin.get(ch);

                    while(ch!='*')
                    {
                        *temp_ptr=ch;
                        temp_ptr++;
                        fin.get(ch);
                    }
                    *temp_ptr='\0';
                    (*Wtemp).tranWrite(temp, mystrlen(temp));
                }

                //here we begin take a word's pos from the file
                //and write it into the Dict
                if(ch=='^')
                {

                    temp_ptr=temp;
                    *temp_ptr='\0';

                    fin.get(ch);

                    while(ch!='^')
                    {
                        *temp_ptr=ch;
                        temp_ptr++;
                        fin.get(ch);
                    }
                    *temp_ptr='\0';
                    (*Wtemp).posWrite(temp);
                }

                //here we begin take a word's description from the file
                //and write it into the Dict
                if(ch=='+')
                {

                    temp_ptr = temp;
                    *temp_ptr='\0';

                    fin.get(ch);

                    while(ch!='+')
                    {
                        *temp_ptr=ch;
                        temp_ptr++;
                        fin.get(ch);
                    }
                    *temp_ptr='\0';
                    (*Wtemp).descrWrite(temp,mystrlen(temp));
                }

            //if(ch=='='){COUTDICTCRC}
            }
        }

        /*
        else
        {
            cout << "File \'"
                 << dictSources[i]
                 << "\' not found"
                 << endl;
        }
        */
        fin.close();
    }
    delete [] temp;
    return;
}

void Dict::getDesc(char *about, char *where)
{
    char *temp = about;
    char dir[50] = "/home/arman/KRPR/\0";
    char fail[] = "nothing is founded\0";
    char word[30];
    char *ptr_dir = &dir[17];
    char *ptr_word = word;
    char *crcbuf = new char[6];
    char *wordbuf = new char[32];
    unsigned short int  tempcrc;

    if(!HALT)
    {
        unsigned short int tempcrc = crc16(about, mystrlen(about));
        dictionary[tempcrc].descGet(about, where);

        delete [] crcbuf;
        delete [] wordbuf;
        return;
    }


    ptr_dir = &dir[17];
    ptr_word = word;

    while(*temp != '\0')
    {
        *ptr_dir = *temp;
        ptr_dir++;
        *ptr_dir = '/';
        ptr_dir++;
        *ptr_dir = '\0';

        *ptr_word = *temp;
        ptr_word++;
        *ptr_word = '\0';

        temp++;
    }

    ptr_word = word;

    while(*ptr_word != '\0')
    {
        *ptr_dir = *ptr_word;
        ptr_dir++;
        ptr_word++;
    }


    *ptr_dir = '.';
    ptr_dir++;
    *ptr_dir = 't';
    ptr_dir++;
    *ptr_dir = 'x';
    ptr_dir++;
    *ptr_dir = 't';
    ptr_dir++;
    *ptr_dir = '\0';


    ifstream in(dir);
    if(in.is_open())
    {
        in.getline(crcbuf,8);
        in.getline(wordbuf,32);
        tempcrc =  atoi(crcbuf);
        dictionary[tempcrc].descGet(wordbuf, where);
    }

    else
    {
        mystrcpy(where, fail);
    }

    delete [] crcbuf;
    delete [] wordbuf;
    return;
}

void Dict::getTran(char *what, char *where)
{
    char *temp = what;
    char dir[50] = "/home/arman/KRPR/\0";
    char word[30];
    char *ptr_dir;
    char *ptr_word;
    char *crcbuf = new char[6];
    char *wordbuf = new char[32];

    int n = 1, i = 0;
    unsigned short int  tempcrc;


    if(!HALT)
    {
        tempcrc = crc16(what, mystrlen(what));
        dictionary[tempcrc].tranGet(what, where);
        return;
    }

    //how many words
    while(*temp != '\0')
    {
        if(*temp == ' ') n++;
        temp++;
    }


    char **str = new char* [n];

    temp = what;

    while(*temp != '\0')
    {
        while(!isENletter(*temp)) temp++;
        //if(*temp == '\0') goto notthistime;

        ptr_dir = &dir[17];
        ptr_word = word;

        while(isENletter(*temp))
        {
            *ptr_dir = *temp;
            ptr_dir++;
            *ptr_dir = '/';
            ptr_dir++;
            *ptr_dir = '\0';

            *ptr_word = *temp;
            ptr_word++;
            *ptr_word = '\0';

            temp++;

        }

//notthistime:

        ptr_word = word;
        while(*ptr_word != '\0')
        {
            *ptr_dir = *ptr_word;
            ptr_dir++;
            ptr_word++;
        }

        *ptr_dir = '.';
        ptr_dir++;
        *ptr_dir = 't';
        ptr_dir++;
        *ptr_dir = 'x';
        ptr_dir++;
        *ptr_dir = 't';
        ptr_dir++;
        *ptr_dir = '\0';

        ifstream in(dir);
        if(in.is_open())
        {
            in.getline(crcbuf,8);
            in.getline(wordbuf,32);
            tempcrc =  atoi(crcbuf);

            str[i] = new char [mystrlen(wordbuf)];
            dictionary[tempcrc].tranGet(wordbuf,str[i]);
        }

        else
        {
            str[i] = new char [mystrlen(word)];
            mystrcpy(str[i], word);
        }

        crcbuf[0] = '\0';
        wordbuf[0] ='\0';
        i++;
    }

    char *ptr_where = where;
    for (int j = 0; j<n; j++)
    {
        ptr_word = str[j];

        do
        {
            *ptr_where = *ptr_word;
            ptr_where++;
            ptr_word++;
        }
        while(*ptr_word != '\0');

        *ptr_where = ' ';
        *ptr_where++;
    }

    *ptr_where = '\0';


    for (int j = 0; j<n; j++) delete [] str[j];
    delete [] str;
    delete [] crcbuf;
    delete [] wordbuf;
    return;

}
