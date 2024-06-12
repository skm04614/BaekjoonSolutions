#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int CNT[42];

int main(void)
{
	int sol = 0;
	for (int i = 0; i < 10; i++)
	{
		int val;
		scanf("%d", &val);

		if (CNT[val % 42] == 0)
		{
			sol++;
		}
		CNT[val % 42]++;
	}

	printf("%d", sol);

	return 0;
}