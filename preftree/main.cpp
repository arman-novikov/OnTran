#include "preftree.h"

void mkWORDdirTEST()
{
    char str[] = "acted\0";
    char init[] = "act\0";

    char *Ishalldelete=str;
    char *temp=init;

    mkWORDdir(Ishalldelete,temp);
}

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        mkWORDdir(argv[1], argv[2]);
    }

    return 0;
}
