#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[100100];
Edge* EDGES[100100];
int N;

int S[100100];
int E[100100];

int dfs(int v, int val)
{
    S[v] = ++val;

    for (const Edge* e = EDGES[v]; e; e = e->next)
    {
        val = dfs(e->v, val);
    }

    E[v] = val;

    return val;
}

int SEG[400400];

void update(int node, int idx0, int idx1, int target_idx, int k)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (target_idx == idx0 && idx1 == target_idx)
    {
        SEG[node] += k;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, target_idx, k);
    update(node << 1 | 1, mid + 1, idx1, target_idx, k);

    SEG[node] = SEG[node << 1] + SEG[node << 1 | 1];
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


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int Q;
    int parent;
    std::cin >> N >> Q >> parent;
    for (int i = 2; i <= N; ++i)
    {
        std::cin >> parent;
        
        Edge& e = POOL[i];
        e.v = i;
        e.next = EDGES[parent];
        EDGES[parent] = &e;
    }

    dfs(1, 0);

    while (Q--)
    {
        int opt;
        std::cin >> opt;
        if (opt == 1)
        {
            int v, k;
            std::cin >> v >> k;
            update(1, 1, N, S[v], k);
        }
        else
        {
            int v;
            std::cin >> v;
            std::cout << query(1, 1, N, S[v], E[v]) << '\n';
        }
    }

    return 0;
}