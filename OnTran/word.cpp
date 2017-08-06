#include "word.h"

using namespace std;

void Word::show()
{
    cout<<"reserved: "<<reserved<<' '<<word<<' '<<tran<<' '<<"       pos: "<<enEpos
    <<endl<<descr;
    return;
}

void Word::reservedWrite(bool b)
{
    try
    {
        reserved = b;
    }
    catch(...)
    {
        cout<<"\nwrong parameter\n";
    }
}

void Word::wordWrite(char *x,short int len)
{
    word = new char[len];
    char *ptr1 = word, *ptr2=x;

    while(*ptr2!='\0')
    {
        *ptr1=*ptr2;
        ptr1++;
        ptr2++;
    }
    *ptr1='\0';
}

void Word::tranWrite(char *x, short int len)
{
    tran = new char[len];
    char *ptr1 = tran, *ptr2=x;

    while(*ptr2!='\0')
    {
        *ptr1=*ptr2;
        ptr1++;
        ptr2++;
    }
    *ptr1='\0';
}

void Word::posWrite(char *x)
{
    enEpos = (pos) atoi(x);
}

void Word::descrWrite(char *x, short int len)
{
    descr = new char[len];
    char *ptr1 = descr, *ptr2=x;

    while(*ptr2!='\0')
    {
        *ptr1=*ptr2;
        ptr1++;
        ptr2++;
    }
    *ptr1='\0';
}

void Word::criWrite()
{
    cri.y=word[0];
}

bool Word::isReserved()
{
    if(reserved) return 1;
    else return 0;
}

short int Word::criGet()
{
    return cri.x;
}

void Word::tranGet(char *what, char *where)
{
    Word *Temp = this;
    union forcri temp_cri;
    temp_cri.y = what[0];

    while (!mystrcmp(what,(*Temp).word))
    {
        // compare int representation of the given word[0] and this->word[0]
        if (temp_cri.x > Temp->criGet())
        {
            // if int representation of the given word[0] is MORE then this->cri.x
            //go to the right branch
            Temp = this->right;
            //check the existence of the right branch
            if (Temp == nullptr)
            {
                //if no appropriate data is found return the translation required word
                mystrcpy(where, what);
                return;
            }
        }

        else
        {
            // else go to the left branch
            Temp = this->left;
            //check the existence of the left branch
            if (Temp == nullptr)
            {
                //if no appropriate data is found return the translation required word
                mystrcpy(where, what);
                return;
            }
        }
    }

    //we found appropriate translation
    mystrcpy(where, (*Temp).tran);

    return;
}

void Word::descGet(char *about, char *where)
{
    Word *Temp = this;
    union forcri temp_cri;
    temp_cri.y = about[0];

    while (!mystrcmp(about,(*Temp).word))
    {
        // compare int representation of the given word[0] and this->word[0]
        if (temp_cri.x > Temp->criGet())
        {
            // if int representation of the given word[0] is MORE then this->cri.x
            //go to the right branch
            Temp = this->right;
            //check the existence of the right branch
            if (Temp == nullptr)
            {
                //if no appropriate data is found return the description required word
                mystrcpy(where, about);
                return;
            }
        }

        else
        {
            // else go to the left branch
            Temp = this->left;
            //check the existence of the left branch
            if (Temp == nullptr)
            {
                //if no appropriate data is found return the description required word
                mystrcpy(where, about);
                return;
            }
        }
    }

    //we found appropriate description
    mystrcpy(where, (*Temp).descr);

    return;
}

void bitreeWrite(Word *X, short int y)
{
    while(X!=nullptr)
    {
        if(y>(*X).criGet())
        {
            X=X->right;
            bitreeWrite(X,y);
        }
        else
        {
            X=X->left;
            bitreeWrite(X,y);
        }
    }
    X=new Word;
    return;
}

Word::~Word()
{
    delete [] word;
    delete [] tran;
    delete [] descr;
}

void bitreeDelete(Word *Tie)
{

    Word *temp;
    if (Tie != nullptr)
    {
        temp = Tie->left;
        bitreeDelete(temp);
    }
    if (Tie != nullptr)
    {
        temp = Tie->right;
        bitreeDelete(temp);
    }
    delete Tie;
}


