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

	sleep(1);
	if(read(fd, dump, BUFFER_SIZE) <= 0)
		fprintf(stderr, "mtest1: write success");
	else
		fprintf(stderr, "mtest1: write failed");
	sleep(2);
	if(read(fd, dump, BUFFER_SIZE) <= 0)
		fprintf(stderr, "mtest1: write success");
	else
		fprintf(stderr, "mtest1: write failed");
	return 0;
}
