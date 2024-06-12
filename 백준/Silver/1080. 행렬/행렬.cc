#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

using ull = unsigned long long;

constexpr int L = 3;

ull MAP[51];
ull TGT[51];
int Y;
int X;

bool is_eq()
{
	for (int y = 0; y < Y; ++y)
	{
		if (MAP[y] != TGT[y])
		{
			return false;
		}
	}

	return true;
}

void toggle(int y, int x)
{
	for (int i = 0; i < L; ++i)
	{
		MAP[y + i] ^= (7llu << x);
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> Y >> X;
	for (int y = 0; y < Y; ++y)
	{
		for (int x = 0; x < X; ++x)
		{
			char c;
			std::cin >> c;

			MAP[y] = MAP[y] << 1 | static_cast<ull>(c - '0');
		}
	}

	for (int y = 0; y < Y; ++y)
	{
		for (int x = 0; x < X; ++x)
		{
			char c;
			std::cin >> c;

			TGT[y] = TGT[y] << 1 | static_cast<ull>(c - '0');
		}
	}

	int cnt = 0;
	for (int y = 0; y < Y - L + 1; ++y)
	{
		for (int x = 0; x < X - L + 1; ++x)
		{
			if ((MAP[y] & (1llu << x)) != (TGT[y] & (1llu << x)))
			{
				toggle(y, x);
				++cnt;
			}
		}
	}

	if (is_eq())
	{
		std::cout << cnt;
	}
	else
	{
		std::cout << -1;
	}

	return 0;
}