#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int CNT2;
int CNT5;

int main(void)
{
	int N;
	scanf("%d", &N);

	for (int n = 1; n <= N; n++)
	{
		int tmp = n;
		while (tmp % 2 == 0)
		{
			tmp /= 2;
			CNT2++;
		}

		while (tmp % 5 == 0)
		{
			tmp /= 5;
			CNT5++;
		}
	}

	int n_zero = CNT2 < CNT5 ? CNT2 : CNT5;
	printf("%d", n_zero);



	return 0;
}