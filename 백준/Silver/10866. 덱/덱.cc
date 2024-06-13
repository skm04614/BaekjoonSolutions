#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int SIZE = 10010;

class Deque
{
public:
	Deque() : left{ SIZE }, right{ SIZE - 1 }, data{}
	{
	}

	void push_front(int val)
	{
		data[--left % SIZE] = val;
	}

	void push_back(int val)
	{
		data[++right % SIZE] = val;
	}

	int pop_front()
	{
		if (empty())
		{
			return -1;
		}

		return data[left++ % SIZE];
	}

	int pop_back()
	{
		if (empty())
		{
			return -1;
		}

		return data[right-- % SIZE];
	}

	int size()
	{
		return right - left + 1;
	}

	int empty()
	{
		return size() == 0;
	}

	int front()
	{
		if (empty())
		{
			return -1;
		}

		return data[left % SIZE];
	}

	int back()
	{
		if (empty())
		{
			return -1;
		}

		return data[right % SIZE];
	}

private:
	int data[SIZE];
	int left;
	int right;
};

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	int val;
	char buf[100];
	Deque dq;
	for (int i = 0; i < n; i++)
	{
		std::cin >> buf;
		switch (buf[0])
		{
		case 's':
			std::cout << dq.size() << '\n';
			break;
		case 'e':
			std::cout << dq.empty() << '\n';
			break;
		case 'f':
			std::cout << dq.front() << '\n';
			break;
		case 'b':
			std::cout << dq.back() << '\n';
			break;
		default:
			switch (buf[5])
			{
			case 'f':
				std::cin >> val;
				dq.push_front(val);
				break;
			case 'b':
				std::cin >> val;
				dq.push_back(val);
				break;
			case 'r':
				std::cout << dq.pop_front() << '\n';
				break;
			case 'a':
				std::cout << dq.pop_back() << '\n';
				break;
			default:
				break;
			}
			break;
		}
	}

	return 0;
}