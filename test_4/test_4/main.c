#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	pid = fork();
	return 0;
}