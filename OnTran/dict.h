#ifndef DICT_H_INCLUDED
#define DICT_H_INCLUDED
#include "word.h"

const int dictSize = 65535;


class Dict {

//protected:
public:
    char dictName[15];
    Word * dictionary;
public:
    Dict();
    ~Dict();
    void forming();

void getTran(char* what, char* where);
void getDesc(char* about, char* where);
};

#endif // DICT_H_INCLUDED
