#include <cstdio>

int gRec[1000001];

int main(void)
{
	int N{};
	scanf("%d", &N);

	gRec[1] = 0;
	for (int i = 2; i <= N; i++)
	{
		gRec[i] = gRec[i - 1] + 1;

		if (i % 2 == 0 && gRec[i / 2] + 1 < gRec[i])
		{
			gRec[i] = gRec[i / 2] + 1;
		}

		if (i % 3 == 0 && gRec[i / 3] + 1 < gRec[i])
		{
			gRec[i] = gRec[i / 3] + 1;
		}
	}

	printf("%d", gRec[N]);

	return 0;
}