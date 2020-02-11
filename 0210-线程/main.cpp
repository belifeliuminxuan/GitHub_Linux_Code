#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//»ÆÅ£ÇÀÆ±
//4¸ö»ÆÅ£

#define THREADCOUNT 4
int g_tickets = 100;

typedef struct ThreadPara
{
	int threadId;
}TP;
void* threadStart(void* arg)
{
	TP* tp = (TP*)arg;
	while (1)
	{
		if (g_tickets)
		{
			printf("i am thread[%d],i have ticket is[%d]\n",tp->threadId, g_tickets);
			g_tickets--;
		}
		else
		{
			break;
		}
	}
	return NULL;
}
int  main()
{
	pthread_t tid[THREADCOUNT];
	for (int i=0;i<THREADCOUNT;i++)
	{
		usleep(2000);
		//TP* tp = (TP*)malloc(sizeof(TP));
		TP* tp = new TP;
		tp->threadId = i;
		pthread_create(&tid[i], NULL, threadStart, (void*)tp);
	}
	for (int i=0;i<THREADCOUNT;i++)
	{
		pthread_join(tid[i], NULL);
	}
	getchar();
	return 0;
}