#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ORIGINAL_H_CNT[257];
int SUM;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;
	std::cin >> n >> m >> SUM;

	int val;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cin >> val;
			ORIGINAL_H_CNT[val]++;
			SUM += val;
		}
	}

	int max_height = SUM / (n * m);

	int best_time = 0x7FFFFFFF;
	int best_height = 0;

	for (int h = 0; h <= max_height; h++)
	{
		int current_time = 0;
		for (int h0 = 0; h0 <= 256; h0++)
		{
			if (h0 == h)
			{
				continue;
			}

			if (h0 < h)
			{
				current_time += (h - h0) * ORIGINAL_H_CNT[h0];
			}
			else
			{
				current_time += 2 * (h0 - h) * ORIGINAL_H_CNT[h0];
			}
		}

		if (current_time <= best_time)
		{
			best_time = current_time;
			best_height = h;
		}
	}

	std::cout << best_time << ' ' << best_height;


	return 0;
}