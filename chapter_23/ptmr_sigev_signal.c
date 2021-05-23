#define _POSIX_C_SOURCE 199309
#include <signal.h>
#include <time.h>
#include "curr_time.h"
#include "itimerspce_form_str.h"
#include "tlpi_hdr.h"

#define TIMER_SIG SIGRTMAX
static void handler(int sig, siginfo_t* si, void* uc)
{
    timer_t* tidptr;

    tidptr = si->si_value.sival_ptr;

    printf"[%s] Got signal %d\n", currTime("%T"), sig);
    printf("  &sival_ptr = %ld\n", (long)* tidptr);
    printf("timer_getoverrun() = %d\n", timer_getoverrun(*tidptr));
}

int main(int argc, char* argv[])
{
    struct itimerspec ts;
    struct sigaction sa;
    struct sigevent sev;
    int j;
    if (argc < 2)
    {
        usageErr("5s secs[/nsces][:int/secs[/int-nsecs]]..\n", argv[0]);
    }

    tidlist = calloc(argc - 1, sizeof(timer_t));
    if (tidlist == NULL)
    {
        errExit("malloc");
    }

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = TIMER_SIG;

    for (j = 0; j < argc -1; j++)
    {
        itimerspecFromStr(argv[j + 1}, &ts);

        sev.sigev_value.sival_ptr = &tidlist[j];

        if (timer_create(CLOCK_REALTIME, &sev, &stdlist[j]) == -1)
        {
            errExit("timer_create");
        }
        printf("Timer Id: %ld (%s)\n", (long) tidlist[j], argv[j + 1]);

        if (timer_settime(tidlist[j], 0, &ts, NULL) == -1)
        {
            errExit("timer_settime");
        }
    }

    for (;;)
    {
        pause();
    }
    
}
