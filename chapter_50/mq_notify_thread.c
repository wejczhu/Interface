#include <pthread.h>
#include <mqueue.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

static void notifySetup(mqd_t * mqdp);

static void threadFunc(union sigval sv)
{
    ssize_t numRead;
    mqd_t* mqdp;
    void* buffer;
    struct mq_attr attr;

    mqdp = sv.sival_ptr;
    if(mq_getattr(*mqdp, &attr) == -1)
    {
        errExit("mq_getattr");
    }

    buffer = malloc(attr.mq_msgsize);
    if(buffer == NULL)
    {
        errExit("malloc");
    }

    notifySetup(mqdp);
    while((numRead = mq_receive(*mqdp, buffer, attr.mq_msgsize, NULL)) >= 0)
    {
        printf("Read %ld bytes\n", (long)numRead);
    }

    if(errno != EAGAIN)
    {
        errExit("mq_receive");
    }

    free(buffer);
    pthread_exit(NULL);
}

static void notifySetup(mqd_t* mqdp)
{
    struct sigevent sev;
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = threadFunc;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_value.sival_ptr = mqdp;

    if(mq_notify(*mqdp, &sev) == -1)
    {
        errExit("mq_notify");
    }

    int main(int argc, char* argv[])
    {
        mqd_t mqd;
        if(argc != 2 || strcmp(argv[1], "--help") == 0)
        {
            usageErr("%s mq-name\n", argv[0]);
        }

        mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);
        if(mqd == (mqd_t) -1)
        {
            errExit("mq_open");
        }

        notifySetup(&mqd);
        pause();
    }
}