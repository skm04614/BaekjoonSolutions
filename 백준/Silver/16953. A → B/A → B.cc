#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


unsigned long long A, B;
int SOL = 0x7FFFFFFF;

void sol(unsigned long long current, int cnt)
{
	if (current > B)
	{
		return;
	}

	if (current == B)
	{
		SOL = SOL < cnt ? SOL : cnt;
		return;
	}

	sol(2 * current, cnt + 1);
	sol(10 * current + 1, cnt + 1);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> A >> B;

	sol(A, 1);
	std::cout << (SOL == 0x7FFFFFFF ? -1 : SOL);


	return 0;
}