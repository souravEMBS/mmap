//This file defines the use of mmap

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	/* code */
	int fd;
	struct stat myfstat;
	void* pmap;
	char buff[128] = "This is the file to test mmap.";

	fd =  open("sample.txt",O_RDWR);

	if(fd == -1)
	{
		perror("open: ");
		exit(1);
	}

	if(write(fd,&buff,sizeof(buff)) == -1)
	{
		perror("write: ");
		close(fd);
		exit(1);
	}

	fsync(fd);

	if(fstat(fd,&myfstat)<0)
	{
		perror("fstat: ");
		close(fd);
		exit(1);
	}

	pmap = mmap(0,myfstat.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);

	if(pmap == MAP_FAILED)
	{
		perror("perror: ");
		close(fd);
		exit(1);
	}

	strncpy(pmap,"That is a file to test mmap",30);


	close(fd);

	return 0;
}

