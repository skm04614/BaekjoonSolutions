#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

using ull = unsigned long long;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int n, k;
	std::cin >> n >> k;

	ull last = 1;
	ull current = 10;
	int digits = 1;
	int num = 0;
	int nth_digit = 0;
	for (;;)
	{
		if (k > digits * (current - last))
		{
			k -= (digits * (current - last));

			digits++;
			current *= 10;
			last *= 10;
		}
		else
		{
			num = last + ((k - 1) / digits);
			nth_digit = (k - 1) % digits;
			break;
		}
	}

	if (num > n)
	{
		std::cout << -1;
	}
	else
	{
		char buf[10] = {};
		int blen = 0;
		while (num)
		{
			buf[blen++] = '0' + (num % 10);
			num /= 10;
		}

		std::cout << buf[blen - 1 - nth_digit];
	}
	
	return 0;
}