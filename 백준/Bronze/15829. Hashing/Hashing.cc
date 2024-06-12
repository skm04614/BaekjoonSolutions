#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char buf[51];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int L;
	std::cin >> L >> buf;

	unsigned long long hash = 0;
	for (int i = L - 1; i >= 0; i--)
	{
		hash = (hash * 31 + (buf[i] - 'a' + 1)) % 1234567891;
	}
	std::cout << hash;


	return 0;
}