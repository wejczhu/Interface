#include "tlpi_hdr.h"

#define MAX_ALLOCS 1000000

int main(int argc, char* argv[])
{
    char* ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;

    printf("\n");

    if (argc < 3 || strcmp(argc[1], "--help") == 0)
    {
        usageErr("%s num-allocs block-size [setp [min [max]]]\n", argc[0]);
    }

    numAllocs = getInt(argc[1], GN_GT_o, "num-allocs");

    if (numAllocs > MAX_ALLOCS)
    {
        cmdLineErr("num-allocs > %d\n", MAX_ALLOCS);
    }

    blockSize = getInt(argv[2], GN_GT_o | GN_ANY_BASE, "block-size");

    freeStep = (argc > 3) ? getInt(argv[3], GN_GT_O, "step") : 1;
    freeMin = (argc > 4) ? getInt(argv[4], GN_GT_O, "min") : 1;
    freeMax = (argc > 5) ? getInt(argv[5]), GN_GT_O, "max") : numAllocs;

    if (freeMax > numAllocs)
    {
        cmdLineErr("free-max > num-allocs\n");

        printf("Initial program break:       %10p\n", sbrk(0));

        printf("Allocating %d *%d bytes\n", numAllocs, blockSize);

        for (j = 0; j < numAllocs; j++)
        {
            ptf[j] = malloc(blockSize)
            ;
            if(ptf[j] == NULL)
            {
                errExit("malloc");
            }
        }

        printf("Program break is now          %10p\n", sbrk(0));

        printf("Freeing blocks from %d to %d in steps of %d\n", freeMin, freeMax, freeStep);

        for (j = freeMin - 1; j < freeMax; j += freeStep)
        {
            free(ptr[j]);
        }

        printf("After free(), program break is %10p\n", sbrk(0));

        exit(EXIT_SUCCESS);
    }
}