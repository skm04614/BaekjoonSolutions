#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Element
{
	char c;
	Element* child;
	Element* next;
	bool end;

	Element(char c = 0) : c{ c }, end { false }, child{}, next{}
	{

	}

	~Element()
	{
		if (child)
		{
			delete child;
		}

		if (next)
		{
			delete next;
		}
	}

	Element* get_child(const char c) const
	{
		if (child == nullptr)
		{
			return nullptr;
		}

		Element* node = child;
		for (; node->next; node = node->next)
		{
			if (node->next->c == c)
			{
				return node->next;
			}

			if (node->next->c > c)
			{
				break;
			}
		}

		return nullptr;
	}

	Element* get_or_add_child(const char c)
	{
		if (child == nullptr)
		{
			child = new Element{};
		}

		Element* node = child;
		for (; node->next; node = node->next)
		{
			if (node->next->c == c)
			{
				return node->next;
			}

			if (node->next->c > c)
			{
				break;
			}
		}

		Element* e = new Element{c};
		e->next = node->next;
		node->next = e;

		return e;
	}
};

struct Trie
{
	Element root;

	void insert(const char* word)
	{
		Element* current_root = &root;
		while (*word)
		{
			current_root = current_root->get_or_add_child(*word);
			word++;
		}
		current_root->end = true;
	}

	void search(const char* word, bool* result) const
	{
		const Element* current_root = &root;
		int n = 0;
		while (*word)
		{
			current_root = current_root->get_child(*word);
			if (current_root == nullptr)
			{
				break;
			}

			if (current_root->end)
			{
				result[n] = true;
			}
			word++;
			n++;
		}
	}
};

Trie COLOR_TRIE;
Trie TEAM_TRIE;

int _slen(const char* s)
{
	int len = 0;
	while (*s++) { len++; }
	return len;
}

int _s_rvscpy(char* dest, const char* src)
{
	int len = _slen(src);
	for (int i = 0; i < len; i++)
	{
		dest[i] = src[len - i - 1];
	}
	dest[len] = 0;

	return len;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	char buf[2010] = {};
	char buf_rvsd[2010] = {};
	int N, M;
	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		std::cin >> buf;
		COLOR_TRIE.insert(buf);
	}

	for (int i = 0; i < M; i++)
	{
		std::cin >> buf;
		_s_rvscpy(buf_rvsd, buf);
		TEAM_TRIE.insert(buf_rvsd);
	}

	int K;
	std::cin >> K;

	bool color[2010]{};
	bool team[2010]{};
	for (int i = 0; i < K; i++)
	{
		std::cin >> buf;
		int len = _s_rvscpy(buf_rvsd, buf);

		for (int i = 0; i < len; i++)
		{
			color[i] = team[i] = false;
		}

		COLOR_TRIE.search(buf, color);
		TEAM_TRIE.search(buf_rvsd, team);

		bool is_valid = false;
		for (int i = 0; i < len - 1; i++)
		{
			if (color[i] && team[len - i - 2])
			{
				is_valid = true;
				break;
			}
		}

		std::cout << (is_valid ? "Yes" : "No") << '\n';
	}

	return 0;
}