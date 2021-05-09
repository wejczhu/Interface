#include <sys/inotify.h>
#include <limits.h>
#include "tlpi_hdr.h"

static void displayInotifyEvent(struct inotify_event* i)
{
    printf("  wd = %2d; ", i->wd);
    if(i->cookie > 0)
    {
        printf("cookie  =%4d", i->cookie);
    }

    printf("mask = ");

    if(i -> mask & IN_ACCESS)
    {
        printf("in_access");
    }
    if(i -> mask & IN_ATTRIB)
    {
        printf("in_attrib");
    }
    if(i -> mask & IN_CLOSE_NOWRITE)
    {
        printf("in_close_nowrite");
    }
    if(i -> mask & IN_CLOSE_WRITE)
    {
        printf("in_close_write");
    }
    if(i -> mask & IN_CREATE)
    {
        printf("in_create");
    }
    if(i -> mask & IN_DELETE)
    {
        printf("in_delete");
    }
    if(i -> mask & IN_DELETE_SELF)
    {
        printf("in_delete_self");
    }
    if(i -> mask & IN_IGNORED)
    {
        printf("in_ignored");
    }
    if(i -> mask & IN_ISDIR)
    {
        printf("in_isdir");
    }
    if(i -> mask & IN_MODIFY)
    {
        printf("in_modify");
    }
    if(i -> mask & IN_MOVE_SELF)
    {
        printf("in_move_self");
    }
    if(i -> mask & IN_MOVED_FROM)
    {
        printf("in_moved_from");
    }
    if(i -> mask & IN_MOVED_TO)
    {
        printf("in_moved_to");
    }
    if(i -> mask & IN_OPEN)
    {
        printf("in_open");
    }
    if(i -> mask & IN_Q_OVERFLOW)
    {
        printf("in_q_overflow");
    }
    if(i -> mask & IN_UNMOUNT)
    {
        printf("in_unmount");
    }
    printf("\n");

    if (i->len > 0)
    {
        printf("name = %s\n", i->name);
    }

}

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main(int argc, char* argv[])
{
    int inotifyFd, wd, j;
    char buf[BUF_LEN];
    ssize_t numRead;
    char* p;
    struct inotify_event* event;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s pathname ... \n", argv[0]);
    }

    inotifyFd = inotify_init();

    if (inotifyFd == -1)
    {
        errExit("inotify_init");
    }

    for (j = 1; j < argc; j++)
    {
        wd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);
        if (wd == -1)
        {
            errExit("inotify_add_watch");

            printf("Watching %s using wd %d\n", argv[j], wd);
        }
    }

    for (;;)
    {
        numRead = read(inotifyFd, buf, BUF_LEN);
        if (numRead == 0)
        {
            fatal("read() from inotify fd returned 0!");
        }

        if (numRead == -1)
        {
            errExit("read");
        }

        printf("Read %ld bytes from inotify fd\n", (long) numRead);

        for (p = buf; p < buf + numRead;)
        {
            event (struct inotify_event*) p;
            displayInotifyEvent(event);

            p += sizeof(struct inofity_event) + event->len;
        }

        exit(EXIT_SUCCESS);
    }
}