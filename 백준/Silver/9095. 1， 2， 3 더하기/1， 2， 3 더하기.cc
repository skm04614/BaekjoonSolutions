#include <cstdio>

int gRec[12];

int main(void)
{
	gRec[1] = 1;
	gRec[2] = 2;
	gRec[3] = 4;

	for (int n = 4; n <= 11; n++)
	{
		gRec[n] = gRec[n - 1] + gRec[n - 2] + gRec[n - 3];
	}

	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++)
	{
		int n;
		scanf("%d", &n);
		printf("%d\n", gRec[n]);
	}

	return 0;
}