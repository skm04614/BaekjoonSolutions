#include <iostream>
#include <iomanip>

int MAX_DIST;
int NET_DIST[110];
int COST[110];
int N;

int DP[110];
int LAST_STATION[110];
int CNT[110];

void print_record(int last_st)
{
	if (last_st == 0)
	{
		return;
	}

	print_record(LAST_STATION[last_st]);
	std::cout << last_st << ' ';
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> MAX_DIST;
	std::cin >> N;
	for (int i = 1; i <= N + 1; i++)
	{
		int val;
		std::cin >> val;
		NET_DIST[i] = NET_DIST[i - 1] + val;
	}

	for (int i = 1; i <= N; i++)
	{
		std::cin >> COST[i];
	}

	CNT[0] = -1;
	for (int i = 1; i <= N + 1; i++)
	{
		int opt = 0x7FFFFFFF;
		for (int j = i - 1; j >= 0; j--)
		{
			if (NET_DIST[i] - NET_DIST[j] > MAX_DIST)
			{
				break;
			}

			int tmp = DP[j] + COST[j];
			if (tmp <= opt)
			{
				opt = tmp;
				CNT[i] = CNT[j] + 1;
				LAST_STATION[i] = j;
			}
		}

		DP[i] = opt;
	}

	std::cout << DP[N + 1] << '\n' << CNT[N + 1] << '\n';
	print_record(LAST_STATION[N + 1]);

	return 0;
}