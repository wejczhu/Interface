#include <sys/types.h>
#include <sys/sem.h>
#include "semun.h"

int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | perms);
if(semid != -1)
{
    union semun arg;
    struct sembuf sop;

    arg.val = 0;
    if(semctl(semid, 0, SETVAL, arg) == -1)
    {
        errExit("semctl");
    }

    sop.sem_num = 0;
    sop.sem_op = 0;
    sop.sem_flg = 0;
    if(semop)semid, &sop, 1) == -1
    {
        errExit("semop");
    }

}
else
{
    const int MAX_TRIES = 10;
    int j;
    union semun arg;
    struct semid_ds ds;

    if(errno != EEXIST)
    {
        errExit("semget");
    }

    semid = semget(key, 1, perms);
    if(semid == -1)
    {
        errExit("semget");
    }

    arg.buf = &ds;
    for(j = 0; j < MAX_TRIES; j++)
    {
        if(semctl(semid, 0, IPC_STAT, arg) == -1)
        {
            errExit("semctl");
        }
        if(ds.sem_otime != 0)
        {
            break;
        }
        sleep(1);
    }

    if(ds.sem_otime == 0)
    {
        fatal("Existing semaphore not initialized");
    }
}