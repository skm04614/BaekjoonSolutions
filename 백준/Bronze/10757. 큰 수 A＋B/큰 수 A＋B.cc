#include <cstdio>

char BUF[10002];

template <typename T>
void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

inline int ctoi(const char &c)
{
	return c - '0';
}

inline char itoc(const int &i)
{
	return i + '0';
}

struct bigint
{
	int		size;
	char	data[10002];

	bigint(char* data = nullptr) : data{}, size{ 0 }
	{
		if (data == nullptr) return;

		for (int i = 0; data[i]; i++)
		{
			this->data[i] = data[i];
			size++;
		}

		for (int i = 0; i < size / 2; i++)
		{
			swap(this->data[i], this->data[size - 1 - i]);
		}
	}

	bigint(char* data, int size) : data{}, size{size}
	{
		for (int i = 0; i < size; i++)
		{
			this->data[i] = data[i];
		}
	}

	bigint operator+(const bigint& other)
	{
		char buf[10002]{};
		int carry{};
		const bigint& bigger = (other.size >= this->size) ? other : *this;
		const bigint& smaller = (other.size >= this->size) ? *this : other;
		int size = bigger.size;

		for (int i = 0; i < bigger.size; i++)
		{
			int tmp = ctoi(bigger.data[i]) + carry;
			if (i < smaller.size)
			{
				tmp += ctoi(smaller.data[i]);
			}
			buf[i] = itoc(tmp % 10);
			carry = tmp / 10;
		}

		if (carry)
		{
			buf[size++] = itoc(carry);
		}

		return bigint{ buf, size };
	}

	void print(void) const
	{
		for (int i = size - 1; i >= 0; i--)
		{
			printf("%c", data[i]);
		}
	}
};



int main(void)
{
	scanf("%s", BUF);
	bigint A{ BUF };
	scanf("%s", BUF);
	bigint B{ BUF };
	bigint C = A + B;
	C.print();

	return 0;
}