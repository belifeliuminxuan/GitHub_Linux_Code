#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{

  int fd;
  fd=open("test.txt",O_CREAT|O_RDWR|O_APPEND,0777);
  char buffer[]="helloworld"; 
  int length;
  length = write(fd,buffer,sizeof(buffer));
  return 0;
}
