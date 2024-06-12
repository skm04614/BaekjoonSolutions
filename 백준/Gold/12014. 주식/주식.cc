#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int ARR[10010];
int N;
int K;

int LIS[10010];
int MAX_LEN;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t)
	{
		std::cin >> N >> K;

		LIS[0] = MAX_LEN = 0;

		for (int i = 1; i <= N; ++i)
		{
			int val;
			std::cin >> val;

			if (val > LIS[MAX_LEN])
			{
				LIS[++MAX_LEN] = val;
			}
			else
			{
				int left = 1;
				int right = MAX_LEN;
				while (left <= right)
				{
					int mid = (left + right) >> 1;
					if (val == LIS[mid])
					{
                        left = mid;
						break;
					}

					if (val < LIS[mid])
					{
						right = mid - 1;
					}
					else
					{
						left = mid + 1;
					}
				}

				LIS[left] = val;
			}
		}

		std::cout << "Case #" << t << '\n';
		std::cout << static_cast<int>(MAX_LEN >= K) << '\n';
	}

	return 0;
}