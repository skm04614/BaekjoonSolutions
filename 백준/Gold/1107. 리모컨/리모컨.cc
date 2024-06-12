#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int ORIGINAL_CHANNEL = 100;
int TARGET_CHANNEL;

bool IS_BROKEN[10];


inline int abs(int x)
{
	return x < 0 ? -x : x;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int M;
	std::cin >> TARGET_CHANNEL >> M;
	for (int m = 0; m < M; m++)
	{
		int key;
		std::cin >> key;
		IS_BROKEN[key] = true;
	}

	if (TARGET_CHANNEL == ORIGINAL_CHANNEL)
	{
		std::cout << 0;
	}
	else
	{
		int best_cnt = abs(ORIGINAL_CHANNEL - TARGET_CHANNEL);
		for (int ch = 0; ch <= 999999; ch++)
		{
			int tmp = ch;

			bool skip = false;
			int cnt = 0;
			do
			{
				if (IS_BROKEN[tmp % 10])
				{
					skip = true;
					break;
				}
				tmp /= 10;
				cnt++;
			} while (tmp);

			if (!skip)
			{
				cnt += abs(ch - TARGET_CHANNEL);

				best_cnt = best_cnt < cnt ? best_cnt : cnt;
			}
		}

		std::cout << best_cnt;
	}

	return 0;
}