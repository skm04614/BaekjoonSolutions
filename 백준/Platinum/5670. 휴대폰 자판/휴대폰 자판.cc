#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

struct Element
{
	Element* child[26];
	int n_child;
	bool end;

	Element() : child{}, end{ false }, n_child{ 0 }
	{

	}

	~Element()
	{
		for (int i = 0; i < 26; i++)
		{
			if (child[i])
			{
				delete child[i];
			}
		}
	}

	Element* add_or_get_child(const char c)
	{
		Element*& _child = child[c - 'a'];
		if (_child == nullptr)
		{
			_child = new Element{};
			n_child++;
		}
		return _child;
	}
};

struct Trie
{
	Element root;
	int n_words;

	Trie() : root{}, n_words{ 0 }
	{

	}

	void insert(const char* word)
	{
		Element* current = &root;
		while (*word)
		{
			current = current->add_or_get_child(*word++);
		}
		current->end = true;
		n_words++;
	}

	double query() const
	{
		return query(&root, root.n_child == 1) / n_words;
	}

private:
	double query(const Element* current, double cost) const
	{
		double result = current->end ? cost : 0;

		if (current->n_child > 1 || current->end)
		{
			cost++;
		}

		for (int i = 0; i < 26; i++)
		{
			if (current->child[i] == nullptr)
			{
				continue;
			}
			result += query(current->child[i], cost);
		}

		return result;
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	char buf[81];
	int N;
	while (std::cin >> N)
	{
		Trie trie;
		for (int i = 0; i < N; i++)
		{
			std::cin >> buf;
			trie.insert(buf);
		}
		std::cout << std::fixed << std::setprecision(2) << trie.query() << '\n';
	}

	return 0;
}