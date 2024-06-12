#include <iostream>

using ull = unsigned long long;

ull ARR[100100];
int MIN_IDX_SEG[400400];
ull SUM_SEG[400400];
int N;

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

ull MAX;
int L;
int R;

void sol(int l, int r)
{
    if (l > r)
    {
        return;
    }

    int idx = query_min_idx(1, 1, N, l, r);
    ull res = query_sum(1, 1, N, l, r) * ARR[idx];
    if (res > MAX)
    {
        MAX = res;
        L = l;
        R = r;
    }

    sol(l, idx - 1);
    sol(idx + 1, r);
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

    MAX = 0;
    L = 1;
    R = N;
    sol(1, N);

    std::cout << MAX << '\n' << L << ' ' << R;

    return 0;
}
