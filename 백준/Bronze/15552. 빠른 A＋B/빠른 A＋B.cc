#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;
	while (T--)
	{
		int a, b;
		std::cin >> a >> b;
		std::cout << a + b << '\n';
	}

	return 0;
}