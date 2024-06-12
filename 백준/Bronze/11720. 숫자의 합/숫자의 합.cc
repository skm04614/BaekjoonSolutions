#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


int main(void)
{
	int n;
	scanf("%d", &n);

	int sol = 0;
	for (int i = 0; i < n; i++)
	{
		char c;
		scanf(" %c", &c);
		sol += c - '0';

	}

	printf("%d", sol);

	return 0;
}