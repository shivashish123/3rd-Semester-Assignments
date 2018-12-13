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
#include <sys/wait.h>
int main(int argc, char** argv)
{
	pid_t pid;
	double t;
	const int SIZE=4096;	/* the size (in bytes) of shared memory object */
	const char *name="OS1";	/* name of the shared memory object */
	char *s=argv[1];  // command to execute
	int shm_fd;			/* shared memory file descriptor */
	struct timeval *ptr; /* pointer to shared memory obect */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); /* create the shared memory object */
	ftruncate(shm_fd, SIZE);	/* configure the size of the shared memory object */
	ptr=(struct timeval *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); /* memory map the shared memory object */
	pid=fork();
	if (pid < 0) { /* error occurred */
	fprintf(stderr, "Fork Failed");
	return 1;
	}
	else if(pid==0) // child process
	{
		struct timeval start;
		gettimeofday(&start,NULL);	//start time of execution of command
		ptr->tv_sec=start.tv_sec;	//storing start time of execution of command
		ptr->tv_usec=start.tv_usec;
		execlp(s,s,NULL);
	}
	else		// parent process
	{
		struct timeval end;
		wait(NULL);
		gettimeofday(&end,NULL);	//end time of execution of command
		t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (ptr->tv_sec * 1000000 + ptr->tv_usec)) / 1000.0;
		printf("Elapsed time : %lf milli-seconds\n",t);
		shm_unlink(name);
	}
}