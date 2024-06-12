#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int W[31];
int N;
int DP[40010];

int abs(int x)
{
	return x < 0 ? -x : x;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	DP[0] = 1;

	std::cin >> N;
	for (int i = 2; i <= N + 1; i++)
	{
		int weight;
		std::cin >> weight;
	
		for (int w = 0; w <= 40000; w++)
		{
			if (!DP[w] || DP[w] == i)
			{
				continue;
			}
			
			if (w + weight <= 40000 && !DP[w + weight])
			{
				DP[w + weight] = i;
			}

			int w2 = abs(w - weight);
			if (!DP[w2])
			{
				DP[w2] = i;
			}
		}
	}

	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		int target;
		std::cin >> target;

		std::cout << (DP[target] ? 'Y' : 'N') << ' ';
	}

	return 0;
}