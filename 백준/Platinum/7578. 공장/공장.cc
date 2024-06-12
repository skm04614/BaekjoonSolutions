#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using ull = unsigned long long;

int MAP[1001000];
int SEG[4004000];
int N;

int query(int node, int  idx0, int idx1, int left, int right)
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

void update(int node, int idx0, int idx1, int target_idx)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (target_idx == idx0 && idx1 == target_idx)
    {
        SEG[node] = 1;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, target_idx);
    update(node << 1 | 1, mid + 1, idx1, target_idx);
    SEG[node] = SEG[node << 1] + SEG[node << 1 | 1];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        int val;
        std::cin >> val;
        MAP[val] = i;
    }

    ull res = 0;
    for (int i = 1; i <= N; i++)
    {
        int val;
        std::cin >> val;

        val = MAP[val];

        res += query(1, 1, 1000000, val, 1000000);
        update(1, 1, 1000000, val);
    }
    std::cout << res;

    return 0;
}