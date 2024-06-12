#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

char buf[1000010];


int main(void)
{

	int cnt = 0;
	for (;; cnt++)
	{
		if (scanf("%s", buf) == EOF)
		{
			break;
		}
	}

	printf("%d", cnt);
	
	return 0;
}