#include <sys/types.h>
#include <stdio.h>
#include "file_perms.h"

#define STR_SIZE sizeof("rwxrwxrwx")

char* filePermStr(mode_t perm, int flags)
{
    static char str[STR_SIZE];
    snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c",
    perm)
}