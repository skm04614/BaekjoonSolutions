#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int MAP[41][41];
int Y, X;

struct Sticker
{
	int data[11][11];
	int y;
	int x;

	int attach() const
	{
		int cnt = 0;
		for (int y0 = 0; y0 < Y; ++y0)
		{
			for (int x0 = 0; x0 < X; ++x0)
			{
				if (cnt = attach_1(y0, x0))
				{
					return cnt;
				}
			}
		}

		for (int y0 = 0; y0 < Y; ++y0)
		{
			for (int x0 = 0; x0 < X; ++x0)
			{
				if (cnt = attach_2(y0, x0))
				{
					return cnt;
				}
			}
		}

		for (int y0 = 0; y0 < Y; ++y0)
		{
			for (int x0 = 0; x0 < X; ++x0)
			{
				if (cnt = attach_3(y0, x0))
				{
					return cnt;
				}
			}
		}

		for (int y0 = 0; y0 < Y; ++y0)
		{
			for (int x0 = 0; x0 < X; ++x0)
			{
				if (cnt = attach_4(y0, x0))
				{
					return cnt;
				}
			}
		}

		return 0;
	}

private:
	int attach_1(int y0, int x0) const
	{
		if (y0 + y > Y || x0 + x > X)
		{
			return 0;
		}

		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				if (!data[i][j])
				{
					continue;
				}

				if (MAP[y0 + i][x0 + j])
				{
					return 0;
				}
			}
		}

		int cnt = 0;
		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				if (!data[i][j] || MAP[y0 + i][x0 + j])
				{
					continue;
				}

				MAP[y0 + i][x0 + j] = 1;
				++cnt;
			}
		}

		return cnt;
	}

	int attach_2(int y0, int x0) const
	{
		if (y0 + x > Y || x0 + y > X)
		{
			return 0;
		}

		for (int j = 0; j < x; ++j)
		{
			for (int i = 0; i < y; ++i)
			{
				if (!data[y - 1 - i][j])
				{
					continue;
				}

				if (MAP[y0 + j][x0 + i])
				{
					return 0;
				}
			}
		}

		int cnt = 0;
		for (int j = 0; j < x; ++j)
		{
			for (int i = 0; i < y; ++i)
			{
				if (!data[y - 1 - i][j] || MAP[y0 + j][x0 + i])
				{
					continue;
				}

				MAP[y0 + j][x0 + i] = 1;
				++cnt;
			}
		}

		return cnt;
	}

	int attach_3(int y0, int x0) const
	{
		if (y0 + y > Y || x0 + x > X)
		{
			return 0;
		}

		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				if (!data[y - 1 - i][x - 1 - j])
				{
					continue;
				}

				if (MAP[y0 + i][x0 + j])
				{
					return 0;
				}
			}
		}

		int cnt = 0;
		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				if (!data[y - 1 - i][x - 1 - j] || MAP[y0 + i][x0 + j])
				{
					continue;
				}

				MAP[y0 + i][x0 + j] = 1;
				++cnt;
			}
		}

		return cnt;
	}

	int attach_4(int y0, int x0) const
	{
		if (y0 + x > Y || x0 + y > X)
		{
			return 0;
		}

		for (int j = 0; j < x; ++j)
		{
			for (int i = 0; i < y; ++i)
			{
				if (!data[i][x - 1 - j])
				{
					continue;
				}

				if (MAP[y0 + j][x0 + i])
				{
					return 0;
				}
			}
		}

		int cnt = 0;
		for (int j = 0; j < x; ++j)
		{
			for (int i = 0; i < y; ++i)
			{
				if (!data[i][x - 1 - j] || MAP[y0 + j][x0 + i])
				{
					continue;
				}

				MAP[y0 + j][x0 + i] = 1;
				++cnt;
			}
		}

		return cnt;
	}
};

Sticker STICKERS[101];
int K;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int res = 0;

	std::cin >> Y >> X >> K;
	for (int k = 0; k < K; ++k)
	{
		Sticker& s = STICKERS[k];
		std::cin >> s.y >> s.x;
		for (int i = 0; i < s.y; ++i)
		{
			for (int j = 0; j < s.x; ++j)
			{
				std::cin >> s.data[i][j];
			}
		}

		res += s.attach();
	}

	std::cout << res;

	return 0;
}