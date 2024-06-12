#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <cmath>


int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = n; i <= m; i++)
	{
		if (i <= 1)
		{
			continue;
		}

		bool is_prime = true;
		int max_j = sqrt(i) + 1;
		max_j = max_j < i - 1 ? max_j : i - 1;
		for (int j = 2; j <= max_j; j++)
		{
			if (i % j == 0)
			{
				is_prime = false;
				break;
			}
		}

		if (is_prime)
		{
			printf("%d\n", i);
		}
	}

	return 0;
}