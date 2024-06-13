#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int SEG[800800];
int REC[100100];
int N;
int M;
int R;

void init(int node, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        SEG[node] = idx0 <= N;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    init(node << 1, idx0, mid);
    init(node << 1 | 1, mid + 1, idx1);

    SEG[node] = SEG[node << 1] + SEG[node << 1 | 1];
}

void update(int node, int idx0, int idx1, int target_idx, int val)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (idx0 == target_idx && idx1 == target_idx)
    {
        SEG[node] = val;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, target_idx, val);
    update(node << 1 | 1, mid + 1, idx1, target_idx, val);

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

void sol()
{
    std::cin >> N >> M;

    int K = N + M;

    init(1, 1, K);

    for (int i = 1; i <= N; i++)
    {
        REC[i] = N - (i - 1);
    }
    R = N;

    for (int i = 1; i <= M; i++)
    {
        int n;
        std::cin >> n;

        std::cout << query(1, 1, K, REC[n] + 1, K) << ' ';
        update(1, 1, K, REC[n], 0);
        REC[n] = ++R;
        update(1, 1, K, REC[n], 1);
    }
    std::cout << '\n';
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {
        sol();
    }

    return 0;
}