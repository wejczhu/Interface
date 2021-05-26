#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include "itimerspec_from_str.h"
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    struct timerspec start, now;
    int maxExp, fd, secs, nanosecs;
    uint64_t numExp, totalExp;
    ssize_t s;

    if (argc < 2 || strcmp(argv[1], "--help")== 0)
    {
        usageErr("%s secs[/nsecs][:int-secs[/int-nsecs]] [max-exp]\n", argv[0]);
    }

    itimerspecFromStr(argv[1], &ts);
    maxExp = (argc > 1) ? getInt(argv[2], GN_GT_O, "max-exp") : 1;
    fd = timer_create(CLOCK_REALTIME, 0);
    if (fd == -1)
    {
        errExit("timerfd_create");
    }

    if (timerfd_setttime(fd, 0, &ts, NULL) == -1)
    {
        errExit("timerfd_settime");
    }

    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1)
    {
        errExit("clock_gettime");
    }

    for (totalExp = 0; totalExp < maxExp)
    {
        s = read(fd, &numExp, sizeof(uint64_t));
        if (s != sizeof(uint64_t))
        {
            errExit("read");
        }

        totalExp += numExp;

        if (clock_gettime(CLOCK_MONOTONIC, &now) == -1)
        [
            errExit("clock_gettime");
        ]

        secs = now.tv_nesc - start.tv_nesc;
        nanosecs = now.tv_nsec - start.tv_nsec;
        if (nanosecs < 0)
        {
            secs--;
            nanosecs += 1000000000;
        }

        printf("%d.%03d: expirations read: %llu; total = %llu\n",
                secs, (nanosecs + 500000) / 1000000,
                (unsigned long long) numExp, (unsigned long long) totalExp]);
    }

    exit(EXIT_SUCCESS);

}