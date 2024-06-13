#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

ll ARR[200200];
ll SEG_TREE[800800];
int N;
int Q;
int S;
int T;

void init(int node, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        SEG_TREE[node] = ((ARR[idx0] <= 0) ? -T : -S) * ARR[idx0];
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    init(node << 1, idx0, mid);
    init(node << 1 | 1, mid + 1, idx1);
    SEG_TREE[node] = SEG_TREE[node << 1] + SEG_TREE[node << 1 | 1];
}

void update(int node, int idx0, int idx1, int target_idx, int k)
{
    if (target_idx < idx0 || idx1 < target_idx)
    {
        return;
    }

    if (idx0 == target_idx && target_idx == idx1)
    {
        ARR[target_idx] += k;
        SEG_TREE[node] = ((ARR[target_idx] <= 0) ? -T : -S) * ARR[target_idx];
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, target_idx, k);
    update(node << 1 | 1, mid + 1, idx1, target_idx, k);
    SEG_TREE[node] = SEG_TREE[node << 1] + SEG_TREE[node << 1 | 1];
}

ll query()
{
    return SEG_TREE[1];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> Q >> S >> T;
    for (register int i = 0; i <= N; i++)
    {
        std::cin >> ARR[i];
    }

    for (register int i = N; i > 0; i--)
    {
        ARR[i] -= ARR[i - 1];
    }

    init(1, 1, N);

    while (Q--)
    {
        int left, right, k;
        std::cin >> left >> right >> k;

        update(1, 1, N, left, k);
        update(1, 1, N, right + 1, -k);
        std::cout << query() << '\n';
    }

    return 0;
}