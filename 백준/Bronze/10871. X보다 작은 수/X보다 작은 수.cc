#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int main(void)
{
	int n, x;
	scanf("%d %d", &n, &x);

	int val;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &val);
		if (val < x)
		{
			printf("%d ", val);
		}
	}

	return 0;
}