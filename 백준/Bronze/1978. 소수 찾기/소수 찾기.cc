#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <cmath>


int main(void)
{
	int n;
	scanf("%d", &n);

	int val;
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &val);
		if (val <= 1)
		{
			continue;
		}

		bool is_prime = true;
		int max_j = sqrt(val) + 1;
		max_j = max_j < val - 1 ? max_j : val - 1;
		for (int j = 2; j <= max_j; j++)
		{
			if (val % j == 0)
			{
				is_prime = false;
				break;
			}
		}

		if (is_prime)
		{
			cnt++;
		}
	}

	printf("%d", cnt);

	return 0;
}