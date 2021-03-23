#include <tlpi_hdr.h>

int main(int argc, char* argv[])
{
    int j;
    for (j = 0; j < argc; j++)
    {
        printf("argc[%d] = %s\n", j , argv[j]);
    }

    exit(EXIT_SUCCESS);
}