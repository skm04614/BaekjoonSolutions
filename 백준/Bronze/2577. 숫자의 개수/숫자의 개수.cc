#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int CNT[10];

int main(void)
{
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	int num = a * b * c;
	while (num)
	{
		CNT[num % 10]++;
		num /= 10;
	}

	for (int n = 0; n < 10; n++)
	{
		printf("%d\n", CNT[n]);
	}
	
	return 0;
}