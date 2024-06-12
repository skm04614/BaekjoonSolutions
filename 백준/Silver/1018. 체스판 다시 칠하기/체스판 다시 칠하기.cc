#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char MAP[52][52];
const char POOL[3] = "WB";

int COST1[52][52];
int COST2[52][52];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	int k = 8;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			std::cin >> MAP[i][j];
		}
	}

	int init_idx1 = 0;
	int init_idx2 = 1;
	for (int i = 1; i <= n; i++)
	{
		init_idx1 ^= 1;
		init_idx2 ^= 1;
		int net_cost1 = 0;
		int net_cost2 = 0;
		int rmv_cost1 = 0;
		int rmv_cost2 = 0;
		for (int j = 1; j <= m; j++)
		{
			net_cost1 += POOL[(init_idx1 + j) % 2] != MAP[i][j];
			net_cost2 += POOL[(init_idx2 + j) % 2] != MAP[i][j];

			if (j > k)
			{
				rmv_cost1 += POOL[(init_idx1 + j - k) % 2] != MAP[i][j - k];
				rmv_cost2 += POOL[(init_idx2 + j - k) % 2] != MAP[i][j - k];
			}

			COST1[i][j] = net_cost1 - rmv_cost1;
			COST2[i][j] = net_cost2 - rmv_cost2;
		}
	}

	int min_cost = 0x7FFFFFFF;
	for (int j = k; j <= m; j++)
	{
		int local_sum1 = 0;
		int local_sum2 = 0;
		for (int i = 1; i < k; i++)
		{
			local_sum1 += COST1[i][j];
			local_sum2 += COST2[i][j];
		}

		for (int i = k; i <= n; i++)
		{
			local_sum1 = local_sum1 - COST1[i - k][j] + COST1[i][j];
			local_sum2 = local_sum2 - COST2[i - k][j] + COST2[i][j];
			min_cost = min_cost < local_sum1 ? min_cost : local_sum1;
			min_cost = min_cost < local_sum2 ? min_cost : local_sum2;
		}
	}

	std::cout << min_cost;

	return 0;
}