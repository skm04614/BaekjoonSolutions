#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <string>

int main(void)
{
	int T;
	scanf("%d", &T);

	for (int t = 1; t <= T; t++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		printf("Case #%d: %d + %d = %d\n", t, a, b, a + b);
	}
	
	return 0;
}