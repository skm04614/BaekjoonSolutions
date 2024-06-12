#include <cstdio>
#include <iostream>

int N, M;
int TARGET[50];

struct Element
{
	Element* prev;
	Element* next;
};

Element Pool[51];

int main(void)
{
	std::cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		std::cin >> TARGET[i];
	}

	Pool[1].prev = &Pool[N];
	Pool[1].next = &Pool[2];
	Pool[N].prev = &Pool[N - 1];
	Pool[N].next = &Pool[1];

	for (int i = 2; i < N; i++)
	{
		Pool[i].next = &Pool[i + 1];
		Pool[i].prev = &Pool[i - 1];
	}

	Element* rs = &Pool[1];
	Element* ls = &Pool[1];
	int CNT = 0;

	for (int i = 0; i < M; i++)
	{
		int val = TARGET[i];
		int left_cnt = 0;
		int right_cnt = 0;
		while (rs != &Pool[val])
		{
			rs = rs->next;
			right_cnt++;
		}
		while (ls != &Pool[val])
		{
			ls = ls->prev;
			left_cnt++;
		}

		if (left_cnt < right_cnt)
		{
			CNT += left_cnt;
		}
		else
		{
			CNT += right_cnt;
		}

		(&Pool[val])->prev->next = (&Pool[val])->next;
		(&Pool[val])->next->prev = (&Pool[val])->prev;

		ls = rs = Pool[TARGET[i]].next;
	}

	std::cout << CNT;
	return 0;
}