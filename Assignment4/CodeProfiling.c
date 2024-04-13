#include<stdio.h>

int fact(int a)
{
	if(a<2)
	{
		return 1;
	}
	else
	{
		return a*fact(a-1);
	}
}

void print(int a)
{
	printf("\n%d",a);
}

void main()
{
	int a=1,b;

	for(a=1;a<=3;a++)
	{
		b=fact(a);
		print(b);
	}

	
}