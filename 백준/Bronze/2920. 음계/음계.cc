#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int IDXS[26];
char BUF[110];

int main(void)
{
	int val;
	scanf("%d", &val);

	int dir = 0;
	if (val == 8)
	{
		dir = -1;
	}
	else if (val == 1)
	{
		dir = 1;
	}

	for (int i = 1; i < 8; i++)
	{
		int new_val;
		scanf("%d", &new_val);

		if (new_val == val + dir)
		{
			val += dir;
		}
		else
		{
			dir = 0;
		}
	}

	if (dir == 1)
	{
		printf("ascending");
	}
	else if (dir == -1)
	{
		printf("descending");
	}
	else
	{
		printf("mixed");
	}

	return 0;
}