#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


template <typename T>
inline void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}


struct MinHeap
{
	int data[100010];
	int size;

	MinHeap() : size{ 0 }, data{}
	{

	}

	void push(int val)
	{
		data[++size] = val;

		int idx = size;
		while (idx > 1)
		{
			if (data[idx] < data[idx / 2])
			{
				swap(data[idx], data[idx / 2]);
				idx /= 2;
			}
			else
			{
				break;
			}
		}
	}

	int pop()
	{
		if (size == 0)
		{
			return 0;
		}

		int ret = data[1];
		swap(data[1], data[size--]);
		
		int idx = 1;
		for (;;)
		{
			const int lchidx = 2 * idx;
			const int rchidx = lchidx + 1;

			if (lchidx > size)
			{
				break;
			}

			int chidx = lchidx;
			if (size >= rchidx && data[rchidx] < data[lchidx])
			{
				chidx = rchidx;
			}

			if (data[chidx] < data[idx])
			{
				swap(data[chidx], data[idx]);
				idx = chidx;
			}
			else
			{
				break;
			}
		}

		return ret;
	}



};

MinHeap g_min_heap;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, val;
	std::cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		std::cin >> val;

		if (val == 0)
		{
			std::cout << g_min_heap.pop() << '\n';
		}
		else
		{
			g_min_heap.push(val);
		}
	}

	return 0;
}