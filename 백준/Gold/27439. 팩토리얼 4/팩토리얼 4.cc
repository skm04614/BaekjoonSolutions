#include <iostream>
#include <iomanip>

struct BigInt
{
	static constexpr unsigned long long MAX_VAL = static_cast<unsigned long long>(1e12);

	unsigned long long val[100000];
	int idx;

	BigInt() : idx{ 0 }, val{}
	{
		val[0] = 1;
	}

	void operator*=(unsigned int num)
	{
		unsigned long long carry = 0;
		for (int i = 0; i <= idx; i++)
		{
			val[i] = num * val[i] + carry;
			carry = val[i] / MAX_VAL;
			val[i] %= MAX_VAL;
		}

		if (carry)
		{
			val[++idx] = carry;
		}
	}

	void print() const
	{
		std::cout << val[idx];

		for (int i = idx - 1; i >= 0; i--)
		{
			std::cout << std::setfill('0') << std::setw(12) << val[i];
		}
	}
} X;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N;
	std::cin >> N;
	for (int i = 1; i <= N; i++)
	{
		X *= i;
	}
	X.print();

	return 0;
}