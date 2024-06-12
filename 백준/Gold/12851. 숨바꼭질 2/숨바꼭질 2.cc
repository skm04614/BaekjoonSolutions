#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int RECORD[100010];
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

	RECORD[N] = 1;
	VISITED[N] = 1;
	Q[++RP] = { N };

	while (RP > LP)
	{
		const Element& current = Q[++LP];
		if (current.pos == K)
		{
			break;
		}

		for (int i = 0; i < 3; i++)
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

			if (VISITED[next.pos] == VISITED[current.pos] + 1)
			{
				RECORD[next.pos] += RECORD[current.pos];
			}
		}
	}
	std::cout << VISITED[K] - 1 << '\n' << RECORD[K];

	return 0;
}