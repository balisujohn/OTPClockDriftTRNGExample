#include<stdio.h>
#include<stdlib.h>
#include<truerand.h>

int main(char * argv[], int argc )
{
for(int i = 0; i < 10; i++)
{
printf("%d\n", (unsigned int)truerand() );
}





return 0;
}
