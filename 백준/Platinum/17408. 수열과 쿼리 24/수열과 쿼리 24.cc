#include <iostream>

int ARR[100100];
int SEG_TREE[400400];
int N;

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

    int idx_l = SEG_TREE[node << 1];
    int idx_r = SEG_TREE[node << 1 | 1];
    SEG_TREE[node] = ARR[idx_l] > ARR[idx_r] ? idx_l : idx_r;
}

void update(int node, int idx0, int idx1, int target_idx, int k)
{
    if (target_idx < idx0 || idx1 < target_idx)
    {
        return;
    }

    if (target_idx == idx0 && idx1 == target_idx)
    {
        ARR[target_idx] = k;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, target_idx, k);
    update(node << 1 | 1, mid + 1, idx1, target_idx, k);

    int idx_l = SEG_TREE[node << 1];
    int idx_r = SEG_TREE[node << 1 | 1];
    SEG_TREE[node] = ARR[idx_l] > ARR[idx_r] ? idx_l : idx_r;
}

int _query(int node, int idx0, int idx1, int left, int right)
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

    int idx_l = _query(node << 1, idx0, mid, left, right);
    int idx_r = _query(node << 1 | 1, mid + 1, idx1, left, right);
    return ARR[idx_l] > ARR[idx_r] ? idx_l : idx_r;
}

int query(int node, int idx0, int idx1, int left, int right)
{
    int idx_max = _query(node, idx0, idx1, left, right);

    int cidx_1 = _query(node, idx0, idx1, left, idx_max - 1);
    int cidx_2 = _query(node, idx0, idx1, idx_max + 1, right);

    return (ARR[cidx_1] > ARR[cidx_2] ? ARR[cidx_1] : ARR[cidx_2]) + ARR[idx_max];
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

    init(1, 1, N);

    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        if (a == 1)
        {
            update(1, 1, N, b, c);
        }
        else
        {
            std::cout << query(1, 1, N, b, c) << '\n';
        }
    }

    return 0;
}