#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int ARR[500500];
int SEG_TREE_K[2002000];
int SEG_TREE_D[2002000];
int N;
int K;
int D;

void update(int* seg_tree, int node, int idx0, int idx1, int target_idx, int val)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (target_idx == idx0 && idx1 == target_idx)
    {
        seg_tree[node] = val;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(seg_tree, node << 1, idx0, mid, target_idx, val);
    update(seg_tree, node << 1 | 1, mid + 1, idx1, target_idx, val);

    seg_tree[node] = max(seg_tree[node << 1], seg_tree[node << 1 | 1]);
}

int query(int* seg_tree, int node, int idx0, int idx1, int left, int right)
{
    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return seg_tree[node];
    }

    int mid = (idx0 + idx1) >> 1;
    return max(query(seg_tree, node << 1, idx0, mid, left, right), query(seg_tree, node << 1 | 1, mid + 1, idx1, left, right));
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> K >> D;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i];
    }

    for (int i = 1; i <= N; i++)
    {
        int t = ARR[i] % K;
        int c1 = query(SEG_TREE_K, 1, 0, K, t, t);

        int l = ARR[i] - D;
        if (l <= 0)
        {
            l = 1;
        }
        int r = ARR[i] + D;
        if (r > 500000)
        {
            r = 500000;
        }
        int c2 = query(SEG_TREE_D, 1, 1, 500000, l, r);

        int c = max(c1, c2) + 1;

        update(SEG_TREE_K, 1, 0, K, t, c);
        update(SEG_TREE_D, 1, 1, 500000, ARR[i], c);
    }
    std::cout << query(SEG_TREE_D, 1, 1, N, 1, N);

    return 0;
}
