#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

bool RECORD[21];
int M;

bool isMatch(const char* s1, const char* s2)
{
	while (*s1 && *s2 && *s1++ == *s2++);
	return *s1 == 0 && *s2 == 0;
}

int main(void)
{
	scanf("%d", &M);

	char cmd[50];
	for (int m = 0; m < M; m++)
	{
		scanf("%s", cmd);
		if (isMatch("all", cmd))
		{
			for (int i = 1; i <= 20; i++)
			{
				RECORD[i] = true;
			}
		}
		else if (isMatch("empty", cmd))
		{
			for (int i = 1; i <= 20; i++)
			{
				RECORD[i] = false;
			}
		}
		else
		{
			int val;
			scanf("%d", &val);

			if (isMatch("add", cmd))
			{
				RECORD[val] = true;
			}
			else if (isMatch("remove", cmd))
			{
				RECORD[val] = false;
			}
			else if (isMatch("check", cmd))
			{
				printf("%d\n", RECORD[val]);
			}
			else if (isMatch("toggle", cmd))
			{
				RECORD[val] ^= true;
			}
		}
	}

	return 0;
}