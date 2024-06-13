#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
char POOL[100010];
int CNT[10];

int main(void)
{
	scanf("%s", POOL);
	bool hasZero = false;
	int sum = 0;
	for (int i = 0; POOL[i]; i++)
	{
		CNT[POOL[i] - '0']++;
		sum += POOL[i] - '0';
	}

	if (sum % 3 == 0 && CNT[0])
	{
		for (int n = 9; n >= 0; n--)
		{
			for (int i = 0; i < CNT[n]; i++)
			{
				printf("%d", n);
			}
		}
	}
	else
	{
		printf("-1");
	}

	return 0;
}