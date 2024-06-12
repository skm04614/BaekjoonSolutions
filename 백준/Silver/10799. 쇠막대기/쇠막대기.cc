#include <cstdio>

int main(void)
{
	int sp = 0;

	char buf[100001];
	scanf("%s", buf);

	char* pbuf = buf;
	int total = 0;
	while (*pbuf)
	{
		if (*pbuf == '(')
		{
			if (*(pbuf + 1) == ')')
			{
				total += sp;
				pbuf++;
			}
			else
			{
				sp++;
			}
		}
		else if (*pbuf == ')')
		{
			sp--;
			total++;
		}
		pbuf++;
	}
	printf("%d", total);

	return 0;
}