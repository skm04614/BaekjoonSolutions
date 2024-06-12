#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using uint = unsigned int;

uint WORDS[51];
int N, K;

int SOL;

void sol(uint pool, uint sc, int cnt)
{
	if (cnt < 0)
	{
		return;
	}

	if (cnt == 0 || sc > (1u << 25))
	{
		int result = 0;
		for (int i = 0; i < N; i++)
		{
			result += ((WORDS[i] & pool) == WORDS[i]);
		}
		SOL = SOL > result ? SOL : result;
		return;
	}

	if (!(pool & sc))
	{
		sol(pool | sc, sc << 1, cnt - 1);
	}
	sol(pool, sc << 1, cnt);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	const uint init = (1u << ('a' - 'a')) | (1u << ('n' - 'a')) | (1u << ('t' - 'a')) | (1u << ('i' - 'a')) | (1u << ('c' - 'a'));

	std::cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		char buf[20] = {};
		std::cin >> buf;
		const char* ptr = buf;
		while (*ptr)
		{
			WORDS[i] |= (1u << (*ptr++ - 'a'));
		}
	}
	
	K -= 5;
	sol(init, 1u, K);
	std::cout << SOL;

	return 0;
}