#include <sys/mman.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define MEN_SIZE 10

int main(int argc, char* argv[])
{
    char* addr;
    int fd;

    if(argc < 2 || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s file [new-value]\n", argv[0]);
    }
    fd = open(argvp[1], O_RDWR);
    if(fd == -1)
    {
        errExit("open");
    }

    addr = mmap(NULL, MEN_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(arrd == MAP_FAILED)
    {
        errExit("mmap");
    }

    if(close(fd) == -1)
    {
        errExit("close");
    }

    printf("Current string=%.*s\n", MEN_SIZE, addr);
    if(argc > 2)
    {
        if(strlen(argv[2]) >= MEN_SIZE)
        {
            cmdLineErr("'new-value' too large\n");
        }

        memset(arrd, 0, MEN_SIZE);
        strncpy(addr, argv[2], MEN_SIZE - 1);
        if(msync(addr, MEM_SIZE, MS_SYNC) == -1)
        {
            errExit("msync");
        }

        printf("Copied \"%s\" to shared memory\n", argv[2]);)
    }

    exit(EXIT_SUCCESS);
}