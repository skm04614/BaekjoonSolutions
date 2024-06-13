#include <cstdio>

int gRecord[1500002];

int main(void)
{
	int N;
	scanf("%d", &N);

	int t = 0, p = 0;
	int max = 0;
	int sol = 0;
	for (int t0 = 1; t0 <= N; t0++)
	{
		scanf("%d %d", &t, &p);
		max = max > gRecord[t0] ? max : gRecord[t0];
		if (t0 + t > N + 1) continue;

		gRecord[t0 + t] = gRecord[t0 + t] > max + p ? gRecord[t0 + t] : max + p;
		sol = sol > gRecord[t0 + t] ? sol : gRecord[t0 + t];
	}
	printf("%d", sol);

	return 0;
}