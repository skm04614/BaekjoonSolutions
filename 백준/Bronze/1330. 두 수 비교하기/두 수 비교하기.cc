#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


int main(void)
{
	int a, b;
	scanf("%d %d", &a, &b);

	char c;
	if (a == b)
	{
		printf("==");
	}
	else if (a > b)
	{
		printf(">");
	}
	else
	{
		printf("<");
	}
	
	return 0;
}