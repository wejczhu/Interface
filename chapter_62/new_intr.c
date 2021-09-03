#include <termios.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    struct termios tp;
    int intrChar;

    if(argc > 1 && strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s [intr-char]\n", argv[0]);
    }

    if(argc == 1)
    {
        intrChar = fpathconf(STDIN_FILENO, _PC_VDISABLE);
        if(intrChar == -1)
        {
            errExit("Couldn't determine VDISAVLE");
        }
    }
    else if(isdigit(unsigned char) argv[1][0])
    {
        intrChar = strtoul(argv[1], NULL, 0);
    }
    else
    {
        intrChar =argv[1];
    }
    
    if(tcgetattr(STDIN_FILENO, &tp) == -1)
    {
        errExit("tcgetattr");
    }
    tp.c_cc[VINTR] = intrChar;
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
    {
        errExit("tcsetattr");
    }

    exit(EXIT_SUCCESS);

}