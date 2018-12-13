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
#include <bits/stdc++.h>
using namespace std;
struct data{ //structure for storing mean,median and standard deviation
double mean;
double standard_deviation;
double median;
};
double a[50000005];//input array
int main()
{

	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	pid_t pid,pid2;
	double t;
	const int SIZE=4096;	/* the size (in bytes) of shared memory object */
	const char *name="OS1";	/* name of the shared memory object */
	int shm_fd;			/* shared memory file descriptor */
	data *ptr; /* pointer to shared memory obect */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); /* create the shared memory object */
	ftruncate(shm_fd, SIZE);	/* configure the size of the shared memory object */
	ptr=(data *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); /* memory map the shared memory object */
	struct timeval start,end;
	gettimeofday(&start,NULL);
	sort(a,a+n);
	pid=fork();	/* fork a child process */
	pid2=fork();/* fork a child process */
	if(pid==0 && pid2==0) // child process for calculating mean
	{
		int i;
		double sum=0;
		for(i=0;i<n;i++)
			sum+=a[i];
		ptr->mean=sum/n;
	}
	else if(pid>0 && pid2==0)	// child process for calculating median
	{
		if(n&1)
			ptr->median=a[n/2];
		else
		{
			ptr->median=(a[n/2]+a[(n/2)-1])/2.0;
		}
	}
	else if(pid2>0 && pid==0)	//child process for calculating standard deviation
	{
		int i;
		double temp;
		double sum=0;
		for(i=0;i<n;i++)
			sum+=a[i];
		temp=sum/n;
		double s=0;
		for(i=0;i<n;i++)
		{
			double u=a[i];
			s+=(u-temp)*(u-temp);
		}
		double h=s/(n-1);
		ptr->standard_deviation=sqrt(h);
	}
	else		// parent process
	{
		wait(NULL);
		wait(NULL);/* parent will wait for the child to complete */
		gettimeofday(&end,NULL); //storing end time of execution
		printf("The average value is : %lf\nThe standard deviation value is: %lf\nThe median value is: %lf\n",ptr->mean,ptr->standard_deviation,ptr->median);
		t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000.0;
		//printf("Elapsed time : %lf milli-seconds\n",t); 
		//uncomment the above line to print execution time
		shm_unlink(name);
	}
	return 0;
}