#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

constexpr int R = 0;
constexpr int G = 1;
constexpr int B = 2;

int DP[2][3][3];
int N;

inline int min(int x, int y)
{
	return x < y ? x : y;
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);


	std::cin >> N;

	std::cin >> DP[0][R][R] >> DP[0][G][G] >> DP[0][B][B];

	DP[0][R][G] = DP[0][R][B] = DP[0][G][R] = DP[0][G][B] = DP[0][B][R] = DP[0][B][G] = 0x70000000;

	int p = 0;
	int c = 1;
	for (int n = 0; n < N - 1; n++)
	{
		int r, g, b;
		std::cin >> r >> g >> b;

		for (int s_c = 0; s_c < 3; s_c++)
		{
			DP[c][s_c][R] = r + min(DP[p][s_c][G], DP[p][s_c][B]);
			DP[c][s_c][G] = g + min(DP[p][s_c][R], DP[p][s_c][B]);
			DP[c][s_c][B] = b + min(DP[p][s_c][R], DP[p][s_c][G]);
		}

		p ^= 1;
		c ^= 1;
	}

	int sol = 0x70000000;
	for (int c1 = 0; c1 < 3; c1++)
	{
		for (int c2 = 0; c2 < 3; c2++)
		{
			if (c1 == c2)
			{
				continue;
			}

			sol = sol < DP[p][c1][c2] ? sol : DP[p][c1][c2];
		}
	}

	std::cout << sol;


	return 0;
}