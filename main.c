//#include"unistd.h"
//#include"stdio.h"
//#include"fcntl.h"
//
//int main()
//{
//	int fd;
//	fd = open("hello.txt", O_CREAT |O_RDWR, 0777);
//	if (fd < 0)
//	{
//		printf("open file hello.txt failure,fd=%d\n", fd);
//		return-1;
//	}
//	printf("open file hello.txt success,fd=%d\n", fd);
//}


#include"unistd.h"
#include"fcntl.h"
#include"stdio.h"
#define MAX 128
int main()
{
	int fd;
	char buf[] = "abcdefghjhhhgljkljjlg";
	int wr_len = 0;
	fd = open("hello.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		printf("open a file hello.txt failure\n");
		return-1;
	}
	printf("open a file hello.txt success\n");
	fgets(buf, MAX, stdin);
	printf("start write бн");
	wr_len = write(fd, (char*)buf, sizeof(buf));
	printf("wr_len=%d\n", wr_len);
	close(fd);
}