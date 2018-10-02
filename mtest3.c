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

	sleep(2);
	read(fd, dump, BUFFER_SIZE);
}