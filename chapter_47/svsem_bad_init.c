#include <sys/sem.h>
#include <sys/types.h>
#include "semun.h"

semid = semget(key, 1, IPC_CREAT | IPC_EXCL | perms);

if(semid != -1)
{
    union semun arg;

    arg.val = 0;
    if(semctl(semid, 0, SETVAL, arg) == -1)
    {
        errExit("semctl");
    }

}
else
{
    if(errno != EEXIST)
    {
        errExit("semget");
    }
    semid = semget(key, 1, perms);
    if(semid == -1)
    {
        errExit("semget");
    }
}

sops[0].sem_op = 1;
sops[0].sem_num = 0;
sops[0].sem_flg = 0;
if(semop(semid, sops, 1) == -1)
{
    errExit("semop");
}