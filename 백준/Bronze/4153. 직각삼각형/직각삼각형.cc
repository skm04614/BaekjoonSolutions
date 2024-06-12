#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cmath>

inline void swap(int& n, int& m)
{
	int tmp = n;
	n = m;
	m = tmp;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int a, b, c;
	for (;;)
	{
		std::cin >> a >> b >> c;
		if (a == 0 && b == 0 && c == 0)
		{
			break;
		}

		if (a > c)
		{
			swap(a, c);
		}

		if (b > c)
		{
			swap(b, c);
		}

		std::cout << (a * a + b * b == c * c ? "right" : "wrong") << '\n';
	}

	return 0;
}