#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<cyrand.h>


#define n 100000


int main (char * argv[], int argc)
{

	int vals[256];


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
		printf("OCCURENCES: %d CHARACTER:%c\n",vals[i],(char)i);

	}


	return 0;
}




