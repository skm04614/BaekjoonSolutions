#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int max(int x, int y)
{
	return x > y ? x : y;
}

inline int abs(int x)
{
	return x < 0 ? -x : x;
}

struct Entry
{
	int l;
	int r;
	int cnt;
};

// a = 1 ~ z = 26
Entry ENTRIES[27];
int DP[2][27];
int N;

void init()
{
	N = 0;
	ENTRIES[0] = { 0, 0, 0 };
	for (int i = 1; i <= 26; ++i)
	{
		ENTRIES[i] = { INF, 0, 0 };
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	init();

	char buf[51] = "";
	std::cin >> buf;
	for (int i = 0; buf[i]; ++i)
	{
		Entry& e = ENTRIES[1 + buf[i] - 'a'];

		e.l = min(e.l, i);
		e.r = max(e.r, i);
		++e.cnt;
	}

	for (int i = 1; i <= 26; ++i)
	{	
		const Entry& e = ENTRIES[i];
		if (e.l == INF)
		{
			continue;
		}

		ENTRIES[++N] = e;
	}

	DP[0][0] = DP[0][1] = 0;
	for (int i = 1; i <= N; ++i)
	{
		const Entry& last = ENTRIES[i - 1];
		const Entry& current = ENTRIES[i];

		const int base = current.cnt + current.r - current.l;

		DP[0][i] = base + min(DP[0][i - 1] + abs(last.l - current.r), DP[1][i - 1] + abs(last.r - current.r));
		DP[1][i] = base + min(DP[1][i - 1] + abs(last.r - current.l), DP[0][i - 1] + abs(last.l - current.l));
	}
	std::cout << min(DP[0][N], DP[1][N]);

	return 0;
}