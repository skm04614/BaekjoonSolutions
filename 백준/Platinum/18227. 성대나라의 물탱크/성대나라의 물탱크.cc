#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[400400];
Edge* EDGES[200200];

bool VISITED[200200];
int S[200200];
int E[200200];
int DEPTH[200200];

int N;
int C;

int dfs(int node, int cnt, int depth)
{
    VISITED[node] = true;
    S[node] = ++cnt;
    DEPTH[node] = ++depth;

    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        if (VISITED[e->v])
        {
            continue;
        }

        cnt = dfs(e->v, cnt, depth);
    }

    return E[node] = cnt;
}

int SEG[800800];

void add(int node, int idx0, int idx1, int target_idx)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (idx0 == target_idx && target_idx == idx1)
    {
        ++SEG[node];
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    add(node << 1, idx0, mid, target_idx);
    add(node << 1 | 1, mid + 1, idx1, target_idx);

    SEG[node] = SEG[node << 1] + SEG[node << 1 | 1];
}

void add(int city)
{
    add(1, 1, N, S[city]);
}

int query(int node, int idx0, int idx1, int left, int right)
{
    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return SEG[node];
    }

    int mid = (idx0 + idx1) >> 1;
    return query(node << 1, idx0, mid, left, right) + query(node << 1 | 1, mid + 1, idx1, left, right);
}

unsigned long long query(int city)
{
    return static_cast<unsigned long long>(query(1, 1, N, S[city], E[city])) * DEPTH[city];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> C;
    for (int i = 0; i < N - 1; ++i)
    {
        int v1, v2;
        std::cin >> v1 >> v2;

        Edge& e1 = POOL[i << 1];
        Edge& e2 = POOL[i << 1 | 1];

        e1.v = v2;
        e1.next = EDGES[v1];
        EDGES[v1] = &e1;

        e2.v = v1;
        e2.next = EDGES[v2];
        EDGES[v2] = &e2;
    }

    dfs(C, 0, 0);

    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int a, b;
        std::cin >> a >> b;
        if (a == 1)
        {
            add(b);
        }
        else
        {
            std::cout << query(b) << '\n';
        }
    }

    return 0;
}