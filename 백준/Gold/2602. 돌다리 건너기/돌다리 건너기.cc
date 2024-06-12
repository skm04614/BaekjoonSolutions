#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

enum
{
	ANGEL,
	DEVIL
};

char KEY[22];
char BRIDGES[2][110];

int DP[22][2][110];

int _slen(const char* s)
{
	int len = 0;
	while (*s++) { len++; }
	return len;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> KEY >> BRIDGES[0] >> BRIDGES[1];

	int klen = _slen(KEY);
	int blen = _slen(BRIDGES[0]);

	for (int j = 0; j < blen; j++)
	{
		for (int b = 0; b < 2; b++)
		{
			if (KEY[0] == BRIDGES[b][j])
			{
				DP[0][b][j] = 1;
			}
		}
	}

	for (int i = 1; i < klen; i++)
	{
		const char k = KEY[i];
		int cnt[2] = { 0, 0 };
		for (int j = 0; j < blen; j++)
		{
			for (int b = 0; b < 2; b++)
			{
				if (BRIDGES[b][j] == k)
				{
					DP[i][b][j] = cnt[b ^ 1];
				}
				cnt[b ^ 1] += DP[i - 1][b ^ 1][j];
			}
		}
	}

	int sol = 0;
	for (int i = 0; i < blen; i++)
	{
		for (int b = 0; b < 2; b++)
		{
			sol += DP[klen - 1][b][i];
		}
	}
	std::cout << sol;


	return 0;
}