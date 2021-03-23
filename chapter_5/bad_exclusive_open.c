#include <sys/stat.h>
#include <fcntl.h>

fd = open(argv[1], O_WRONLY);
if(fd != -1)
{
    printf(pid %ld file \%s\ )
}

else
{
    if(error != ENOENT)
    {
        errExit("open");
    }
    else
    {
        fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        if(df == -1)
        {
            errExit("open");

            printf("pid ")
        }
    }
}