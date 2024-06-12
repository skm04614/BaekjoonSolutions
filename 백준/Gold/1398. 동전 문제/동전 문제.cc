#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--)
	{
		ull target_val;
		std::cin >> target_val;

		ull cnt = 0;
		while (target_val)
		{
			ull local_cnt = 100;
			for (int i = 0; i < 4; i++)
			{
				int local_val = (target_val % 100) - 25 * i;
				if (local_val < 0)
				{
					break;
				}

				ull candidate_cnt = i + (local_val / 10) + (local_val % 10);
				local_cnt = local_cnt < candidate_cnt ? local_cnt : candidate_cnt;
			}
			cnt += local_cnt;

			target_val /= 100;
		}
		std::cout << cnt << '\n';
	}


	return 0;
}