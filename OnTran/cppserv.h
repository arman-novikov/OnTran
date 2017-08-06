#include "dict.h"
#ifndef CPPSERV_H_INCLUDED
#define CPPSERV_H_INCLUDED

class Server
{
protected:
    Dict *ThisDict;
public:
    Server();
    void push_descr(int port);
    void push_trans(int port);
    ~Server();
};


#endif // CPPSERV_H_INCLUDED
