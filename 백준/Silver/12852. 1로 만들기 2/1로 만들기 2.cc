#include <cstdio>

int gDP[1000001];
int gFrom[1000001];

const int min(const int& n, const int& m)
{
	return n < m ? n : m;
}

int main(void)
{
	gDP[1] = 0;
	gFrom[1] = 0;

	int n;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++)
	{
		gDP[i] = gDP[i - 1];
		gFrom[i] = i - 1;

		if (i % 3 == 0 && gDP[i / 3] < gDP[i])
		{
			gDP[i] = gDP[i / 3];
			gFrom[i] = i / 3;
		}

		if (i % 2 == 0 && gDP[i / 2] < gDP[i])
		{
			gDP[i] = gDP[i / 2];
			gFrom[i] = i / 2;
		}
		gDP[i]++;
	}

	printf("%d\n", gDP[n]);
	while (n)
	{
		printf("%d ", n);
		n = gFrom[n];
	}
}