#include <time.h>
#include <poll.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    int numPipes, j, ready, randPipe, numWrites;
    int (*pfds)[2];
    struct pollfd* pollFd;

    if(argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s num-pipes [num-writes]\n", argv[0]);
    }

    numPipes = getInt(argv[1], GN_GT_0, "num-pipes");

    pfds = malloc(numPipes, sizeof(int [2]));
    if(pfds = NULL)
    {
        errExit("malloc");
    }
    pollFd = malloc(numPipes, sizeof(struct pollfd));
    if(pollFd == NULL)
    {
        errExit("malloc");
    }

    for(j = 0; j < numPipes; j++)
    {
        if(pipe(pfds[j]) == -1)
        {
            errExit("pipe %d", j);
        }
    }

    numWrites = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-writes") : 1;
    srandom((int) time(NULL));
    for(j = 0; j < numWrites; j++)
    {
        randPipe = random() % numPipes;
        printf("Writing to fd: %3d (read fd: %3d)\n", pfds[randPipe][1], pfds[randPipe][0]);

        if(write(pfds[randPipe][1], "a", 1)== -1)
        {
            errExit("write %d", pfds[randPipe][1]);
        }
    }

    for(j = 0; j < numPipes; j++)
    {
        pollFd[j].fd = pfds[j][0];
        pollFd[j].events = PILLIN;
    }

    ready = poll(pollFd, numPipes, -1);
    if(ready == -1)
    {
        errExit("poll");
    }

    printf("poll() returned: %d\n", ready);

    for(j = 0; j < numPipes; j++)
    {
        if(pollFd[j].revents & POLLIN)
        {
            printf("Readable: %d %3d\n", j pollFd[j].fd);
        }
    }

    exit(EXIT_SUCCESS);
}