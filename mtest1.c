#include <stdio.h>
#include <fcntl.h>

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

	write(fd, dump, BUFFER_SIZE);
	sleep(3);
	write(fd, dump, BUFFER_SIZE);
}