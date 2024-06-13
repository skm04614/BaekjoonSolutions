#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull ACC[56]; // # digits로 표현 가능한 모든 수의 bit 개수

ull count_bit(ull val)
{
	int n = 54;
	ull cnt = 0;
	int multiplier = 0;
	while (val)
	{
		while (((1llu << n) - 1) > val)
		{
			--n;
		}

		cnt += ACC[n] + multiplier++ * ((1llu << n) - 1);
		val -= ((1llu << n) - 1);

		if (val)
		{
			--val;
			cnt += multiplier;
		}
	}

	return cnt;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	for (int i = 1; i <= 54; ++i)
	{
		ACC[i] = 2 * ACC[i - 1] + (1llu << (i - 1));
	}

	ull n, m;
	std::cin >> n >> m;

	ull res = count_bit(m) - count_bit(n - 1);
	std::cout << res;
	return 0;
}