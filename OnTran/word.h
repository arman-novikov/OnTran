#include "funcs.h"

#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED

enum pos
{
    undefined=      0,
    noun=           1,
    adjective=      2,
    verb=           3,
    adverb=         4,
    hybro=          5,
    stative=        6,
    pronoun=        7,
    numeral=        8,
    conjunctions=   9,
    prepositions=   10,
    functional=     11,
    name=           12
};

union forcri
{
    short int x;
    char y;
};

class Word
{
protected:

    bool reserved;
    union forcri cri;

    char *word;
    char *tran;
    char *descr;

    enum pos enEpos;

protected:

    Word *left;
    Word *right;


public:

    Word():
           left(nullptr),
           right(nullptr),
           word(""),
           tran(""),
           descr(""),
           enEpos((pos)undefined),
           reserved(0){};
    //+++++++++++++++++++++++++

    ~Word();

    void wordWrite(char *x, short int len);
    void tranWrite(char *x, short int len);
    void reservedWrite(bool b);
    void posWrite(char *x);
    void descrWrite(char *x, short int len);
    void criWrite();

    void show();

    short int criGet();
    void tranGet(char *what, char *where);
    void descGet(char *about, char *where);
    bool isReserved();

    friend void bitreeWrite(Word *X, short int y);
    friend void bitreeDelete(Word *Tie);

};

#endif // WORD_H_INCLUDED
