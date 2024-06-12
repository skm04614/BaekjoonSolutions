#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int BASE = 4000;
int VALUES[8001];

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

void swap(int& n, int& m)
{
	int t = n;
	n = m;
	m = t;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;

	int sum = 0;
	int val;
	int min = 4000;
	int max = -4000;
	for (int i = 0; i < n; i++)
	{
		std::cin >> val;

		VALUES[BASE + val]++;
		sum += val;

		min = min < val ? min : val;
		max = max > val ? max : val;
	}
	std::cout << _round(static_cast<double>(sum) / n) << '\n';

	int mid = _round(static_cast<double>(n) / 2);
	val = 0;
	while (mid)
	{
		if (mid <= VALUES[val])
		{
			break;
		}
		mid -= VALUES[val];
		val++;
	}
	std::cout << (val - BASE) << '\n';

	int max_cnt_val = 0;
	int max_cnt_val2 = -1;
	int max_cnt = VALUES[0];
	int max_cnt2 = -1;
	for (int i = 1; i <= 8000; i++)
	{
		if (VALUES[i] > max_cnt2)
		{
			max_cnt2 = VALUES[i];
			max_cnt_val2 = i;
		}

		if (max_cnt2 > max_cnt)
		{
			swap(max_cnt2, max_cnt);
			swap(max_cnt_val2, max_cnt_val);
		}
	}

	std::cout << ((max_cnt2 == max_cnt ? max_cnt_val2 : max_cnt_val) - BASE) << '\n';


	std::cout << (max - min);

	return 0;
}