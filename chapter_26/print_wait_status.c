#define _GNU_SOURCE
#include <string.h>
#include <sys/wait.h>
#include "print_wait_status.h"
#include "tlpi_hdr.h"

void printWaitStatus(const char* msg, int status)
{
    if (msg != NULL)
    {
        printf("%s", msg);
    }

    if (WIFEXITED(status))
    {
        printf("child exited, status=%d\n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status))
    {
        printf("child killed by signal %d (%s)", WTERMSIG(status), strsignal(WTERMSIG(status)));
        if (WCOREDUMP(status))
        {
            printf("(core dumped)");
        }
    }
    else if(WIFSTOPPED(status))
    {
        printf("child stopped by signal %d (%s)\n", WSTOPPED(status), strsignal(WSTOPPED(status));)
    }
    else if(WIFCONTINUED(status))
    {
        printf("child continued\n")
    }
    else
    {
        printf("what happended to this child? (status=%x)\n", (unsigned int) status);
    }
}