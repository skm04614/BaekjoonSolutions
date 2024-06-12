#include <cstdio>

int main(void)
{
	int sp = 0;

	int T = 0;
	scanf("%d", &T);
	for (int t = 0; t < T; t++)
	{
		char buf[51];
		scanf("%s", buf);
		sp = 0;

		char* pbuf = buf;
		while (*pbuf)
		{
			if (*pbuf == '(')
			{
				sp++;
			}
			else if (*pbuf == ')' && sp > 0)
			{
				sp--;
			}
			else
			{
				sp = -1;
				break;
			}
			pbuf++;
		}
		printf("%s\n", sp == 0 ? "YES" : "NO");
	}

	return 0;
}