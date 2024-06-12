#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int _round(double x)
{
	if (x > 0)
	{
		x += 0.5;
	}
	else if (x < 0)
	{
		x -= 0.5;
	}
	
	return static_cast<int>(x);
}

int SCORE_CNT[31];
int N;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;

	if (N == 0)
	{
		std::cout << 0;
	}
	else
	{
		int val;
		for (int i = 0; i < N; i++)
		{
			std::cin >> val;
			SCORE_CNT[val]++;
		}

		const int discard_cnt = _round(0.15 * N);
		int discard_left = discard_cnt;
		int discard_right = discard_cnt;

		for (int n = 1; n <= 30; n++)
		{
			if (discard_left > SCORE_CNT[n])
			{
				discard_left -= SCORE_CNT[n];
				SCORE_CNT[n] = 0;
			}
			else
			{
				SCORE_CNT[n] -= discard_left;
				discard_left = 0;
			}

			if (discard_left == 0)
			{
				break;
			}
		}

		for (int n = 30; n >= 1; n--)
		{
			if (discard_right > SCORE_CNT[n])
			{
				discard_right -= SCORE_CNT[n];
				SCORE_CNT[n] = 0;
			}
			else
			{
				SCORE_CNT[n] -= discard_right;
				discard_right = 0;
			}

			if (discard_right == 0)
			{
				break;
			}
		}

		int sum = 0;
		for (int n = 1; n <= 30; n++)
		{
			sum += (n * SCORE_CNT[n]);
		}
		int sol = _round(static_cast<double>(sum) / (N - (2 * discard_cnt)));
		std::cout << sol;
	}
	return 0;
}