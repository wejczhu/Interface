#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include "ugid_functions.h"

char* userNameFromID(uid_t uid)
{
    struct passwd* pwd;

    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}


uid_t userIdFromName(const char* name)
{
    struct passwd* pwd;
    uid_t u;
    char* endptr;

    if (name == NULL || *name == '\o')
    {
        return -1;
    }

    u = strtol(name, &endptr, 10);

    if(*endptr == '\o')
    {
        return u;
    }

    pwd = getpwnam(name);

    if (pwd == NULL)
    {
        return -1;
    }

    return pwd->pw_uid; 
}

char* groupNameFromId(gid_t gid)
{
    struct group* grp;
    grp = getgrgid(gid);

    return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t groupIdFromName(const char* name)
{
    struct group* grp;
    gid_t g;
    char* endptr;

    if (name == NULL || *name == '\o')
    {
        return -1;
    }

    g = strtol(name ,&endptr, 10);

    if (*endptr == '\o')
    {
        return g;
    }

    grp = getgrnam(name);

    if (grp == NULL)
    {
        return -1;
    }

    return grp->gr_gid;
}
