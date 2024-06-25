#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

#pragma pack(push, 1)
struct Problem
{
	int id;
	short level;
	short group;

	bool operator<=(const Problem& other) const
	{
		if (level == other.level)
		{
			return id <= other.id;
		}

		return level < other.level;
	}

	bool operator>=(const Problem& other) const
	{
		if (level == other.level)
		{
			return id >= other.id;
		}

		return level > other.level;
	}

	bool operator==(const Problem& other) const
	{
		return id == other.id && level == other.level && group == other.group;
	}

	bool operator!=(const Problem& other) const
	{
		return !(*this == other);
	}
};
#pragma pack(pop)

template <bool Max>
struct Heap
{
	Problem data[111000];
	int size;

	bool empty() const
	{
		return size == 0;
	}

	const Problem& peek() const
	{
		return data[1];
	}

	int peek_id() const
	{
		return data[1].id;
	}

	void push(Problem p)
	{
		data[++size] = p;

		int c = size;
		while (c > 1)
		{
			int p = c >> 1;
			if (data[p] >= data[c] == Max)
			{
				break;
			}
			swap(data[p], data[c]);
			c = p;
		}
	}

	Problem pop()
	{
		swap(data[1], data[size--]);

		int p = 1;
		int c = p << 1;
		while (c <= size)
		{
			if ((c | 1) <= size && (data[c | 1] >= data[c]) == Max)
			{
				c |= 1;
			}

			if ((data[p] >= data[c]) == Max)
			{
				break;
			}
			swap(data[p], data[c]);
			p = c;
			c = p << 1;
		}

		return data[size + 1];
	}
};


Problem P[100100];

Heap<true> MAX_PQ_1[102];
Heap<false> MIN_PQ_1[102];

Heap<true> MAX_PQ_2;
Heap<false> MIN_PQ_2;

Heap<true> MAX_PQ_3[102];
Heap<false> MIN_PQ_3[102];

void add(int p, short l, short g)
{
	P[p] = { p, l, g };

	MAX_PQ_1[g].push(P[p]);
	MIN_PQ_1[g].push(P[p]);

	MAX_PQ_2.push(P[p]);
	MIN_PQ_2.push(P[p]);

	MAX_PQ_3[l].push(P[p]);
	MIN_PQ_3[l].push(P[p]);
}

void solve(int p)
{
	P[p] = { -1, -1, -1 };
}

int recommend_1(int opt, int g)
{
	if (opt == 1)
	{
		auto& pq = MAX_PQ_1[g];
		while (!pq.empty() && pq.peek() != P[pq.peek_id()])
		{
			pq.pop();
		}

		if (pq.empty())
		{
			return -1;
		}

		return pq.peek_id();
	}
	else
	{
		auto& pq = MIN_PQ_1[g];
		while (!pq.empty() && pq.peek() != P[pq.peek_id()])
		{
			pq.pop();
		}

		if (pq.empty())
		{
			return -1;
		}

		return pq.peek_id();
	}
}

int recommend_2(int opt)
{
	if (opt == 1)
	{
		auto& pq = MAX_PQ_2;
		while (!pq.empty() && pq.peek() != P[pq.peek_id()])
		{
			pq.pop();
		}

		if (pq.empty())
		{
			return -1;
		}

		return pq.peek_id();
	}
	else
	{
		auto& pq = MIN_PQ_2;
		while (!pq.empty() && pq.peek() != P[pq.peek_id()])
		{
			pq.pop();
		}

		if (pq.empty())
		{
			return -1;
		}

		return pq.peek_id();
	}
}

int recommend_3(int opt, short l)
{
	if (opt == 1)
	{
		Problem problem = { 0x7FFF, 0x7FFF, 1 };
		for (int level = l; level <= 100; ++level)
		{
			auto& pq = MIN_PQ_3[level];
			while (!pq.empty() && pq.peek() != P[pq.peek_id()])
			{
				pq.pop();
			}

			if (pq.empty())
			{
				continue;
			}

			if (pq.peek() <= problem)
			{
				problem = pq.peek();
			}
		}

		return problem.id == 0x7FFF ? -1 : problem.id;
	}
	else
	{
		Problem problem = { 0, 0, 1 };
		for (int level = 1; level < l; ++level)
		{
			auto& pq = MAX_PQ_3[level];
			while (!pq.empty() && pq.peek() != P[pq.peek_id()])
			{
				pq.pop();
			}

			if (pq.empty())
			{
				continue;
			}

			if (pq.peek() >= problem)
			{
				problem = pq.peek();
			}
		}

		return problem.id == 0 ? -1 : problem.id;
	}
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int N;
	std::cin >> N;
	while (N--)
	{
		int p, l, g;
		std::cin >> p >> l >> g;
		add(p, l, g);
	}

	char buf[20];

	int M;
	std::cin >> M;
	while (M--)
	{
		std::cin >> buf;
		if (buf[0] == 'a')
		{
			int p, l, g;
			std::cin >> p >> l >> g;
			add(p, l, g);
		}
		else if (buf[0] == 's')
		{
			int p;
			std::cin >> p;
			solve(p);
		}
		else
		{
			if (buf[9] == '2')
			{
				int opt;
				std::cin >> opt;
				std::cout << recommend_2(opt) << '\n';
			}
			else if (buf[9] == '3')
			{
				int opt, l;
				std::cin >> opt >> l;
				std::cout << recommend_3(opt, l) << '\n';
			}
			else
			{
				int g, opt;
				std::cin >> g >> opt;
				std::cout << recommend_1(opt, g) << '\n';
			}
		}
	}

	return 0;
}