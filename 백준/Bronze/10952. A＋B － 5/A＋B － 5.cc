#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <string>

int main(void)
{
	for (;;)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		if (a == 0 && b == 0)
		{
			break;
		}
		printf("%d\n", a + b);
	}
	
	return 0;
}