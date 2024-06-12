#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

char S1[110];
char S2[110];
char S3[110];

int DP[110][110][110];

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

	std::cin >> S1 + 1 >> S2 + 1 >> S3 + 1;
	const int l1 = _slen(S1 + 1);
	const int l2 = _slen(S2 + 1);
	const int l3 = _slen(S3 + 1);

	for (int i = 1; i <= l1; i++)
	{
		for (int j = 1; j <= l2; j++)
		{
			for (int k = 1; k <= l3; k++)
			{
				if (S1[i] == S2[j] && S1[i] == S3[k])
				{
					DP[i][j][k] = DP[i - 1][j - 1][k - 1] + 1;
				}
				else
				{
					DP[i][j][k] = max(max(DP[i - 1][j][k], DP[i][j - 1][k]), DP[i][j][k - 1]);
				}
			}
		}
	}
	std::cout << DP[l1][l2][l3];

	return 0;
}