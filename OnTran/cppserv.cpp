#include "cppserv.h"

Server::Server()
{
    ThisDict = new Dict;
    ThisDict->forming();
}

void Server::push_descr(int port)
{
    int sock, listener, bytes_read;

    struct sockaddr_in addr;

    char buf[32];
    char *ptr_buf = buf;

    char *forsend = new char[128];

    listener = socket(AF_INET, SOCK_STREAM, 0);

    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr,sizeof(addr))<0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener,1); //listener == socket to listen, 1 == size of requests queue

    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 32, 0);
            if(bytes_read <=0) break;
            ThisDict->getDesc(ptr_buf, forsend);
            send(sock,forsend, mystrlen(forsend), 0);
            forsend[0] = '\0';
            buf[0] = '\0';
        }
        close(sock);
    }

    delete [] forsend;
    return;
}


void Server::push_trans(int port)
{
    int sock, listener, bytes_read;

    struct sockaddr_in addr;

    char buf[110];
    char *ptr_buf = buf;

    char *forsend = new char[110];

    listener = socket(AF_INET, SOCK_STREAM, 0);

    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr,sizeof(addr))<0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener,1); //listener == socket to listen, 1 == size of requests queue

    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 110, 0);
            if(bytes_read <=0) break;

            ThisDict->getTran(ptr_buf, forsend);
            send(sock,forsend, mystrlen(forsend), 0);
            //forsend[0] = '\0';
            //buf[0] = '\0';
            // todo a check for the first =='\0'
            mystrclean(forsend,mystrlen(forsend));
            mystrclean(buf, mystrlen(buf));
        }
        close(sock);
    }


    delete [] forsend;
    return;
}


Server::~Server()
{
    ThisDict->~Dict();
}

