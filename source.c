#include<stdio.h>
#include<stdlib.h>
#include<cyrand.h>
#include<time.h>
int main (int arcgc, char * argv)
{

srand(time(0));

for (;;)
{
char c = randByte();
printf("%c", c);
}


return 0;
}
