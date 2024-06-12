#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <string>

int map[26]{};
char buf[1000010];


int main(void)
{
	scanf("%s", buf);

	char* ptr = buf;
	for (; *ptr; ptr++)
	{
		if (*ptr >= 'a')
		{
			map[*ptr - 'a']++;
		}
		else
		{
			map[*ptr - 'A']++;
		}
	}

	int max = -1;
	int max_cnt = 0;
	int max_idx = -1;
	for (int cidx = 0; cidx < 26; cidx++)
	{
		if (map[cidx] > max)
		{
			max = map[cidx];
			max_cnt = 1;
			max_idx = cidx;
		}
		else if (map[cidx] == max)
		{
			max_cnt++;
		}
	}

	printf("%c", max_cnt > 1 ? '?' : 'A' + max_idx);
	
	return 0;
}