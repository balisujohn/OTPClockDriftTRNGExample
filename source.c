#include<stdio.h>
#include<stdlib.h>
#include<cyrand.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/sysinfo.h>
#include<stdint.h>


int bufferLength = 1000;
//volatile int entropyOut = 0;


void source(int entropyCount)
{


	srand(time(0));

	char * writeBuffer = malloc(bufferLength);
	int writeIndex = 0;
	for (;;)
	{
		writeBuffer[writeIndex] = randByte();
		writeIndex++; 
		if( writeIndex == bufferLength)
		{
			write(1,writeBuffer,bufferLength);
			writeIndex = 0;
		}
	}






}

int main (int arcgc, char * argv)
{
	int procs = get_nprocs();
	pthread_t cid[procs];
	for(int i =0; i < procs; i++)
	{
		pthread_create(&cid[i], NULL, (void*)source, NULL);
	}
	for(int i =0; i < procs; i++)
	{
		pthread_join(cid[i],NULL);
	}
return 0;
}


