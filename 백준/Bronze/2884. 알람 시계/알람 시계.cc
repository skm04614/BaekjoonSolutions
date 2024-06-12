#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int HR;
int MIN;

int main(void)
{
	scanf("%d %d", &HR, &MIN);

	MIN -= 45;
	if (MIN < 0)
	{
		MIN += 60;
		HR -= 1;
	}

	if (HR < 0)
	{
		HR += 24;
	}

	printf("%d %d", HR, MIN);

	return 0;
}