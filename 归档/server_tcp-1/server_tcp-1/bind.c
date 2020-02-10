#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#define  PORT 2345

int main(void)
{
	int sockfd;
	struct  sockaddr_in addr;
	int addr_len = sizeof(struct sockaddr_in);
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket created error!");
		exit(1);
	}
	else
	{
		printf("socket created successfully!\n");
		printf("socket id:%d\n", sockfd);
	}
	bzero(&addr, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockfd,(struct sockaddr*)(&addr),sizeof(struct sockaddr))<0)
	{
		perror("bind error!");
		exit(1);
	}
	else
	{
		printf("bind port successfully!\n");
		printf("local port:%d\n", PORT);
	}
	return 0;
}