#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Element
{
	int val;
} POOL[101];

struct
{
	Element* data[10010];
	int sp = -1;
	int ep = -1;

	void push(Element *e)
	{
		data[++ep] = e;
	}

	Element* pop()
	{
		return data[++sp];
	}

	void clear()
	{
		sp = -1;
		ep = -1;
	}

	bool empty() const
	{
		return sp == ep;
	}

	int size() const
	{
		return ep - sp;
	}
} QUEUE;

int CNT[10];
int N;
int M;
int T;
Element* target;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> T;
	for (int i = 0; i < T; i++)
	{
		target = nullptr;

		for (int j = 0; j < 10; j++)
		{
			CNT[j] = 0;
		}
		QUEUE.clear();

		std::cin >> N >> M;

		for (int n = 0; n < N; n++)
		{
			std::cin >> POOL[n].val;
			QUEUE.push(&POOL[n]);
			CNT[POOL[n].val]++;
			if (n == M)
			{
				target = &POOL[n];
			}
		}

		while (!QUEUE.empty())
		{
			auto e = QUEUE.pop();
			bool flag = false;
			for (int p = e->val + 1; p < 10; p++)
			{
				if (CNT[p])
				{
					flag = true;
					break;
				}
			}

			if (!flag)
			{
				CNT[e->val]--;
				if (target == e)
				{
					std::cout << N - QUEUE.size() << '\n';
					break;
				}
			}
			else
			{
				QUEUE.push(e);
			}
		}
	}

	return 0;
}