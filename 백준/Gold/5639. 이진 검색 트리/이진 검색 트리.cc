#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
	int val;
	Node* left;
	Node* right;

	Node(int val) : val{ val }, left{ nullptr }, right{ nullptr }
	{
	}

	~Node()
	{
		if (left)
		{
			delete left;
		}
		if (right)
		{
			delete right;
		}
	}
};

struct BST
{
	Node* root;

	BST() : root{ nullptr }
	{
	}

	~BST()
	{
		if (root)
		{
			delete root;
		}
	}

	void insert(int val)
	{
		if (root == nullptr)
		{
			root = new Node{ val };
		}
		else
		{
			for (Node* current = root;;)
			{
				if (val < current->val)
				{
					if (current->left == nullptr)
					{
						current->left = new Node{ val };
						return;
					}

					current = current->left;
				}
				else
				{
					if (current->right == nullptr)
					{
						current->right = new Node{ val };
						return;
					}

					current = current->right;
				}
			}
		}
	}
};

BST GBST;

void sol(Node* root)
{
	if (root == nullptr)
	{
		return;
	}

	sol(root->left);
	sol(root->right);
	std::cout << root->val << '\n';
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int val;
	while (std::cin >> val)
	{
		GBST.insert(val);
	}

	sol(GBST.root);

	return 0;
}