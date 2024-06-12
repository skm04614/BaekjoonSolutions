#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

struct Node
{
    int val;
    int cnt;
    Node* l;
    Node* r;

    Node(int val, int cnt) : val{ val }, cnt{ cnt }, l{}, r{}
    {

    }

    ~Node()
    {
        delete l;
        delete r;
        l = r = nullptr;
    }
};

struct Element
{
    int val;
    int cnt;

    bool is_valid() const
    {
        return cnt <= 8;
    }

    Element operation(int opt, const Element& other) const
    {
        if (opt == 0)
        {
            return { val + other.val, cnt + other.cnt };
        }

        if (opt == 1)
        {
            return { val - other.val, cnt + other.cnt };
        }

        if (opt == 2)
        {
            return { val * other.val, cnt + other.cnt };
        }

        return { val / other.val, cnt + other.cnt };
    }
};

struct BinarySearchTree
{
    Node* root;

    BinarySearchTree() : root{}
    {

    }

    ~BinarySearchTree()
    {
        delete root;
        root = nullptr;
    }

    void insert(int val, int cnt)
    {
        if (val == 0)
        {
            return;
        }

        if (root == nullptr)
        {
            root = new Node{ val, cnt };
            return;
        }

        Node* current = root;
        for (;;)
        {
            if (val == current->val)
            {
                current->cnt = min(cnt, current->cnt);
                break;
            }

            if (val < current->val)
            {
                if (current->l == nullptr)
                {
                    current->l = new Node{ val, cnt };
                }
                current = current->l;
            }
            else
            {
                if (current->r == nullptr)
                {
                    current->r = new Node{ val, cnt };
                }
                current = current->r;
            }
        }
    }

    int search(int val)
    {
        if (root == nullptr)
        {
            return 0;
        }

        Node* current = root;
        for (;;)
        {
            if (val == current->val)
            {
                break;
            }

            if (val < current->val)
            {
                if (current->l == nullptr)
                {
                    break;
                }
                current = current->l;
            }
            else
            {
                if (current->r == nullptr)
                {
                    break;
                }
                current = current->r;
            }
        }

        return current->val == val ? current->cnt : 0;
    }

    void copy(Element* arr, int& size)
    {
        copy(root, arr, size);
    }

private:
    void copy(Node* node, Element* arr, int& size)
    {
        if (node == nullptr)
        {
            return;
        }

        copy(node->l, arr, size);
        arr[++size] = { node->val, node->cnt };
        copy(node->r, arr, size);
    }
};

Element ARR[65000];
int N;

BinarySearchTree BST;
int K;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> K;
    for (int n = 1, val = K; n <= 8; ++n, val = 10 * val + K)
    {
        BST.insert(val, n);
    }

    for (int i = 1; i < 8; ++i)
    {
        N = 0;
        BST.copy(ARR, N);
        for (int j = 1; j <= N; ++j)
        {
            for (int k = 1; k <= N; ++k)
            {
                for (int l = 0; l < 4; ++l)
                {
                    const Element e = ARR[j].operation(l, ARR[k]);
                    if (e.is_valid())
                    {
                        BST.insert(e.val, e.cnt);
                    }
                }
            }
        }
    }

    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int val;
        std::cin >> val;

        int res = BST.search(val);
        if (res)
        {
            std::cout << res << '\n';
        }
        else
        {
            std::cout << "NO" << '\n';
        }
    }

    return 0;
}
