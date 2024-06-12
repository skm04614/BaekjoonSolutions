#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

bool _streq(const char* s1, const char* s2)
{
	while (*s1 && *s2 && *s1++ == *s2++);

	return *s1 == 0 && *s2 == 0;
}

struct Element
{
	char name[21];
	int n;
	Element* next;

	Element(const char* name, int n, Element* next) : name{}, n { n }, next{ next }
	{
		char* ptr = this->name;
		while (*ptr++ = *name++);
	}

	~Element()
	{
		if (next)
		{
			delete next;
			next = nullptr;
		}
	}
};

struct Dict
{
	static constexpr int SIZE = 301943;
	Element* data[SIZE];
	int N;

	Dict() : data{}, N{ 0 }
	{

	}

	~Dict()
	{
		reset();
	}

	void reset()
	{
		N = 0;
		for (register int i = 0; i < SIZE; i++)
		{
			if (data[i])
			{
				delete data[i];
				data[i] = nullptr;
			}
		}
	}

	int insert_or_get(const char* s)
	{
		Element* e = find(s);
		if (e)
		{
			return e->n;
		}

		ull hash = get_hash(s);
		Element* new_e = new Element{ s, ++N, data[hash] };
		data[hash] = new_e;

		return new_e->n;
	}

private:
	Element *find(const char* s)
	{
		ull hash = get_hash(s);

		for (Element* element = data[hash]; element; element = element->next)
		{
			if (_streq(element->name, s))
			{
				return element;
			}
		}

		return nullptr;
	}

	static ull get_hash(const char* s)
	{
		ull hash = 5381;
		while (*s)
		{
			hash = ((hash << 5) + hash + *s) % SIZE;
			s++;
		}

		return hash;
	}
};

Dict DICT;
int COUNT[200200];
int PARENT[200200];

void init()
{
	for (register int i = 0; i < 200200; i += 8)
	{
		COUNT[i] = 1;
		COUNT[i + 1] = 1;
		COUNT[i + 2] = 1;
		COUNT[i + 3] = 1;
		COUNT[i + 4] = 1;
		COUNT[i + 5] = 1;
		COUNT[i + 6] = 1;
		COUNT[i + 7] = 1;

		PARENT[i] = i;
		PARENT[i + 1] = i + 1;
		PARENT[i + 2] = i + 2;
		PARENT[i + 3] = i + 3;
		PARENT[i + 4] = i + 4;
		PARENT[i + 5] = i + 5;
		PARENT[i + 6] = i + 6;
		PARENT[i + 7] = i + 7;
	}
}

int find(int v)
{
	if (PARENT[v] == v)
	{
		return v;
	}

	return PARENT[v] = find(PARENT[v]);
}

int _union(int v1, int v2)
{
	v1 = find(v1);
	v2 = find(v2);

	if (v1 < v2)
	{
		PARENT[v2] = v1;
		COUNT[v1] += COUNT[v2];
		COUNT[v2] = 0;
		return COUNT[v1];
	}
	else if (v1 > v2)
	{
		PARENT[v1] = v2;
		COUNT[v2] += COUNT[v1];
		COUNT[v1] = 0;
		return COUNT[v2];
	}

	return COUNT[v1];
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;
	while (T--)
	{
		DICT.reset();
		init();

		char name1[21];
		char name2[21];

		int M;
		std::cin >> M;
		while (M--)
		{
			std::cin >> name1 >> name2;

			int v1 = DICT.insert_or_get(name1);
			int v2 = DICT.insert_or_get(name2);

			std::cout << _union(v1, v2) << '\n';
		}
	}

	return 0;
}