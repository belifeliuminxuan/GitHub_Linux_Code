#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
//��ţ��Ʊ����
//4����ţ��100��Ʊ
//��ţA, ��ţB, ��ţC, ��ţD
//1        2      3     4
//5       6       7     8
//��ţ���߳�������
//100Ʊ��ȫ�ֱ�������ʾ

//g_tickets���ٽ���Դ
int g_tickets = 100;
#define THREADCOUNT 4
//���廥��������
pthread_mutex_t g_mutex;

typedef struct ThreadPara
{
	int ThreadId_;
	//... and so on
}TP;

void* ThreadStart(void* arg)
{
	TP* tp = (TP*)arg;
	while (1)
	{
		//2
		pthread_mutex_lock(&g_mutex);
		if (g_tickets > 0)
		{
			usleep(1000);
			printf("i am thread[%d], i am ticket is [%d]\n", tp->ThreadId_, g_tickets);
			g_tickets--;
		}
		else
		{
			pthread_mutex_unlock(&g_mutex);
			delete tp;
			tp = NULL;
			break;
		}
		pthread_mutex_unlock(&g_mutex);
	}
	return NULL;
}

int main()
{
	//�̴߳���֮ǰ����ʼ������������
	pthread_mutex_init(&g_mutex, NULL);
	pthread_t tid[THREADCOUNT];
	int i = 0;
	for (; i < THREADCOUNT; i++)
	{
		TP* tp = new TP;
		tp->ThreadId_ = i;
		pthread_create(&tid[i], NULL, ThreadStart, (void*)tp);
	}

	for (i = 0; i < THREADCOUNT; i++)
	{
		pthread_join(tid[i], NULL);
	}
	//���ٻ���������
	pthread_mutex_destroy(&g_mutex);
	getchar();
	return 0;
}
