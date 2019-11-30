#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8888
char *IP = "127.0.0.1";
//char *IP = "192.168.0.232";
int main()
{
	int listenfd, recvfd;
	struct sockaddr_in serveraddr, clientaddr;
	int clientaddr_len, recv_len;
	char recvBuffer[1024];
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = inet_addr(IP);
	if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) 
	{
		printf("Bind Error!\n");
		exit(1);
	}
	if (listen(listenfd, 10) == -1) {
		printf("Listen Error!\n");
		exit(1);
	}
	clientaddr_len = sizeof(struct sockaddr);
	while (1) {
		recvfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddr_len);
		printf("Already received ID:%d\n", recvfd);
		while (1)
		{
			if ((recv_len = recv(recvfd, recvBuffer, 1024, 0)) == -1)
			{
				printf("Message receiving Error!\n");
			}
			printf("%s", recvBuffer);
		}
	}
	close(recvfd);
	return 0;
}