#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


int main(void)
{
	char buf[81];
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++)
	{
		scanf("%s", buf);

		char* ptr = buf;
		int sol = 0;
		int pt = 0;
		for (; *ptr; ptr++)
		{
			if (*ptr == 'O')
			{
				sol += (++pt);
			}
			else
			{
				pt = 0;
			}
		}
		printf("%d\n", sol);
	}

	return 0;
}