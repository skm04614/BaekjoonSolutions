#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Element
{
	Element* child[256];
	bool end;

	Element() : child{}, end{ false }
	{

	}

	~Element()
	{
		for (int i = 0; i < (sizeof(child) / sizeof(child[0])); i++)
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
	int dir_cnt = 0;

	void insert(const char* path)
	{
		insert(&root, path);
	}

private:
	void insert(Element* current_root, const char* path)
	{
		if (*path == 0)
		{
			return;
		}

		Element*& child = current_root->child[*path];
		if (child == nullptr)
		{
			child = new Element{};
		}

		if (*(path + 1) == '/' || *(path + 1) == 0)
		{
			if (child->end == false)
			{
				dir_cnt++;
				child->end = true;
			}
		}

		insert(child, path + 1);
	}

};



int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;
	char path[110];
	for (int t = 1; t <= T; t++)
	{
		Trie trie;

		int N, M;
		std::cin >> N >> M;
		for (int i = 0; i < N; i++)
		{
			std::cin >> path;
			trie.insert(path + 1);
		}

		int new_cnt = trie.dir_cnt;

		for (int i = 0; i < M; i++)
		{
			std::cin >> path;
			trie.insert(path + 1);
		}
		new_cnt = trie.dir_cnt - new_cnt;
		std::cout << "Case #" << t << ": " << new_cnt << '\n';
	}


	return 0;
}