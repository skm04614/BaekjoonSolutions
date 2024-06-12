#include <iostream>


struct Element
{
	Element() : child{}, isEnd{false}
	{

	}

	~Element()
	{
		for (int i = 0; i < 10; i++)
		{
			if (child[i])
			{
				delete child[i];
			}
		}
	}

	Element* child[10];
	bool isEnd;
};

struct Trie
{
	Element root;
	
	void insert(const char* word)
	{
		insert(&root, word);
	}

	bool is_valid() const
	{
		return is_valid(&root);
	}

private:
	void insert(Element* current_root, const char *word)
	{
		if (*word == 0)
		{
			current_root->isEnd = true;
			return;
		}

		int leading_digit = *word - '0';
		if (current_root->child[leading_digit] == nullptr)
		{
			current_root->child[leading_digit] = new Element();
		}

		return insert(current_root->child[leading_digit], word + 1);
	}

	bool is_valid(const Element* current_root) const
	{
		bool result = true;
		for (int i = 0; i < 10; i++)
		{
			if (current_root->child[i])
			{
				if (current_root->isEnd)
				{
					return false;
				}
				result &= is_valid(current_root->child[i]);
			}
		}

		return result;
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;
	char buf[11];
	while (T--)
	{
		Trie trie;

		int N;
		std::cin >> N;
		while (N--)
		{
			std::cin >> buf;
			trie.insert(buf);
		}

		std::cout << (trie.is_valid() ? "YES" : "NO") << '\n';
	}


	return 0;
}