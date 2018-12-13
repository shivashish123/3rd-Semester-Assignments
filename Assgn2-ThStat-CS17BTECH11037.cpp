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
double mean;				//stores median of input array
double standard_deviation;	//stores standard deviation of input array
double median;				//stores median of input array
int n;
double a[50000005];				//input array
void *mean_func(void *param)	// thread for computing mean
{
	int i;
	double sum=0;
	for(i=0;i<n;i++)
		sum+=a[i];
	mean=sum/n;
	pthread_exit(0);
}
void *median_func(void *param)	// thread for computing median
{
	if(n&1)
		median=a[n/2];
	else
	{
		median=(a[n/2]+a[(n/2)-1])*1.0/2.0;
	}
	pthread_exit(0);
}
void *deviation_func(void *param)	//thread for computing standard deviation
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
	double h=s/n;
	standard_deviation=sqrt(h);
	pthread_exit(0);
}
int main()
{

	cin>>n;
	struct timeval start,end;
	for(int i=0;i<n;i++)
		cin>>a[i];
	pthread_t tid[3];/* the thread identifier */
	pthread_attr_t attr;/* set of thread attributes */
	pthread_attr_init(&attr);/* getting the default attributes */
	gettimeofday(&start,NULL);//storing the start time
	sort(a,a+n);
	pthread_create(&tid[0],&attr,mean_func,NULL);
	pthread_create(&tid[1],&attr,median_func,NULL);		// thread creation
	pthread_create(&tid[2],&attr,deviation_func,NULL);
	int j;
	for(j=0;j<3;j++)
		pthread_join(tid[j],NULL);	/* wait for the thread to exit */
	gettimeofday(&end,NULL);//storing end time
	double t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000.0;
	printf("The average value is : %lf\nThe standard deviation value is: %lf\nThe median value is: %lf\n",mean,standard_deviation,median);
	//printf("Elapsed time : %lf milli-seconds\n",t);
	//uncomment the above line to print execution time
	return 0;
}