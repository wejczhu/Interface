#include <termios.h>
#include <signal.h>
#include <ctype.h>
#include "tty_functions.h"

#include "tlpi_hdr.h"


static struct termios userTermios;

static void handler(int sig)
{
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &userTermios) == -1)
    {
        errExit("tcsetattr");
    }
    _exit(EXIT_SUCCESS);
}

static void tstpHandler(int sig)
{
    struct termios outTermios;
    sigset_t tstpMask, prevMask;
    struct sigaction sa;
    int savedErrno;

    savedErrno = errno;

    if(tcgetattr(STDIN_FILENO, &outTermios) == -1)
    {
        errExit("tcgetattr");
    }
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &userTermios) == -1)
    {
        errExit("tcsetattr");
    }

    if(signal(SIGTSTP, SIG_DFL) == SIG_ERR)
    {
        errExit("signal");
    }

    raise(SIGTSTP);

    sigemptyset(&tstpMask);
    sigaddset(&tstpMask, SIGTSTP);
    if(sigprocmask(SIG_UNBLOCK, &tstpMask, &prevMask) == -1)
    {
        errExit("sigprocmask");
    }

    if(sigprocmask(SIG_SETMASK, &prevMask, NULL) == -1)
    {
        errExit("sigprocmask");
    }

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = tstpHandler;
    if(sigaction(SIGTSTP, &sa, NULL) == -1)
    {
        errExit("tcgetattr");
    }

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &ourTermios) == -1)
    {
        errExit("tcsetattr");
    }

    errno = savedErrno;
}

int main(int argc, char* argv[])
{
    char ch;
    struct sigaction sa, prev;
    ssize_t n;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
}