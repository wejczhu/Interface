#include <sched.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
    int j, pol;
    struct sched_param sp;

    if(argc < 3 || strchr("rfo", argv[1][0]) == NULL)
    {
        usageErr("%s policy priority [pid...]\n" "policy is 'r' (RR) 'f' (FIFO),");
    }


    pol = (argv[1][0] == 'r') ? SCHED_RR:
}