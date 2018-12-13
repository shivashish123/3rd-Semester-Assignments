#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
int main(int argc, char** argv)
{
	pid_t pid;
	pid=fork();
	double t;
	const int SIZE=4096;
	const char *name="OS1";
	char s[1001];
	strcpy(s,argv[1]);
	if(pid==0)
	{
		int shm_fd;
		struct timeval *ptr;
		struct timeval start;
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
		ftruncate(shm_fd, SIZE);
		ptr = (struct timeval *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
		gettimeofday(&start,NULL);
		ptr->tv_sec=start.tv_sec;
		ptr->tv_usec=start.tv_usec;
		execlp(s,"ls",NULL);
	}
	else
	{
		struct timeval end;
		wait(NULL);
		gettimeofday(&end,NULL);
		int shm_fd;
		struct timeval *ptr;
		shm_fd = shm_open(name, O_RDONLY, 0666);
		ptr=(struct timeval *)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (ptr->tv_sec * 1000000 + ptr->tv_usec)) / 1000000.0;
		printf("%lf\n",t);
		shm_unlink(name);
	}
}