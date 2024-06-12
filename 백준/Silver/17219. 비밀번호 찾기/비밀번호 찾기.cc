#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

bool _streq(const char* s1, const char* s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return *s1 == 0 && *s2 == 0;
}

void _strcpy(char* dest, const char* src)
{
	while (*dest++ = *src++);
}

struct Element
{
	char key[21];
	char val[21];
	Element* next;
	
	Element(const char* key, const char* val) : next{ nullptr }
	{
		_strcpy(this->key, key);
		_strcpy(this->val, val);
	}
};

struct HashMap
{
	static constexpr int SIZE = 100003;
	Element* data[SIZE];

	~HashMap()
	{
		for (int i = 0; i < SIZE; i++)
		{
			const Element* current = data[i];
			while (current)
			{
				const Element* bkup = current;
				current = current->next;
				delete bkup;
			}
		}
	}

	void push(const char* key, const char* val)
	{
		const ull hash = get_hash(key);

		Element* e = new Element{key, val};
		if (data[hash] == nullptr)
		{
			data[hash] = e;
		}
		else
		{
			Element* current = data[hash];
			for (; current->next; current = current->next);
			current->next = e;
		}
	}

	const char* get(const char* key)
	{
		const ull hash = get_hash(key);
		
		Element* current = data[hash];
		for (; !_streq(current->key, key); current = current->next);
		
		return current->val;
	}

	static ull get_hash(const char* s)
	{
		ull hash = 5381;

		while (*s)
		{
			hash = (((hash << 5) + hash + *s) % SIZE);
			s++;
		}
		
		return hash;
	}
};

HashMap HM;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	char key[21];
	char val[21];
	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		std::cin >> key >> val;
		HM.push(key, val);
	}

	for (int i = 0; i < M; i++)
	{
		std::cin >> key;
		std::cout << HM.get(key) << '\n';
	}

	return 0;
}