#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int main(void)
{
	for (;;)
	{
		int val;
		scanf("%d", &val);
		if (val == 0)
		{
			break;
		}
		int tmp = val;
		int reversed_val = 0;
		while (tmp)
		{
			reversed_val = (reversed_val * 10) + tmp % 10;
			tmp /= 10;
		}
		printf("%s\n", val == reversed_val ? "yes" : "no");
	}

	return 0;
}