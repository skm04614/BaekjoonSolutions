#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int H, W, N;

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++)
	{
		scanf("%d %d %d", &H, &W, &N );
		printf("%d\n", (1 + ((N - 1) % H)) * 100 + ((N - 1) / H) + 1);


	}

	return 0;
}