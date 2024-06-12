#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull ARR[100100];
ull SUM_SEG[400400];
int MIN_IDX_SEG[400400];
int N;

inline ull min(ull x, ull y)
{
    return x < y ? x : y;
}

inline ull max(ull x, ull y)
{
    return x > y ? x : y;
}

void init(int node, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        SUM_SEG[node] = ARR[idx0];
        MIN_IDX_SEG[node] = idx0;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    init(node << 1, idx0, mid);
    init(node << 1 | 1, mid + 1, idx1);

    SUM_SEG[node] = SUM_SEG[node << 1] + SUM_SEG[node << 1 | 1];
    MIN_IDX_SEG[node] = ARR[MIN_IDX_SEG[node << 1]] < ARR[MIN_IDX_SEG[node << 1 | 1]] ? MIN_IDX_SEG[node << 1] : MIN_IDX_SEG[node << 1 | 1];
}

ull query_sum(int node, int idx0, int idx1, int left, int right)
{
    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return SUM_SEG[node];
    }

    int mid = (idx0 + idx1) >> 1;
    return query_sum(node << 1, idx0, mid, left, right) + query_sum(node << 1 | 1, mid + 1, idx1, left, right);
}

int query_min_idx(int node, int idx0, int idx1, int left, int right)
{
    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return MIN_IDX_SEG[node];
    }

    int mid = (idx0 + idx1) >> 1;
    int l_idx = query_min_idx(node << 1, idx0, mid, left, right);
    int r_idx = query_min_idx(node << 1 | 1, mid + 1, idx1, left, right);

    return ARR[l_idx] < ARR[r_idx] ? l_idx : r_idx;
}

ull sol(int l, int r)
{
    if (l > r)
    {
        return 0;
    }

    int idx = query_min_idx(1, 1, N, l, r);
    ull res = ARR[idx] * query_sum(1, 1, N, l, r);

    res = max(res, sol(l, idx - 1));
    res = max(res, sol(idx + 1, r));

    return res;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i];
    }
    ARR[0] = 0x7FFFFFFFFFFFFFFF;
    init(1, 1, N);
    std::cout << sol(1, N);

    return 0;
}