#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int n;
	std::cin >> n;
	for (int i = 2; n != 1; ++i)
	{
		while (n % i == 0)
		{
			std::cout << i << '\n';
			n /= i;
		}
	}

	return 0;
}