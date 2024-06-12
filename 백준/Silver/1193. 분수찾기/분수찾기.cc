#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>


int main(void)
{
	int n;
	scanf("%d", &n);

	int i = 0;
	for (i = 1; ; i++)
	{
		if (n - i <= 0)
		{
			break;
		}
		n -= i;
	}
    
    if (i % 2)
    {
        printf("%d/%d", i - n + 1, n);
    }
    else
    {
        printf("%d/%d", n, i - n + 1);
    }

	return 0;
}