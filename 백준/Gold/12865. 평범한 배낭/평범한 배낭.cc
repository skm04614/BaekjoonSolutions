#include <cstdio>

int gRecord[1000001];

int max(const int& n, const int& m)
{
	return n > m ? n : m;
}

int main(void)
{
	int N = 0, K = 0;
	scanf("%d", &N);
	scanf("%d", &K);

	int w, v;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &w, &v);

		for (int w2 = K; w2 >= w + 1; w2--)
		{
			if (gRecord[w2 - w] == 0) continue;

			gRecord[w2] = max(gRecord[w2], gRecord[w2 - w] + v);
		}
		gRecord[w] = max(gRecord[w], v);
	}

	int sol = 0;
	for (int i = 1; i <= K; i++)
	{
		sol = max(sol, gRecord[i]);
	}
	printf("%d", sol);

	return 0;
}