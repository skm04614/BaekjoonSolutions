#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


void s_cpy(char* dest, const char* src)
{
	while (*dest++ = *src++);
}

int s_cmp(const char* s1, const char* s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 == 0 && *s2 == 0)
	{
		return 0;
	}

	return *s1 > *s2 ? 1 : -1;
}


struct Element
{
	char val[11];
	int size;

	Element() : val{}, size{}
	{
	}

	Element(const char* val) : Element{}
	{
		char* ptr = this->val;
		while (*ptr++ = *val++) { size++; }
	}

	int cmp(const Element& other) const
	{
		char c1[22]{};
		s_cpy(c1, val);
		s_cpy(c1 + size, other.val);

		char c2[22]{};
		s_cpy(c2, other.val);
		s_cpy(c2 + other.size, val);

		return s_cmp(c1, c2);
	}

	void print() const
	{
		std::cout << val;
	}

	bool is_null() const
	{
		for (int i = 0; i < size; i++)
		{
			if (val[i] > '0')
			{
				return false;
			}
		}

		return true;
	}
};

Element ARR[1010];
int N;

inline void swap(Element& e1, Element& e2)
{
	Element tmp = e1;
	e1 = e2;
	e2 = tmp;
}

void q_sort(Element* arr, int idx0, int idx1)
{
	if (idx0 >= idx1)
	{
		return;
	}

	int pivot = idx0;
	int left = pivot + 1;
	int right = idx1;

	for (;;)
	{
		while (left <= right && arr[right].cmp(arr[pivot]) != 1)
		{
			right--;
		}

		while (left <= right && arr[left].cmp(arr[pivot]) != -1)
		{
			left++;
		}

		if (left > right)
		{
			swap(arr[pivot], arr[right]);
			break;
		}

		swap(arr[left], arr[right]);
	}

	q_sort(arr, idx0, right - 1);
	q_sort(arr, right + 1, idx1);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;

	char buf[11];
	for (int i = 0; i < N; i++)
	{
		std::cin >> buf;
		ARR[i] = Element{ buf };
	}

	q_sort(ARR, 0, N - 1);

	if (ARR[0].is_null())
	{
		std::cout << 0;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			ARR[i].print();
		}
	}

	return 0;
}