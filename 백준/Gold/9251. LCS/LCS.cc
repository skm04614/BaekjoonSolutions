#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

char s1[1002];
char s2[1002];

int DP[1002][1002];


int _slen(const char* s)
{
	int len = 0;
	while (*s++) { len++; }
	return len;
}

int max(int x, int y)
{
	return x > y ? x : y;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> s1 + 1 >> s2 + 1;

	int slen1 = _slen(s1 + 1);
	int slen2 = _slen(s2 + 1);

	for (int i = 1; i <= slen1; i++)
	{
		for (int j = 1; j <= slen2; j++)
		{
			if (s1[i] == s2[j])
			{
				DP[i][j] = DP[i - 1][j - 1] + 1;
			}
			else
			{
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
			}
		}
	}

	std::cout << DP[slen1][slen2];

	return 0;
}