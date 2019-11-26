//server_tcp.c
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
	int fd, rw_fd;
	int ret;
	char buf[128] = { 0 };
	struct sockaddr_in myaddr;
	fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd<0)
	{
		printf("creat socket failure\n");//
		return -1;
	}
	printf("fd=%d\n", fd);

	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(8888);
	myaddr.sin_addr.s_addr = inet_addr("192.168.1.34");
	ret = bind(fd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr));

	if (ret<0)
	{
		printf("Bind error!\n");
		return -2;
	}
	listen(fd, 5);
	printf("accept before\n");
	rw_fd = accept(fd, NULL, NULL);
	printf("accept after\n");
	read(rw_fd, buf, 128);
	printf("recv from %s", buf);
	return 0;
}