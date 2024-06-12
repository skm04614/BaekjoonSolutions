#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

struct Edge
{
    int v;
    Edge* next;

    Edge(int v, Edge* next) : v{ v }, next{ next }
    {

    }

    ~Edge()
    {
        if (next)
        {
            delete next;
            next = nullptr;
        }
    }
};

struct Range
{
    int start;
    int end;
} RANGES[100100];
int E;

ll SEG_TREE[400400];
ll LAZY[400400];
int N;
int M;

void dfs(Edge** edges, int node)
{
    ++E;
    RANGES[node].start = E;

    for (register const Edge* e = edges[node]; e; e = e->next)
    {
        dfs(edges, e->v);
    }

    RANGES[node].end = E;
}

void init()
{
    std::cin >> N >> M;

    Edge** edges = new Edge * [N + 1] {};

    int parent;
    std::cin >> parent;
    for (register int child = 2; child <= N; child++)
    {
        std::cin >> parent;
        edges[parent] = new Edge{ child, edges[parent] };
    }

    dfs(edges, 1);

    for (register int i = 0; i < N + 1; i++)
    {
        if (edges[i])
        {
            delete edges[i];
        }
    }
    delete[] edges;
}

void propagate(int node, int idx0, int idx1)
{
    if (LAZY[node])
    {
        SEG_TREE[node] += (idx1 - idx0 + 1) * LAZY[node];

        if (idx0 != idx1)
        {
            LAZY[node << 1] += LAZY[node];
            LAZY[node << 1 | 1] += LAZY[node];
        }

        LAZY[node] = 0;
    }
}

void update(int node, int idx0, int idx1, int left, int right, int k)
{
    propagate(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return;
    }

    if (left <= idx0 && idx1 <= right)
    {
        LAZY[node] += k;
        propagate(node, idx0, idx1);
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, left, right, k);
    update(node << 1 | 1, mid + 1, idx1, left, right, k);
    SEG_TREE[node] = SEG_TREE[node << 1] + SEG_TREE[node << 1 | 1];
}

ll query(int node, int idx0, int idx1, int target_idx)
{
    propagate(node, idx0, idx1);

    if (idx1 < target_idx || target_idx < idx0)
    {
        return 0;
    }

    if (idx0 == target_idx && target_idx == idx1)
    {
        return SEG_TREE[node];
    }

    int mid = (idx0 + idx1) >> 1;
    return query(node << 1, idx0, mid, target_idx) + query(node << 1 | 1, mid + 1, idx1, target_idx);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    init();

    for (int i = 1; i <= M; i++)
    {
        int a, b;
        std::cin >> a >> b;
        if (a == 1)
        {
            int c;
            std::cin >> c;

            update(1, 1, N, RANGES[b].start, RANGES[b].end, c);
        }
        else
        {
            std::cout << query(1, 1, N, RANGES[b].start) << '\n';
        }
    }

    return 0;
}