#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Coords
{
	int y;
	int x;

	bool is_out_of_bounds(int y0, int y1, int x0, int x1) const
	{
		return y < y0 || y >= y1 || x < x0 || x >= x1;
	}

	Coords operator+(const Coords& other) const
	{
		return { y + other.y, x + other.x };
	}
};

const Coords DIRS[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

Coords Q[365000];
int L;
int R;

char MAP[610][610];
bool VISITED[610][610];
int Y;
int X;

int gcd(int a, int b)
{
	if (a == b)
	{
		return a;
	}

	if (a > b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}

	return gcd(b - a, a);
}

int lcm(int a, int b)
{
	return a * b / gcd(a, b);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		int sol = -1;
		int max_c = lcm(a, b);
		for (int k = c; k <= max_c; k += a)
		{
			if (((k - 1) % b) + 1 == d)
			{
				sol = k;
				break;
			}
		}

		std::cout << sol << '\n';
	}

	return 0;
}