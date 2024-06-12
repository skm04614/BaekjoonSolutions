#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


int main(void)
{
	int N;
	scanf("%d", &N);

	unsigned long long sol = 1;
	for (int n = 1; n <= N; n++)
	{
		sol *= n;
	}
	printf("%llu", sol);





	return 0;
}