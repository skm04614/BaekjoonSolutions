#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

template <typename T>
void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

struct Heap
{
	ull data[1001000];
	int size;

	void push(ull val)
	{
		data[++size] = val;

		register int c = size;
		while (c > 1)
		{
			register int p = c >> 1;
			if (data[p] <= data[c])
			{
				break;
			}
			swap(data[p], data[c]);
			c = p;
		}
	}

	ull pop()
	{
		ull ret = data[1];
		swap(data[1], data[size--]);

		register int p = 1;
		register int c = p << 1;
		while (c <= size)
		{
			if ((c | 1) <= size && data[c | 1] <= data[c])
			{
				c |= 1;
			}

			if (data[p] <= data[c])
			{
				break;
			}
			swap(data[p], data[c]);
			p = c;
			c = p << 1;
		}

		return ret;
	}

	void reset()
	{
		size = 0;
	}

	int get_size() const
	{
		return size;
	}
} HQ;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;
	while (T--)
	{
		HQ.reset();

		int N;
		std::cin >> N;
		for (register int i = 0; i < N; i++)
		{
			int val;
			std::cin >> val;
			HQ.push(val);
		}

		register ull cost = 0;
		while (HQ.get_size() > 1)
		{
			register ull  current = HQ.pop() + HQ.pop();

			cost += current;
			HQ.push(current);
		}

		std::cout << cost << '\n';
	}

	return 0;
}