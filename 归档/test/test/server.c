#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#define PORT 8888
char *IP = "127.0.0.1";
//char *IP="192.168.0.232";

int main(int argc, char const *argv[])
{
	int sendfd, recvfd;
	struct sockaddr_in serveraddr, clientaddr;
	char recvBuffer[1024];
	sendfd = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = inet_addr(IP);
	if (bind(sendfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
	{
		printf("Bind Error!\n");
		exit(0);
	}
	if (listen(sendfd, 10) == -1) 
	{
		printf("Listen Error!\n");
		exit(0);
	}
	while (1) 
	{
		recvfd = accept(sendfd, (struct sockaddr *)&clientaddr, sizeof(struct sockaddr));
		printf("Accept:%d\n", recvfd);

		while (1) 
		{
			if ((recv(recvfd, recvBuffer, 1024, 0)) == -1) 
			{
				printf("Receive Error!\n");
			}
			printf("%s", recvBuffer);
		}
	}
	close(recvfd);
	return 0;
}