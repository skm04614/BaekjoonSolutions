#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

unsigned long long A, B, C;

unsigned long long sol(unsigned long long exp)
{
	if (exp == 0)
	{
		return 1;
	}

	if (exp == 1)
	{
		return A;
	}

	unsigned long long res = sol(exp / 2);
	res = (res * res) % C;
	res = (res * sol(exp % 2)) % C;
	return res;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> A >> B >> C;
	std::cout << sol(B) % C;

	return 0;
}