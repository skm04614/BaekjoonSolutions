#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

bool streq(const char* s1, const char* s2)
{
	while (*s1++ == *s2++)
	{
		if (*s1 == 0 && *s2 == 0)
		{
			return true;
		}
	}
	return false;
}

class Word
{
public:
	Word()
		: Word{ "" }
	{
	}

	Word(const char* word)
		: buf{}, len{}
	{
		for (len = 0; word[len]; len++)
		{
			buf[len] = word[len];
		}
		buf[len] = 0;
	}

	bool operator>(const Word& other) const
	{
		if (len == other.len)
		{
			for (int i = 0; i < len; i++)
			{
				if (buf[i] != other.buf[i])
				{
					return buf[i] < other.buf[i];
				}
			}
		}

		return len < other.len;
	}

	void print() const
	{
		std::cout << buf << '\n';
	}

	char buf[51];
	int len;
};

Word Words[20010];
Word Tmp[20010];

template <typename T>
void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
void merge_sort(T* arr, T* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) / 2;

	merge_sort(arr, tmp, idx0, mid);
	merge_sort(arr, tmp, mid + 1, idx1);

	int left = idx0;
	int right = mid + 1;
	int i = 0;
	for (;;)
	{
		if (left > mid)
		{
			break;
		}

		if (right > idx1)
		{
			break;
		}

		if (arr[left] > arr[right])
		{
			tmp[i++] = arr[left++];
		}
		else
		{
			tmp[i++] = arr[right++];
		}
	}

	while (left <= mid)
	{
		tmp[i++] = arr[left++];
	}

	while (right <= idx1)
	{
		tmp[i++] = arr[right++];
	}

	for (int j = 0; j < i; j++)
	{
		arr[idx0 + j] = tmp[j];
	}
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;

	char buf[51];
	for (int i = 0; i < n; i++)
	{
		std::cin >> buf;
		Words[i] = Word{ buf };
	}

	merge_sort(Words, Tmp, 0, n - 1);

	 
	const char* current_word = "";
	for (int i = 0; i < n; i++)
	{
		if (streq(current_word, Words[i].buf))
		{
			continue;
		}

		current_word = Words[i].buf;
		Words[i].print();
	}

	return 0;
}