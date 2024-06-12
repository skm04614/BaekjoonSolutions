#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Element
{
	int val;
	bool isValid;

	Element() : val{ 0 }, isValid{ true }
	{
	}

	bool operator>(const Element& other) const
	{
		return val > other.val;
	}
};

struct Heap
{
	Element* data[1000100];
	int  size;
	bool ascending;

	Heap(bool ascending) : ascending{ ascending }, size{ 0 }, data{}
	{
	}

	void push(Element* e)
	{
		data[++size] = e;

		for (int c = size;;)
		{
			if (c <= 1)
			{
				break;
			}

			int p = c / 2;
			if ((*data[c] > *data[p]) ^ ascending)
			{
				Element* tmp = data[c];
				data[c] = data[p];
				data[p] = tmp;
				c = p;
			}
			else
			{
				break;
			}
		}
	}

	Element* pop()
	{
		if (size == 0)
		{
			return nullptr;
		}

		Element* ret = data[1];
		data[1] = data[size--];

		for (int p = 1;;)
		{
			int c = 2 * p;
			if (c > size)
			{
				break;
			}

			if (c + 1 <= size && ((*data[c + 1] > *data[c]) ^ ascending))
			{
				c = c + 1;
			}

			if ((*data[c] > *data[p]) ^ ascending)
			{
				Element* tmp = data[c];
				data[c] = data[p];
				data[p] = tmp;
				p = c;
			}
			else
			{
				break;
			}
		}

		return ret;
	}
};

struct DoublePriorityQueue
{
	Heap min_heap{ true };
	Heap max_heap{ false };
	int size = 0;

	void push(Element* e)
	{
		max_heap.push(e);
		min_heap.push(e);
	}

	Element* pop_max()
	{
		for (;;)
		{
			Element* ret = max_heap.pop();
			if (ret == nullptr)
			{
				return ret;
			}

			if (ret->isValid)
			{
				ret->isValid = false;
				return ret;
			}
		}
	}

	Element* pop_min()
	{
		for (;;)
		{
			Element* ret = min_heap.pop();
			if (ret == nullptr)
			{
				return ret;
			}

			if (ret->isValid)
			{
				ret->isValid = false;
				return ret;
			}
		}
	}

	void clear()
	{
		size = 0;
		max_heap.size = 0;
		min_heap.size = 0;
	}
};

DoublePriorityQueue DPQ;

Element POOL[1000100];
int P;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		P = 0;
		DPQ.clear();

		int k;
		std::cin >> k;
		for (int i = 0; i < k; i++)
		{
			char op;
			int val;
			std::cin >> op >> val;

			if (op == 'D')
			{
				if (val == 1)
				{
					DPQ.pop_max();
				}
				else
				{
					DPQ.pop_min();
				}
			}
			else
			{
				Element& e = POOL[P++];
				e.isValid = true;
				e.val = val;
				DPQ.push(&e);
			}
		}

		Element* max = DPQ.pop_max();
		Element* min = DPQ.pop_min();

		if (max == nullptr)
		{
			std::cout << "EMPTY" << '\n';
		}
		else
		{
			std::cout << max->val << ' ';
			if (min == nullptr)
			{
				std::cout << max->val;
			}
			else
			{
				std::cout << min->val;
			}
			std::cout << '\n';
		}
	}

	return 0;
}