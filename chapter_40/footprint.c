pid_t chlidPid;
int status;

childPid = fork();
if(childPid == -1)
{
    errExit("fork");
}

if (childPid == 0)
{
    exit(func(arg));
}

if (wait(&status) == -1)
{
    errExit("wait");
}