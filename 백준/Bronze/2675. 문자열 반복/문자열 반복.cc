#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

char BUF[30];

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++)
	{
		int n;
		scanf("%d %s", &n, BUF);
		char* ptr = BUF;
		for (; *ptr; ptr++)
		{
			for (int i = 0; i < n; i++)
			{
				printf("%c", *ptr);
			}
		}
		printf("\n");

	}

	return 0;
}