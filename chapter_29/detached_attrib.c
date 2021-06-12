#include <pthread.h>

pthread_t thr;
pthread_attr_t atrr;
int s; 
s = pthread_attr_init(&atrr);
if (s != 0)
{
    errExit(s, "pthread_attr_init");
}

s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
if (s != 0)
{
    errExit(s, "pthread_attr_setdetachstate");
}

s = pthread_create(&thr, &artr, threadFunc, (void*) 1);
if(s != 0)
{
    errExit(s, "pthread_create");
}

s = pthread_attr_destroy(&attr);
if (s != 0)
{
    errExit(s, "pthread_attr_destory");
}