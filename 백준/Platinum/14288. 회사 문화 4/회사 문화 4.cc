#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[100100];
Edge* EDGES[100100];
int S[100100];
int E[100100];
int N;

bool RVSD = false;

int dfs(int node, int val)
{
    S[node] = ++val;

    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        val = dfs(e->v, val);
    }

    return E[node] = val;
}

ull SEG[400400];
ull LAZY[400400];

void propagate(int node, int idx0, int idx1)
{
    if (LAZY[node])
    {
        SEG[node] += (LAZY[node] * (idx1 - idx0 + 1));

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

    SEG[node] = SEG[node << 1] + SEG[node << 1 | 1];
}

ull query(int node, int idx0, int idx1, int target_idx)
{
    propagate(node, idx0, idx1);

    if (idx1 < target_idx || target_idx < idx0)
    {
        return 0;
    }

    if (idx0 == target_idx && target_idx == idx1)
    {
        return SEG[node];
    }

    int mid = (idx0 + idx1) >> 1;
    return query(node << 1, idx0, mid, target_idx) + query(node << 1 | 1, mid + 1, idx1, target_idx);
}

int SEG_RVSD[400400];

void update_rvsd(int node, int idx0, int idx1, int target_idx, int k)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (idx0 == target_idx && target_idx == idx1)
    {
        SEG_RVSD[node] += k;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update_rvsd(node << 1, idx0, mid, target_idx, k);
    update_rvsd(node << 1 | 1, mid + 1, idx1, target_idx, k);

    SEG_RVSD[node] = SEG_RVSD[node << 1] + SEG_RVSD[node << 1 | 1];
}

int query_rvsd(int node, int idx0, int idx1, int left, int right)
{
    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return SEG_RVSD[node];
    }

    int mid = (idx0 + idx1) >> 1;
    return query_rvsd(node << 1, idx0, mid, left, right) + query_rvsd(node << 1 | 1, mid + 1, idx1, left, right);
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

            if (RVSD)
            {
                update_rvsd(1, 1, N, S[v], k);
            }
            else
            {
                update(1, 1, N, S[v], E[v], k);
            }
        }
        else if (opt == 2)
        {
            int v;
            std::cin >> v;

            std::cout << query(1, 1, N, S[v]) + query_rvsd(1, 1, N, S[v], E[v]) << '\n';
        }
        else
        {
            RVSD ^= 1;
        }
    }

    return 0;
}