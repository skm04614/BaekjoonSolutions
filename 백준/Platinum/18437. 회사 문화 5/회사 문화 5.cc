#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int OFF = 1;
constexpr int ON = -1;

struct Node
{
    int v;
    Node* next;

    Node(int v, Node* next) : v{ v }, next{ next }
    {
    }

    ~Node()
    {
        if (next)
        {
            delete next;
            next = nullptr;
        }
    }
};

Node* ADJ_LIST[100100];
int N;

struct EulerNode
{
    int start;
    int end;
};
EulerNode EN[100100];
int E;

void dfs(int v)
{
    ++E;
    EN[v].start = E;

    for (Node* node = ADJ_LIST[v]; node; node = node->next)
    {
        dfs(node->v);
    }

    if (ADJ_LIST[v])
    {
        delete ADJ_LIST[v];
        ADJ_LIST[v] = nullptr;
    }

    EN[v].end = E;
}

int SEG_TREE[400400];
int LAZY[400400];

void propagate(int node, int idx0, int idx1)
{
    if (LAZY[node])
    {
        SEG_TREE[node] = (LAZY[node] == ON ? 0 : (idx1 - idx0 + 1));

        if (idx0 != idx1)
        {
            LAZY[node << 1] = LAZY[node];
            LAZY[node << 1 | 1] = LAZY[node];
        }

        LAZY[node] = 0;
    }
}

void set(int node, int idx0, int idx1, int left, int right, bool status)
{
    propagate(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return;
    }

    if (left <= idx0 && idx1 <= right)
    {
        LAZY[node] = status ? ON : OFF;
        propagate(node, idx0, idx1);
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    set(node << 1, idx0, mid, left, right, status);
    set(node << 1 | 1, mid + 1, idx1, left, right, status);
    SEG_TREE[node] = SEG_TREE[node << 1] + SEG_TREE[node << 1 | 1];
}

int query(int node, int idx0, int idx1, int left, int right)
{
    propagate(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return SEG_TREE[node];
    }

    int mid = (idx0 + idx1) >> 1;
    return query(node << 1, idx0, mid, left, right) + query(node << 1 | 1, mid + 1, idx1, left, right);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    int parent;
    std::cin >> parent;
    for (int i = 2; i <= N; i++)
    {
        std::cin >> parent;
        ADJ_LIST[parent] = new Node{ i, ADJ_LIST[parent] };
    }

    dfs(1);

    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int a, b;
        std::cin >> a >> b;
        if (a == 3)
        {
            std::cout << EN[b].end - EN[b].start - query(1, 1, N, EN[b].start + 1, EN[b].end) << '\n';
        }
        else
        {
            set(1, 1, N, EN[b].start + 1, EN[b].end, a == 1);
        }
    }

    return 0;
}