#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

struct Sys
{
	int val[3];

	Sys() : val{}
	{

	}

	Sys move(int opt) const
	{
		Sys ret = *this;

		if (opt == 0)
		{
			ret.val[0] -= 9;
			ret.val[1] -= 3;
			ret.val[2] -= 1;
		}
		else if (opt == 1)
		{
			ret.val[0] -= 9;
			ret.val[1] -= 1;
			ret.val[2] -= 3;
		}
		else if (opt == 2)
		{
			ret.val[0] -= 3;
			ret.val[1] -= 9;
			ret.val[2] -= 1;
		}
		else if (opt == 3)
		{
			ret.val[0] -= 3;
			ret.val[1] -= 1;
			ret.val[2] -= 9;
		}
		else if (opt == 4)
		{
			ret.val[0] -= 1;
			ret.val[1] -= 3;
			ret.val[2] -= 9;
		}
		else
		{
			ret.val[0] -= 1;
			ret.val[1] -= 9;
			ret.val[2] -= 3;
		}

		for (int i = 0; i < 3; ++i)
		{
			ret.val[i] = max(ret.val[i], 0);
		}

		return ret;
	}

	bool is_end() const
	{
		for (int i = 0; i < 3; ++i)
		{
			if (val[i] > 0)
			{
				return false;
			}
		}

		return true;
	}

	int hash() const
	{
		int hash = 0;
		for (int i = 0; i < 3; ++i)
		{
			hash = 62 * hash + val[i];
		}
		return hash;
	}
};

Sys Q[62 * 62 * 62];
int LP, RP;
int VISITED[62 * 62 * 62];


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	Sys init;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> init.val[i];
	}

	Q[++RP] = init;
	VISITED[init.hash()] = 1;

	while (RP > LP)
	{
		const Sys& c = Q[++LP];
		const int v = VISITED[c.hash()];

		for (int opt = 0; opt < 6; ++opt)
		{
			const Sys n = c.move(opt);
			if (VISITED[n.hash()])
			{
				continue;
			}

			VISITED[n.hash()] = v + 1;
			Q[++RP] = n;
		}
	}

	std::cout << VISITED[0] - 1;

	return 0;
}