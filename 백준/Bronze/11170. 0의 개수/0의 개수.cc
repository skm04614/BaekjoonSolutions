#include <cstdio>

int N, M, T;

int main(void)
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &T);

	auto result = 0llu;
	for (int i = 0; i < T; i++)
	{
		scanf("%d %d", &N, &M);
		result = 0;
		for (int i = N; i <= M; i++)
		{
			int tmp = i;
			do
			{
				result += !(tmp % 10);
				tmp /= 10;
			} while (tmp);
		}
		printf("%llu\n", result);
	}

	return 0;
}