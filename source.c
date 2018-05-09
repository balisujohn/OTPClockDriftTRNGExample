#include<stdio.h>
#include<stdlib.h>
#include<cyrand.h>
#include<time.h>
#include<unistd.h>

#define bufferLength 100000
int main (int arcgc, char * argv)
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


	return 0;
}
