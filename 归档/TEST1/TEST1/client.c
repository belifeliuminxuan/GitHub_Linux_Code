#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define PORT 8888
char *IP = "127.0.0.1";
//char *IP = "192.168.0.232";

int main()
{
	int clientfd;
	struct sockaddr_in clientaddr;
	char sendBuffer[1024], recvBuffer[1024];
	if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf("Created Error!\n");
		exit(1);
	}
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_addr.s_addr = inet_addr(IP);
	clientaddr.sin_port = htons(PORT);

	if (connect(clientfd, (struct sockaddr *)&clientaddr, sizeof(struct sockaddr)) == -1) 
	{
		printf(stderr, "Connect Error!\n");
		exit(1);
	}
	if (send(clientfd, sendBuffer, 1024, 0) == -1)
	{
		printf("Send Eeror!\n");
		exit(1);
	}
	while (1) {
		fgets(sendBuffer, 1024, stdin);
		if (send(clientfd, sendBuffer, 1024, 0) == -1) 
		{
			fprintf("Send Message Error!\n");
			exit(1);
		}
	}
	close(clientfd);
	return 0;
}
