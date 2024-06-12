#include <cstdio>

using uint = unsigned int;

uint gRecord[1000001] = { 0, 1, 2, 4 };

int main(void)
{
	for (int i = 4; i <= 1000000; i++)
	{
		gRecord[i] = (gRecord[i - 1] + gRecord[i - 2] + gRecord[i - 3]) % 1000000009;
	}

	int T = 0, n = 0;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%d", &n);
		printf("%u\n", gRecord[n]);
	}

	return 0;
}