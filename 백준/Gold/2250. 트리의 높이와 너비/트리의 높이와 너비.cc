#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

struct Node
{
    int v;
    Node* l;
    Node* r;
    Node* p;

    Node() : v{}, l{}, r{}, p{}
    {
    }
};

Node NODES[10100];
int N;

bool VISITED[10010];
int DEPTH[10010];
int MIN_X[10010];
int MAX_X[10010];
int MAX_D;
int X;

void init()
{
    for (int i = 0; i <= 10000; ++i)
    {
        MIN_X[i] = 0x7FFFFFFF;
        MAX_X[i] = 0;
    }
}

void dfs(const Node* root, int depth)
{
    if (root == nullptr || VISITED[root->v])
    {
        return;
    }

    VISITED[root->v] = true;
    DEPTH[root->v] = ++depth;
    MAX_D = max(MAX_D, depth);

    dfs(root->l, depth);

    ++X;
    MIN_X[depth] = min(MIN_X[depth], X);
    MAX_X[depth] = max(MAX_X[depth], X);

    dfs(root->r, depth);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    init();

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        int v, l, r;
        std::cin >> v >> l >> r;

        Node *node = &NODES[v];
        node->v = v;
        node->l = l == -1 ? nullptr : &NODES[l];
        node->r = r == -1 ? nullptr : &NODES[r];
        
        if (node->l)
        {
            node->l->p = node;
        }

        if (node->r)
        {
            node->r->p = node;
        }
    }

    Node* root = &NODES[1];
    while (root->p)
    {
        root = root->p;
    }
    
    dfs(root, 0);

    int res = 0;
    int lv = 0;
    for (int depth = 1; depth <= MAX_D; ++depth)
    {
        const int d = MAX_X[depth] - MIN_X[depth] + 1;
        if (d > res)
        {
            res = d;
            lv = depth;
        }
    }

    std::cout << lv << ' ' << res;

    return 0;
}
