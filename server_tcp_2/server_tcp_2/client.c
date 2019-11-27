#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_MESSAGE_SIZE 1024
#define Server_Port 8888
char *Server_IP = "127.0.0.1";
char SendBuffer[MAX_MESSAGE_SIZE];
char RecvBuffer[MAX_MESSAGE_SIZE];

struct Message {
	int _Sockfd; 
	int _Flag;
	int _OnlineNum;           

};
int sockfd;
struct Message *MySendMessage, *MyRecvMessage;
void *SendMessage(void *msg)
{
	while (1) {
		MySendMessage = (struct Message*)SendBuffer;
		MySendMessage->_Sockfd = sockfd;
		printf("Please Input:");
		fgets(SendBuffer + sizeof(struct Message), MAX_MESSAGE_SIZE - sizeof(struct Message), stdin);

		if (strncmp(SendBuffer + sizeof(struct Message), "end", 3) == 0)
		{   
			MySendMessage->_Flag = 1;
			if (send(sockfd, SendBuffer, MAX_MESSAGE_SIZE, 0) == -1)
			{
				printf("Message sending failed\n");
			}
			close(sockfd);
			exit(0);
		}
		else
		{
			MySendMessage->_Flag = 2;
		}

		if (send(sockfd, SendBuffer, MAX_MESSAGE_SIZE, 0) == -1) 
		{
			printf("Message sending failed\n");
		}
		bzero(SendBuffer, MAX_MESSAGE_SIZE);
	}
	return NULL;
}
void Progress()
{
	int i, num = 1;
	const char* pic = "|/-\\";
	while (1)
	{
		if (101 == num)
		{
			break;
		}

		printf("[");
		for (i = 0; i < num / 10; i++)
			printf(">>");
		printf("]");

		printf("%d%%[%c]\r", num++, pic[num % 4]);
		fflush(stdout);
		usleep(30000);

	}
}
void Menu()
{
	system("clear");
	printf("################################\n");
	printf("####Welcome To LAN Chat Room####\n");
	printf("####This Is The Client  Side####\n");
	printf("################################\n");
	printf("[Loading]\n");
	Progress();
	system("date");
}
int main(int argc, char const *argv[])
{
	int SendLen;
	struct sockaddr_in serveraddr, recvaddr;
	pthread_t Psend;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		printf("Failed to create server socket\n");
		exit(0);
	}

	bzero(&serveraddr, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(Server_IP);
	serveraddr.sin_port = htons(Server_Port);
	if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) == -1)
	{
		printf("Request connection failed\n");
	}

	printf("Successful connect to %s:%d\n", inet_ntoa(serveraddr.sin_addr), ntohs(serveraddr.sin_port));
	pthread_create(&Psend, NULL, SendMessage, NULL);
	while (1) {
		bzero(RecvBuffer, MAX_MESSAGE_SIZE);
		if (recv(sockfd, RecvBuffer, MAX_MESSAGE_SIZE, 0) == -1) 
		{
			printf("Failed to receive message\n");
		}

		MyRecvMessage = (struct Message *)RecvBuffer;
		if (MyRecvMessage->_Flag == 0) 
		{
			fprintf(stdout, "[User ID:%d Online | Current Online:%d\n]", MyRecvMessage->_Sockfd, MyRecvMessage->_OnlineNum);
		}
		else if (MyRecvMessage->_Flag == 1)
		{
			printf("[User ID:%d Offline | Current Online:%d\n]", MyRecvMessage->_Sockfd, MyRecvMessage->_OnlineNum);
		}
		else if (MyRecvMessage->_Flag == 2)
		{
			fprintf(stdout, "[User ID:%d]->[Say:]%s\n", MyRecvMessage->_Sockfd, RecvBuffer + sizeof(struct Message));
		}

	}
	return 0;
}