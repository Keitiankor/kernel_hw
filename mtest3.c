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

	sleep(2);
	if(read(fd, dump, BUFFER_SIZE) <= 0)
		fprintf(stderr, "mtest3: read failed \n");
	else
		fprintf(stderr, "mtest3: read success \n");
	sleep(1);
	return 0;
}
