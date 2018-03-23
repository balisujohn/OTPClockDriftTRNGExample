#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define n 10000


int main (char * argv[], int argc)
{


char vals[256];

for(int i = 0 ; i < n; i++)
{
vals[(int)cyrand()]++;
}



return 0;
}




