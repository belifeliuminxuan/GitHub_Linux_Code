#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <cstdio>
#include <iostream>
#define THREADCOUNT 1
#define SIZE 4
class RingQueue
{
public:
	RingQueue()
		:Vec_(SIZE)
	{
		Capacity = SIZE;
		PosWrite_ = 0;
		PosRead_ = 0;
		//初始化同步信号量
		//生产的时候看数组大小
		sem_init(&ProSem_, 0, SIZE);
		//消费者初始化的时候是看当前有多少资源可以消费
		sem_init(&ConSem_, 0, 0);
		//初始化互斥
		sem_init(&LockSem_, 0, 1);
	}
	~RingQueue()
	{
		sem_destroy(&ProSem_);
		sem_destroy(&ConSem_);
		sem_destroy(&LockSem_);
	}
	void Push(int& Data)
	{
		sem_wait(&ProSem_);
		sem_wait(&LockSem_);
		
		Vec_[PosWrite_] = Data;
		PosWrite_ = (PosWrite_ + 1) % Capacity;
		sem_post(&LockSem_)-;
		sem_post(&ConSem_);
		
	}
	void Pop(int* Data)
	{
		sem_wait(&ConSem_);
		sem_wait(&LockSem_);
		*Data = Vec_[PosRead_];
		PosRead_ = (PosRead_ + 1) % Capacity;
		sem_post(&LockSem_);
		sem_post(&ProSem_);
	}
private:
	std::vector<int> Vec_;
	size_t Capacity;
	int PosWrite_;
	int PosRead_;
	//同步
	sem_t ProSem_;//生产者的信号量
	sem_t ConSem_;
	//互斥
	sem_t LockSem_;
	
};

void* ProStart(void* arg)
{

	return nullptr;
}
void* ConStart(void* arg)
{
	
	return nullptr;
}

int main()
{
	pthread_t Pro_tid[THREADCOUNT], Con_tid[THREADCOUNT];
	int i = 0;
	int ret = -1;
	RingQueue* rq = new RingQueue();
	for (;i<THREADCOUNT;i++)
	{
		ret = pthread_create(&Pro_tid[i], ProStart, (void*)rq);
		if (ret!=0)
		{
			
		}
		ret = pthread_create(&Con_tid[i], ConStart, (void*)rq);
		if (ret != 0)
		{

		}
	}
	for (i=0;i<THREADCOUNT;i++)
	{
		pthread_join();
	}
	delete rq;
	return 0;
}