#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int C, N;

int DP[2][100050];

int max(int x, int y)
{
	return x > y ? x : y;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> C >> N;

	int prev = 0;
	int curr = 1;
	for (int i = 0; i < N; i++)
	{
		int cost;
		int gain;
		std::cin >> cost >> gain;

		for (int c = 0; c < cost; c++)
		{
			DP[curr][c] = DP[prev][c];
		}
		DP[curr][cost] = max(DP[prev][cost], gain);
		for (int c = cost + 1; c <= 100000; c++)
		{
			DP[curr][c] = DP[prev][c];
			if (DP[curr][c - cost])
			{
				DP[curr][c] = max(DP[curr][c], DP[curr][c - cost] + gain);
			}
		}

		curr ^= 1;
		prev ^= 1;
	}

	for (int c = 0; c <= 100000; c++)
	{
		if (DP[prev][c] >= C)
		{
			std::cout << c;
			break;
		}
	}

	
	return 0;
}