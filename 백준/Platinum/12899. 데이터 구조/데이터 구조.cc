#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MIN = 1;
constexpr int MAX = 2000000;

int SEG[16000800];
int N;

void add(int node, int idx0, int idx1, int target_idx, int k)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (idx0 == target_idx && target_idx == idx1)
    {
        SEG[node] += k;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    add(node << 1, idx0, mid, target_idx, k);
    add(node << 1 | 1, mid + 1, idx1, target_idx, k);
    SEG[node] = SEG[node << 1] + SEG[node << 1 | 1];
}

int query(int k)
{
    int node = 1;
    int left = MIN;
    int right = MAX;

    for (;;)
    {
        if (left > right)
        {
            break;
        }

        int mid = (left + right) >> 1;

        if (k > SEG[node << 1])
        {
            k -= SEG[node << 1];
            node = node << 1 | 1;
            left = mid + 1;
        }
        else
        {
            node = node << 1;
            right = mid;
        }
    }

    while (node)
    {
        --SEG[node];

        node >>= 1;
    }

    return right;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int a, b;
        std::cin >> a >> b;
        if (a == 1)
        {
            add(1, MIN, MAX, b, 1);
        }
        else
        {
            std::cout << query(b) << '\n';
        }
    }

    return 0;
}