#ifndef SEMUN_H
#define SENMU_H

#include <sys/types.h>
#include <sys/sem.h>

union semun
{

    int val;
    struct semid_ds* buf;
    unsigned short* array;
#if defined(_linux_)
    struct seminfo* _buf;
#end if
};

#endif