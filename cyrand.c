#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define upper 100
#define lower 10
#define quality 100

long getTime()
{
	struct timespec ts;
	timespec_get(&ts,TIME_UTC);
	long elapsed = ts.tv_nsec;
}


long timeDiff()
{
	long start = getTime();
        int  cycleTime = rand() % ((upper*2) + 1 - lower) + lower;
	for(int c = 0; c < cycleTime; c++)__asm__("");
	long end = getTime();
	end -= start;
	assert(end !=  0);
	return end;
}

char collapseLong(long l,int pos)
{
unsigned long local = (unsigned long)l;
int longBitSize = sizeof(unsigned long) * 8;
for(int i = 1; i < longBitSize; i++)
{
local = local ^ (local >> (longBitSize - i )); 
}
char val = (char)(local << pos);

}




char randByte()
{
	char value = 0;
	for(int i =0; i < 8;  i ++)
	{
		for(int c = 0; c < quality; c++)
		{
		value = value ^ collapseLong(timeDiff(), i);
		}

	}
	return value;
}





/*

int main (char * argv[], int argc)
{




for(;;)
{
char t = randByte();
printf("%c", t);
}
	return 0;
}



*/
