#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 50
char dump[BUFFER_SIZE];

int main(void)
{
	int fd;
	if ((fd = open("/dev/mydrv", O_RDWR)) < 0)
	{
		perror("open error");
		return -1;
	}

	if(write(fd, dump, BUFFER_SIZE) <= 0)
		fprintf(stderr, "mtest1: write failed \n");
	else
		fprintf(stderr, "mtest1: write success \n");
	sleep(3);
	if(write(fd, dump, BUFFER_SIZE) <= 0)
		fprintf(stderr, "mtest1: write failed \n");
	else
		fprintf(stderr, "mtest1: write success \n");
	return 0;
}
