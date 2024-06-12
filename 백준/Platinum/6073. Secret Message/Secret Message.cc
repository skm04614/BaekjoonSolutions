#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Element
{
	Element* child[2];
	int end_cnt;
	int cnt;

	Element() : child{}, end_cnt{ 0 }, cnt{ 0 }
	{

	}

	~Element()
	{
		for (int i = 0; i < 2; i++)
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

	void insert(const int* arr, int size)
	{
		Element* current_root = &root;
		for (int i = 0; i < size; i++)
		{
			Element*& child = current_root->child[arr[i]];
			if (child == nullptr)
			{
				child = new Element{};
			}

			current_root->cnt++;
			current_root = child;
		}

		current_root->end_cnt++;
	}

	int query(const int* arr, int size) const
	{
		const Element* current_root = &root;
		int result = 0;

		for (int i = 0; i < size; i++)
		{
			current_root = current_root->child[arr[i]];
			if (current_root == nullptr)
			{
				break;
			}
			result += current_root->end_cnt;
		}

		if (current_root)
		{
			result += current_root->cnt;
		}
		return result;
	}
};

int WORD[50050];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	Trie trie;

	int N, M;
	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		int size;
		std::cin >> size;
		for (int j = 0; j < size; j++)
		{
			std::cin >> WORD[j];
		}
		trie.insert(WORD, size);
	}

	for (int i = 0; i < M; i++)
	{
		int size;
		std::cin >> size;
		for (int j = 0; j < size; j++)
		{
			std::cin >> WORD[j];
		}
		std::cout << trie.query(WORD, size) << '\n';
	}

	return 0;
}