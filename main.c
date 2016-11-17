#include "main.h"


void *fnC()
{
    int i;
    for(i=0;i<1000000;i++)
    {
        c++;
    }
}


pthread_mutex_t count_mutex;
pthread_spinlock_t count_spin;
my_spinlock_t count_myspin;


void *pthreadMutexTest()
{

    int i;
	int j;
	int k;

	int localCount = 0;

    for(i=0;i<numItterations;i++)
    {

		for(j=0;j<workOutsideCS;j++)/*How much work is done outside the CS*/
		{
			localCount++;
		}

		pthread_mutex_lock(&count_mutex);
		for(k=0;k<workInsideCS;k++)/*How much work is done inside the CS*/
		{
			c++;
		}
		pthread_mutex_unlock(&count_mutex);

    }


}

void *pthreadSpinTest()
{
  int i;
	int j;
	int k;

	int localCount = 0;

    for(i=0;i<numItterations;i++)
    {

		for(j=0;j<workOutsideCS;j++)/*How much work is done outside the CS*/
		{
			localCount++;
		}

		pthread_spin_trylock(&count_spin);
		for(k=0;k<workInsideCS;k++)/*How much work is done inside the CS*/
		{
			c++;
		}
		pthread_spin_unlock(&count_spin);

    }
}

void *mypthreadSpinTest(){
  int i;
  int j;
  int k;

  int localCount = 0;

    for(i=0;i<numItterations;i++)
    {

    for(j=0;j<workOutsideCS;j++)/*How much work is done outside the CS*/
    {
      localCount++;
    }

    my_spinlock_lockTAS(&count_myspin);
    for(k=0;k<workInsideCS;k++)/*How much work is done inside the CS*/
    {
      c++;
    }
    pthread_spin_unlock(&count_myspin);

    }
}

int runTest(int testID)
{

/*You must create all data structures and threads for you experiments*/

if (testID == 0 || testID == 1 ) /*Pthread Mutex*/
{
	c=0;
	struct timespec start;
	struct timespec stop;
	unsigned long long result; //64 bit integer

	pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);
	int i;
	int rt;

	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{

	 if( rt=(pthread_create( threads+i, NULL, &pthreadMutexTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;
	}

	}

	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run Pthread (Mutex) Total Count: %lld\n", c);
	result=timespecDiff(&stop,&start);
	printf("Pthread Mutex time(ms): %llu\n",result/1000000);

}

if(testID == 0 || testID == 2) /*Pthread Spinlock*/
{
  c=0;
	struct timespec start;
	struct timespec stop;
	unsigned long long result; //64 bit integer

	pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);
	int i;
	int rt;

	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{

	 if( rt=(pthread_create( threads+i, NULL, &pthreadSpinTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;
	}

	}

	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run Pthread (Spin) Total Count: %lld\n", c);
	result=timespecDiff(&stop,&start);
	printf("Pthread Spin time(ms): %llu\n",result/1000000);
}

if(testID == 0 || testID == 3) /*MySpinlockTAS*/
{
  c=0;
  struct timespec start;
  struct timespec stop;
  unsigned long long result; //64 bit integer
  my_spinlock_init(&count_myspin);

  pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);
  int i;
  int rt;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i=0;i<numThreads;i++)
  {
    printf("thread %i\n",i+1);

   if( rt=(pthread_create( threads+i, NULL, &mypthreadSpinTest, NULL)) )
  {
    printf("Thread creation failed: %d\n", rt);
    return -1;
  }

  }

  for(i=0;i<numThreads;i++) //Wait for all threads to finish
  {
     pthread_join(threads[i], NULL);
  }
  clock_gettime(CLOCK_MONOTONIC, &stop);

  printf("Threaded Run Pthread (Spin) Total Count: %lld\n", c);
  result=timespecDiff(&stop,&start);
  printf("Pthread Spin time(ms): %llu\n",result/1000000);
}

/*....you must implement the other tests....*/

	return 0;
}

int testAndSetExample()
{
volatile long test = 0; //Test is set to 0
printf("Test before atomic OP:%ld\n",test);
tas(&test);
printf("Test after atomic OP:%ld\n",test);
}

int processInput(int argc, char *argv[])
{

/*testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myQueueLock*/
	/*You must write how to parse input from the command line here, your software should default to the values given below if no input is given*/
  int argcCounter = argc;
  int i = 0;
  bool numThreads_Check, numItterations_Check, testID_Check, workOutsideCS_Check,workInsideCS_Check = 0;

  for(i; i<argcCounter; i++){
    if(strcmp("-t",argv[i])==0){
      numThreads = atoi(argv[i+1]);
      numThreads_Check = 1;
    }
    else if(strcmp("-i",argv[i])==0){
      numItterations = atoi(argv[i+1]);
      numItterations_Check = 1;
    }
    else if(strcmp("-d",argv[i])==0){
      testID = atoi(argv[i+1]);
      testID_Check = 1;
    }
    else if(strcmp("-o",argv[i])==0){
      workOutsideCS = atoi(argv[i+1]);
      workOutsideCS_Check = 1;
    }
    else if(strcmp("-c",argv[i])==0){
      workInsideCS = atoi(argv[i+1]);
      workInsideCS_Check = 1;
    }
  }

	if(numThreads_Check==0) numThreads=4;
	if(numItterations_Check==0) numItterations=1000000;
	if(testID_Check==0) testID=0;
	if(workOutsideCS_Check==0) workOutsideCS=0;
	if(workInsideCS_Check==0) workInsideCS=1;

  printf("testID= %i\n",testID);

	return 0;
}


int main(int argc, char *argv[])
{
	printf("Usage of: %s -t #threads -i #Itterations -o #OperationsOutsideCS -c #OperationsInsideCS -d testid\n", argv[0]);
	printf("testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myQueueLock, \n");

	//testAndSetExample(); //Uncomment this line to see how to use TAS

	processInput(argc,argv);
	runTest(testID);
	return 0;

}
