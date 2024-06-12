#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char BUF[100100];
int ARR[100100];
int ACC[100100];

int SUM_SEG_TREE[400400];
int MIN_SEG_TREE[400400];
int LAZY[400400];
int N;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

void init(int node, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        SUM_SEG_TREE[node] = ARR[idx0];
        MIN_SEG_TREE[node] = ACC[idx0];
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    init(node << 1, idx0, mid);
    init(node << 1 | 1, mid + 1, idx1);
    SUM_SEG_TREE[node] = SUM_SEG_TREE[node << 1] + SUM_SEG_TREE[node << 1 | 1];
    MIN_SEG_TREE[node] = min(MIN_SEG_TREE[node << 1], MIN_SEG_TREE[node << 1 | 1]);
}

void update_sum(int node, int idx0, int idx1, int target_idx, int new_val)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (idx0 == target_idx && target_idx == idx1)
    {
        SUM_SEG_TREE[node] = new_val;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update_sum(node << 1, idx0, mid, target_idx, new_val);
    update_sum(node << 1 | 1, mid + 1, idx1, target_idx, new_val);
    SUM_SEG_TREE[node] = SUM_SEG_TREE[node << 1] + SUM_SEG_TREE[node << 1 | 1];
}

void propagate_min(int node, int idx0, int idx1)
{
    if (LAZY[node])
    {
        MIN_SEG_TREE[node] += LAZY[node];
        if (idx0 != idx1)
        {
            LAZY[node << 1] += LAZY[node];
            LAZY[node << 1 | 1] += LAZY[node];
        }

        LAZY[node] = 0;
    }
}

void update_min(int node, int idx0, int idx1, int left, int right, int diff)
{
    propagate_min(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return;
    }

    if (left <= idx0 && idx1 <= right)
    {
        LAZY[node] = diff;
        propagate_min(node, idx0, idx1);
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update_min(node << 1, idx0, mid, left, right, diff);
    update_min(node << 1 | 1, mid + 1, idx1, left, right, diff);
    MIN_SEG_TREE[node] = min(MIN_SEG_TREE[node << 1], MIN_SEG_TREE[node << 1 | 1]);
}

bool flip(int idx)
{
    ARR[idx] *= -1;

    update_sum(1, 1, N, idx, ARR[idx]);
    update_min(1, 1, N, idx, N, 2 * ARR[idx]);
    
    return SUM_SEG_TREE[1] == 0 && MIN_SEG_TREE[1] >= 0;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> BUF;
    const char* ptr = BUF;
    while (*ptr)
    {
        ++N;

        ARR[N] = *ptr == ')' ? -1 : 1;
        ACC[N] = ACC[N - 1] + ARR[N];

        ++ptr;
    }

    init(1, 1, N);

    int Q;
    std::cin >> Q;

    unsigned int res = 0;
    while (Q--)
    {
        int idx;
        std::cin >> idx;
        res += flip(idx);
    }
    std::cout << res;

    return 0;
}