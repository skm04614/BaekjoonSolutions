#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int sum;
	std::cin >> sum;
	char op;
	int val;

	int tmp_sum = 0;
	while (std::cin >> op >> val)
	{
		if (tmp_sum)
		{
			if (op == '+')
			{
				tmp_sum += val;
			}
			else
			{
				sum -= tmp_sum;
				tmp_sum = val;
			}
		}
		else
		{
			if (op == '+')
			{
				sum += val;
			}
			else
			{
				tmp_sum = val;
			}
		}
	}

	sum -= tmp_sum;

	std::cout << sum;

	return 0;
}