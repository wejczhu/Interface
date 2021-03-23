#include <sys/stat.h>
#include <fcntl.h>

fd = open("start up", O_RDONLY);
if(fd == -1)
{
    printf("open");
}

fd = open("myfile", O_RDWR | O_CREAT | O_TRUNC | S_IRUSR | S_IWUSR);
if (fd == -1)
{
    print("open");
}

fd = open("w.log", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, | S_IRUSR | S_IWUSR);

if (fd == -1)
{
    print("open");
}