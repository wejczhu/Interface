#define _GNU_SOURCE

#include <string.h>
#include <signal.h>
#include "tlpi_hdr.h"

static void handler(int sig)
{
    printf("PID=%ld, caught signal %d (%s)\n", (long) getpid(), sig, strsignal(sig));
}

int main(int argc, char* argv[])
{
    int j;
    struct sigaction sa;

    if(argc < 2 || strcmp(argv[1]m "--help") == 0)
    {
        usageErr("%s {s|p} ...\n", argv[0]);
    }

    setbuf(stdout, NULL);

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if(sigaction(SIGHUP, &sa, NULL) == -1)
    {
        errExit("sigaction");
    }

    if(sigaction(SIGCONT, &sa, NULL) == -1)
    {
        errExit("sigaction");
    }

    printf("parent: PID = %ld, PPID=%ld, PGID=%ld, SID=%ld\n", (long)getpid(), (long)getppid(), (long)getpgrp(), (long)getsid(0));

    for(j = 1; j < argc; j++
    {
        
    }

}
