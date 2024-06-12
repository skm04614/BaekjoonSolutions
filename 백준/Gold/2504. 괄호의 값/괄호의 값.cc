#include <cstdio>

int score[31] = {};
int sidx = 0;

int main(void)
{
	char str[31] = {};
	char* pstr = str;
	char buf[31] = {};
	scanf("%s", str);
	
	int bidx = -1;
	while (*pstr)
	{
		buf[++bidx] = *pstr;
		if (*pstr == '(' || *pstr == '[')
		{
			score[++sidx] = 0;
		}
		else if (*pstr == ')')
		{
			if (bidx == 0 || buf[bidx - 1] != '(')
			{
				score[0] = 0;
				break;
			}
			score[sidx - 1] += score[sidx] ? score[sidx] * 2 : 2;
			sidx--;
			bidx -= 2;
		}
		else if (*pstr == ']')
		{
			if (bidx == 0 || buf[bidx - 1] != '[')
			{
				score[0] = 0;
				break;
			}
			score[sidx - 1] += score[sidx] ? score[sidx] * 3 : 3;
			sidx--;
			bidx -= 2;
		}

		pstr++;
	}

	printf("%d", bidx == -1 ? score[0] : 0);

	return 0;
}