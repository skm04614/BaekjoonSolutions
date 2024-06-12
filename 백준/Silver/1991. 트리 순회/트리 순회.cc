#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
	char c;
	Node* left;
	Node* right;
};

Node POOL[26];
int N;
Node* root;

void pre_traverse(Node* current)
{
	if (current == nullptr)
	{
		return;
	}

	std::cout << current->c;
	pre_traverse(current->left);
	pre_traverse(current->right);
}

void in_order_traverse(Node* current)
{
	if (current == nullptr)
	{
		return;
	}

	in_order_traverse(current->left);
	std::cout << current->c;
	in_order_traverse(current->right);
}

void post_traverse(Node* current)
{
	if (current == nullptr)
	{
		return;
	}

	post_traverse(current->left);

	post_traverse(current->right);
	std::cout << current->c;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	for (int i = 0; i < 26; i++)
	{
		POOL[i].c = 'A' + i;
		POOL[i].left = nullptr;
		POOL[i].right = nullptr;
	}
	root = &POOL[0];

	std::cin >> N;
	
	char c, l, r;
	for (int i = 0; i < N; i++)
	{
		std::cin >> c >> l >> r;
		Node* parent = &POOL[c - 'A'];
		if (l != '.')
		{
			parent->left = &POOL[l - 'A'];
		}

		if (r != '.')
		{
			parent->right = &POOL[r - 'A'];
		}
	}

	pre_traverse(root);
	std::cout << '\n';
	in_order_traverse(root);
	std::cout << '\n';
	post_traverse(root);

	return 0;
}