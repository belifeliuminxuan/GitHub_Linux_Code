

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct Student
{
	char _name[20];
	char _schoolnumber[20];
}Student;
#if 0
int Input()
{
	int length = 0;
	printf("Please input the length of your student number£º\n");
	scanf("%d", &length);
	Student* add = (Student*)malloc(sizeof(Student));
	printf("Please enter your name:\n");
	scanf("%c", add->_name);
	printf("Please enter your student number:\n");
	scanf("%c", add->_schoolnumber);
	return 0;
}
#endif
int main()
{
	int fd;
	int wr_length = 0;
	char flag[1];
	//int length = 0;
	fd = open("schoolnumber.txt", O_CREAT | O_RDWR, 0777);
	if (fd < 0)
	{
		printf("open file schoolnumber.txt failuse!\n");
		return -1;
	}
	printf("open file schoolnumber.txt success!\n");

	//printf("Please input the length of your student number£º\n");
	//scanf("%d", &length);
	Student* add = (Student*)malloc(sizeof(Student));
	while (flag[1] != 'n')
		printf("Please enter your name:\n");
	scanf("%s", add->_name);
	//sleep(10);
	printf("Please enter your student number:\n");
	scanf("%s", add->_schoolnumber);
	printf("start write,please wait...\n");
	wr_length = write(fd, add->_name, sizeof(add));
	wr_length = write(fd, add->_schoolnumber, sizeof(add));
	printf("Do you want to continue typing?(y/n)\n");
	scanf("%c", &flag);
}

printf("write to file schoolnumber.txt success!\n");
printf("wr_length=[%d]\n", wr_length);
close(fd);
 /*if (wr_length)
{
	printf("write to file schoolnumber.txt success!\n");
	printf("wr_length=[%d]\n", wr_length);
	close(fd);
}
else
{
	printf("write to file schoolnumber.txt failure,Exit in 5 seconds\n");
	sleep(5);
	return -1;
}
*/

return 0;
}