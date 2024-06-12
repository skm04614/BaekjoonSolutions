#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int VISITED[100010];

struct Element
{
	int pos;

	Element execute(int opt) const
	{
		switch (opt)
		{
		case 0:
			return { pos - 1 };
		case 1:
			return { pos + 1 };
		default:
			return { 2 * pos };
		}
	}

	bool is_out_of_bounds() const
	{
		return pos < 0 || pos > 100000;
	}
};

Element Q[100010];
int LP = -1;
int RP = -1;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N;
	int K;
	std::cin >> N >> K;

	VISITED[N] = 1;
	Q[++RP] = { N };

	while (RP > LP)
	{
		const Element& current = Q[++LP];
		if (current.pos == K)
		{
			break;
		}

		{
			Element tp = current.execute(2);
			if (!tp.is_out_of_bounds() && VISITED[tp.pos] == 0)
			{
				Q[++RP] = tp;
				VISITED[tp.pos] = VISITED[current.pos];
			}
		}

		for (int i = 0; i < 2; i++)
		{
			const Element next = current.execute(i);
			if (next.is_out_of_bounds())
			{
				continue;
			}

			if (VISITED[next.pos] == 0)
			{
				Q[++RP] = next;
				VISITED[next.pos] = VISITED[current.pos] + 1;
			}
		}
	}

	std::cout << VISITED[K] - 1;

	return 0;
}