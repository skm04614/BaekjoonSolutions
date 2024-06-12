#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

char S[4010];
char T[4010];

int DP[4010][4010];

int _slen(const char* s)
{
	int len = 0;
	while (*s++) { len++; }
	return len;
}

int max(int n, int m)
{
	return n > m ? n : m;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> S + 1 >> T + 1;

	int slen1 = _slen(S + 1);
	int slen2 = _slen(T + 1);
	int SOL = 0;
	for (int i = 1; i <= slen1; i++)
	{
		for (int j = 1; j <= slen2; j++)
		{
			if (S[i] == T[j])
			{
				DP[i][j] = DP[i - 1][j - 1] + 1;
				SOL = SOL > DP[i][j] ? SOL : DP[i][j];
			}
		}
	}
	std::cout << SOL;

	return 0;
}