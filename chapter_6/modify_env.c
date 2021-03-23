#define _GUN_SOURCE

#include <stdlib.h>
#include "tlpi_hdr.h"

extern char** environ;

int main(int argc, char* argv[])
{
    int j;
    char ** ep;

    clearenv();

    for(j = i; j < argc; j++)
    {
        if (putenv(argc[j] != 0))
        {
            errExit("putenv : %s ", argc[j]);
        }
    }

    if (setenv("GREET", "hello world", 0) == -1)
    {
        errExit("setenv");
    }

    unsetenv("byg");

    for (ep = environ; *ep != NULL; ep++)
    {
        puts(*ep);
    }

    exit(EXIT_SUCCESS);
}