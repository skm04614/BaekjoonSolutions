#include <iostream>
#include <iomanip>

constexpr int PATTY = 0;
constexpr int BUN = 1;

using ull = unsigned long long;
ull DP[51][2];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	DP[0][PATTY] = 1;


	for (int i = 1; i <= 50; i++)
	{
		DP[i][PATTY] = 2 * DP[i - 1][PATTY] + 1;
		DP[i][BUN] = 2 * DP[i - 1][BUN] + 2;
	}

	ull N, X;
	std::cin >> N >> X;
	
	ull patty_cnt = 0;
	while (X)
	{
		ull size = (DP[N][PATTY] + DP[N][BUN] + 1) / 2;
		if (X >= size)
		{
			if (N)
			{
				patty_cnt += DP[N - 1][PATTY] + 1;
				X -= size;
			}
			else
			{
				patty_cnt++;
				break;
			}
		}
		else if (X < size)
		{
			X--;
		}

		N--;
	}
	std::cout << patty_cnt;



	return 0;
}