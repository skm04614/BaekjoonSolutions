#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

int _slen(const char* s)
{
	int len = 0;
	while (*s++) { ++len; }
	return len;
}

char BUF[50];
int DP[2][50];
int N;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> BUF;
	N = _slen(BUF);

	DP[0][0] = 1;
	DP[1][0] = 0;
	for (int i = 1; i < N; ++i)
	{
		int n = BUF[i] - '0';
		int m = 10 * (BUF[i - 1] - '0') + (BUF[i] - '0');

		if (n == 0)
		{
			DP[0][i] = 0;
		}
		else
		{
			DP[0][i] = DP[1][i - 1] + DP[0][i - 1];
		}
		
		if (m <= 34)
		{
			DP[1][i] = DP[0][i - 1];
		}
		else
		{
			DP[1][i] = 0;
		}
	}

	std::cout << (DP[0][N - 1] + DP[1][N - 1]);

	return 0;
}