#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char BUF[3][10];

void print_fizzubzz(int val)
{
	if (val % 5 == 0 && val % 3 == 0)
	{
		std::cout << "FizzBuzz";
		return;
	}

	if (val % 5 == 0)
	{
		std::cout << "Buzz";
		return;
	}

	if (val % 3 == 0)
	{
		std::cout << "Fizz";
		return;
	}

	std::cout << val;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	for (int i = 0; i < 3; ++i)
	{
		std::cin >> BUF[i];
	}

	int n;
	int val = 0;
	for (n = 0; n < 3; ++n)
	{
		if (BUF[n][0] == 'F' || BUF[n][0] == 'B')
		{
			continue;
		}

		const char* ptr = BUF[n];
		while (*ptr)
		{
			val = 10 * val + (*ptr - '0');
			++ptr;
		}
		break;
	}

	val += (3 - n);
	print_fizzubzz(val);

	return 0;
}