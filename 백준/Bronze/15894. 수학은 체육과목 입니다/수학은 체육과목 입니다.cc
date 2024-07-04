#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	unsigned long long n;
	std::cin >> n;
	std::cout << (n << 2);

	return 0;
}