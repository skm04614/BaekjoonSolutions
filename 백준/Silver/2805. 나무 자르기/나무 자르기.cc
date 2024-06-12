#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int N;
int M;
int TREE[1000001];
int SOL;

void sol(unsigned long long h0, unsigned long long h1)
{
	if (h0 > h1)
	{
		return;
	}

	unsigned long long h = (h0 + h1) / 2;
	unsigned long long sum = 0;
	for (int i = 0; i < N; i++)
	{
		if (TREE[i] > h)
		{
			sum += (TREE[i] - h);
		}
	}

	if (sum >= M)
	{
		SOL = SOL > h ? SOL : h;
		sol(h + 1, h1);
	}
	else
	{
		sol(h0, h - 1);
	}

}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		std::cin >> TREE[i];
	}

	sol(0, 2000000000);
	std::cout << SOL;

	return 0;
}