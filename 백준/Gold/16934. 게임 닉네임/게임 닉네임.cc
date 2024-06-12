#include <iostream>


struct Element
{
	Element* child[26];
	int end_cnt;
	
	Element() : child{}, end_cnt{}
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
};

struct Trie
{
	Element root;

	void insert(const char* word)
	{
		insert(&root, word, true);
	}

private:
	void insert(Element* current_root, const char* word, bool print)
	{
		if (*word == 0)
		{
			current_root->end_cnt += 1;
			if (current_root->end_cnt > 1)
			{
				std::cout << current_root->end_cnt;
			}

			std::cout << '\n';

			return;
		}

		if (print)
		{
			std::cout << *word;
		}
		const int idx = *word - 'a';
		if (current_root->child[idx] == nullptr)
		{
			current_root->child[idx] = new Element;
			print = false;
		}

		insert(current_root->child[idx], word + 1, print);
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	Trie trie;

	int N;
	char buf[11];
	std::cin >> N;
	while (N--)
	{
		std::cin >> buf;
		trie.insert(buf);
	}

	return 0;
}