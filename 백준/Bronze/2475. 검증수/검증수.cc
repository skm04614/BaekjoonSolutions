#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


int main(void)
{
	int n = 0;
	for (int i = 0; i < 5; i++)
	{
		int val;
		scanf("%d", &val);
		n += val * val;
	}
	printf("%d", n % 10);
	
	return 0;
}