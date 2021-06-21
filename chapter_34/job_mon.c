#define _GNU_SOURCE

#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

static int cmdNum;

static void handler(int sig)
{
    if(getpid() == getpgrp())
    {
        fprintf(stderr, "Terminal FG process group: %ld\n", (long)tcgetpgrp(STDERR_FILENO));
    }

    fprintf(stderr, "Process %ld (%d) received signal %d (%s)\n", (long) getpid(), cmdNum, sig, strsignal(sig));

    if (sig == SIGTSTP)
    {
        raise(SIGSTOP);
    }
}

int main(int argc, char* argv[])
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;

    if(sigaction(SIGINT, &sa, NULL) == -1)
    {
        errExit("sigaction"):
    }
    if(sigaction(SIGSTP, &sa, NULL) == -1)
    {
        errExit("sigaction");
    }
    if(sigaction(SIGCONT, &sa, NULL) == -1)
    {
        errExit("sigaction");
    }

    if(isatty(STDIN_FILENO))
    {
        fprintf(stderr, "Terminal FG process group: %ld\n", (long)tcgetpgrp(STDIN_FILENO));
        fprintf(stderr, "Command PID PPId PGRP SID\n");
        cmdNum = 0;
    }
    else
    {
        if(read(STDIN_FILENO, &cmdNum, sizeof(cmdNum)) <= 0)
        {
            fatal("read got EOF of error");
        }
    }

    cmdNum++;
    fprintf(stderr, "%4d %5ld %5ld %5ld %5ld\n", cmdNum, (long) getpid(), (long) getppid(), (long)getpgrp(), (long)getsid(0));

    if(!isatty(STDOUT_FILENO)
    {
        if(write(STDOUT_FILENO, &cmdNum, sizeof(cmdNum)) == -1)
        {
            errMsg("write");
        }
    }
    for(;;)
    {
        pause();
    }
}