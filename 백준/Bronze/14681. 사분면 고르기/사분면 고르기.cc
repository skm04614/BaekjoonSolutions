#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int x, y;
	std::cin >> x >> y;
	if (y > 0)
	{
		std::cout << (x < 0 ? 2 : 1);
	}
	else
	{
		std::cout << (x < 0 ? 3 : 4);
	}

	return 0;
}