#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<cyrand.h>
#include<math.h>

#define n 100000


int vals[256];



double average()
{
	int sum = 0;
	for(int i = 0; i < 256; i++)
	{
		sum += vals[i]; 
	}
	return ((double)sum)/256.0;
}


double stDEV()
{
	double std = 0.0;
	double avg = average();
	for(int i = 0; i < 256; i++)
	{
		std +=  ((double)vals[i]-avg) *  ((double)vals[i]-avg);
	}
	return sqrt(std/256.0);
}


double variance()
{
return stDEV() * stDEV();
}




int main (char * argv[], int argc)
{


	for(int i = 0; i < 256; i++)
	{
		vals[i] = 0;

	}
	for(int i = 0 ; i < n; i++)
	{
		vals[(unsigned char)randByte()]++;
	}



	for(int i = 0; i < 256; i++)
	{
		printf("CHARACTER:%c OCCURENCES: %d\n",(char)i,vals[i]);

	}

	printf("AVERAGE: %f\n", average());
	printf("STANDARD DEVIATION: %f\n", stDEV());
	printf("VARIANCE: %f\n", variance());


	return 0;
}




