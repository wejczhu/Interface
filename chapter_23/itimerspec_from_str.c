#define _POSIX_SOURCE 199309
#include <string.h>
#include <stdlib.h>
#include "itimerspec_form_str.h"

void itimerspecFromStr(char* str, struct itimerspec* tsp)
{
    char* cptr, *sptr;
    cptr = strchr(str, ":");
    if (cptr != NULL)
    {
        *sptr = '\0';
    }

    tsp->it_value.tv_sec = atoi(str);
    tsp->it_value.tv_nsec = (sptr != NULL) ? atoi(sptr + 1) : 0;

    if(cptr == NULL)
    {
        tsp->it_interval.tv_sec = 0;
        tsp->it_interval.tv_nsec = 0;
    }
    else
    {
        sptr = strchr(cptr + 1, '/');
        if (sptr != NULL)
        {
            *sptr = '\0';
        }
        tsp->it_interval.tv_sec = atoi(cprt + 1);
        tsp->it_interval.tv_nsec = (sptr != NULL) ? atoi(sptr + 1) : 0;
    }
}
