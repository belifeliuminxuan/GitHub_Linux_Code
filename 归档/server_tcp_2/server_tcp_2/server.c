#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#define  Local_Port  8888
#define MAX_MESSAGE_SIZE 1024
#define MAX_CONNECT_NUM 5
char *Local_IP = "127.0.0.1";//
char SendBuffer[MAX_MESSAGE_SIZE];
char RecvBuffer[MAX_MESSAGE_SIZE];

struct Message
{
	int _Sockfd;
	int _Flag; 
	int _OnlineNum;
};
pthread_t Precv;
pthread_t Psend;
struct Message *SendMessage, *RecvMessage;
int ClientArray[MAX_CONNECT_NUM];
int OnlineNum = 0;

void Deal(int dealfd)
{
	int i,j;
	for (i=0;i<OnlineNum+1;i++)
	{
		if (ClientArray[i]==dealfd)
		{
			for (;i<OnlineNum;i++)
			{
				ClientArray[i] = ClientArray[i + 1];
			}
			printf("Current online:\n");
			for (j=0;j<OnlineNum;j++)
			{
				printf("User ID:%d\n", ClientArray[j]);
			}
		}
	}
}
void SendToClient(char *buffer, int dealfd)
{
	int i;
	for (i = 0; i < OnlineNum; i++)
	{
		if (ClientArray[i] == dealfd)
		{
			continue;
		}
		if (send(ClientArray[i], buffer, MAX_MESSAGE_SIZE, 0) == -1)
		{
			printf("Message sending failed\n");
		}
	}
	bzero(buffer, MAX_MESSAGE_SIZE);
}
void *RecvMessageFromServer(void *recvfd)
{
	int dealfd = *(int *)recvfd;
	while (1) {
		if (recv(dealfd, RecvBuffer, MAX_MESSAGE_SIZE, 0) == -1) 
		{
			printf("Message reception failed\n");
		}
		RecvMessage= (struct Message*)RecvBuffer;
		RecvMessage->_Sockfd = dealfd;
		if (RecvMessage->_Flag == 1)
		{
			OnlineNum--;
			RecvMessage->_OnlineNum = OnlineNum;
			Deal(dealfd);
			printf("ID:%d User Downline\n", dealfd);
			SendToClient(RecvBuffer, dealfd);
			close(dealfd);
			return NULL;
		}
		SendToClient(RecvBuffer, dealfd);
	}
	close(dealfd);
	return NULL;
}
void Progress()//进度条函数
{
	int i, num = 1;
	const char* pic = "|/-\\"; //简单动画特效

	printf("Loading state:\n");

	while (1)
	{
		if (101 == num)    //当num自增到101时，进度条已满。显示Loading成功信息，并跳出死循环。
		{
			printf("\nLoading success!\n");
			break;
		}

		printf("[");
		for (i = 0; i < num / 10; i++)    //当进度前进10个点时，刷新一次进度条。
			printf(">>");    //以>>充当进度条。
		printf("]");

		printf("%d%%[%c]\r", num++, pic[num % 4]);   //'\r'为回车符。
		fflush(stdout);    //清空标准输出缓冲区中多余的数据。
		usleep(80000);    //这里通过修改睡眠时间来控制进度条更新速度。

	}
}
void Menu()
{
	system("clear");
	printf("################################\n");
	printf("####Welcome To LAN Chat Room####\n");
	printf("####This Is The Server  Side####\n");
	printf("################################\n");
	Progress();
	printf("[Log in:]%s\n", system("date"));;
}
int main(int argc, char const *argv[])
{
	
	int serverfd, recvfd;
	socklen_t sockleng;
	struct sockaddr_in serveraddr, clientaddr;
	pid_t ChildID;

	if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("Failed to create server socket\n");
		exit(0);
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(Local_Port);
	serveraddr.sin_addr.s_addr = inet_addr(Local_IP);

	if (bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) == -1)
	{
		printf("Failed to bind socket\n");
		exit(0);
	}

	if (listen(serverfd, 5) == -1)
	{
		printf("Failed to listen to socket\n");
	}

	printf("Listening Local Port:%d,Waiting for connection\n", Local_Port);

	while (1) {
		if ((recvfd = accept(serverfd, (struct sockaddr *)&clientaddr, &sockleng)) == 0)
		{
			printf("Failed to receive message\n");
			exit(0);
		}
		ClientArray[OnlineNum++] = recvfd;

		printf("User ID:%d online\n", recvfd);

		SendMessage = (struct Message *)SendBuffer;
		SendMessage->_Sockfd = recvfd;
		SendMessage->_Flag = 0;
		SendMessage->_OnlineNum = OnlineNum;
		int j;
		for (j = 0; j < OnlineNum; j++) {
			if (send(ClientArray[j], SendBuffer, MAX_MESSAGE_SIZE, 0) == -1) 
			{
				printf("Message sending failed\n");
			}
		}
		bzero(SendBuffer, MAX_MESSAGE_SIZE);
		if ((pthread_create(&Precv, NULL, RecvMessageFromServer, &recvfd)) != 0)
		{
			printf("FAILED\n");
			exit(0);
		}
	}
	close(serverfd);
	return 0;
}
