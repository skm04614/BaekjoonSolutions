#include <iostream>

using ull = unsigned long long;

int ARR[100100];
int SEG_TREE[400400];
int N;

inline ull max(ull x, ull y)
{
    return x > y ? x : y;
}

void init(int node, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        SEG_TREE[node] = idx0;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    init(node << 1, idx0, mid);
    init(node << 1 | 1, mid + 1, idx1);

    SEG_TREE[node] = ARR[SEG_TREE[node << 1]] < ARR[SEG_TREE[node << 1 | 1]] ? SEG_TREE[node << 1] : SEG_TREE[node << 1 | 1];
}

int query(int node, int idx0, int idx1, int left, int right)
{
    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return SEG_TREE[node];
    }

    int mid = (idx0 + idx1) >> 1;
    int l_idx = query(node << 1, idx0, mid, left, right);
    int r_idx = query(node << 1 | 1, mid + 1, idx1, left, right);

    return ARR[l_idx] < ARR[r_idx] ? l_idx : r_idx;
}

ull sol(int l, int r)
{
    if (l > r)
    {
        return 0;
    }

    int idx = query(1, 1, N, l, r);
    ull ret = static_cast<ull>(ARR[idx]) * (r - l + 1);

    ret = max(ret, sol(l, idx - 1));
    ret = max(ret, sol(idx + 1, r));
    return ret;
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
    ARR[0] = 0x7FFFFFFF;

    init(1, 1, N);

    std::cout << sol(1, N);

    return 0;
}
