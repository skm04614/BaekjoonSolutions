#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int IDXS[26];
char BUF[110];

int main(void)
{
	for (int i = 0; i < 26; i++)
	{
		IDXS[i] = -1;
	}

	scanf("%s", BUF);
	int idx = 0;
	for (char* ptr = BUF; *ptr; ptr++, idx++)
	{
		if (IDXS[*ptr - 'a'] == -1)
		{
			IDXS[*ptr - 'a'] = idx;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		printf("%d ", IDXS[i]);
	}

	return 0;
}