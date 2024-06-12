#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
    Node* child[2];
    bool end;

    Node() : child{}, end{ false }
    {

    }

    ~Node()
    {
        delete child[0];
        delete child[1];
        child[0] = child[1] = nullptr;
    }
};

struct Trie
{
    Node* root;

    Trie()
    {
        root = new Node{};
    }

    ~Trie()
    {
        delete root;
        root = nullptr;
    }

    bool insert(char* buf, int n)
    {
        return insert(root, buf, n);
    }

    bool insert(Node* node, char* buf, int n)
    {
        if (n == 0)
        {
            *buf = 0;
            return node->end = true;
        }

        for (int i = 0; i < 2; ++i)
        {
            *buf = '0' + i;

            Node*& c = node->child[i];
            if (c == nullptr)
            {
                c = new Node{};
            }

            if (c->end)
            {
                continue;
            }

            if (insert(c, buf + 1, n - 1))
            {
                return true;
            }
        }

        return false;
    }

    bool is_valid() const
    {
        return is_valid(root, 0);
    }

    bool is_valid(const Node* node, int cnt) const
    {
        if (node == nullptr)
        {
            return cnt <= 1;
        }

        if (node->end)
        {
            ++cnt;
        }

        return is_valid(node->child[0], cnt) && is_valid(node->child[1], cnt);
    }
};

struct Query
{
    int nth;
    int l;

    bool operator>=(const Query& other) const
    {
        return l >= other.l;
    }
};

Query QUERIES[1010];
char REC[1010][1010];
int Q;

inline void swap(Query& x, Query& y)
{
    Query tmp = x;
    x = y;
    y = tmp;
}

void sort(Query* arr, int size)
{
    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            c = p;
        }
    }

    for (int s = size; s >= 1; --s)
    {
        swap(arr[1], arr[s]);
        const int max_s = s - 1;

        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && arr[c | 1] >= arr[c])
            {
                c |= 1;
            }

            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    Trie trie;

    std::cin >> Q;
    for (int i = 1; i <= Q; ++i)
    {
        QUERIES[i].nth = i;
        std::cin >> QUERIES[i].l;
    }

    sort(QUERIES, Q);

    bool success = true;
    for (int i = 1; i <= Q; ++i)
    {
        const Query& q = QUERIES[i];

        if (!trie.insert(REC[q.nth], q.l))
        {
            success = false;
            break;
        }
    }

    if (success)
    {
        std::cout << 1 << '\n';
        for (int i = 1; i <= Q; ++i)
        {
            std::cout << REC[i] << '\n';
        }
    }
    else
    {
        std::cout << -1;
    }

    return 0;
}