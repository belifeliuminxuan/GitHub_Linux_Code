//
// Created by liuminxuan on 2020/2/12.
//

#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

#define THREADCOUNT 4
int g_noodle=0;

//定义互斥锁资源
pthread_mutex_t g_mutex;

void*  EatStart(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        g_noodle--;
        pthread_mutex_unlock(&g_mutex);
    }
    return NULL;
}
void* MakeStart(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        g_noodle++;
        pthread_mutex_unlock(&g_mutex);
    }
    return NULL;
}
int main()
{
    pthread_t eat_tid[THREADCOUNT],make_tid[THREADCOUNT];

    int i=0;
    int ret=-1;
    for (;i<THREADCOUNT;i++)
    {
        ret = pthread_create(&eat_tid[i],NULL,EatStart,NULL);
        if (ret!=0)
        {
            printf("create thread failed\n");
            return 0;
        }
        ret = pthread_create(&make_tid[i],NULL,MakeStart,NULL);
        if (ret!=0)
        {
            printf("create thread failed\n");
            return 0;
        }

    }
    for (i=0;i<THREADCOUNT;i++)
    {
        pthread_join(eat_tid[i],NULL);
        pthread_join(make_tid[i],NULL);
    }
    return 0;
}
