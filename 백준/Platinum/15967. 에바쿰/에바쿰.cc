#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using ll = long long;
ll ARR[1001000];
ll SEG_TREE[4004000];
ll LAZY[4004000];
int N;
int Q0, Q1;

void init(int node, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        SEG_TREE[node] = ARR[idx0];
        return;
    }

    int mid = (idx0 + idx1) / 2;
    init(2 * node, idx0, mid);
    init(2 * node + 1, mid + 1, idx1);

    SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

void propagate(int node, int idx0, int idx1)
{
    if (LAZY[node])
    {
        SEG_TREE[node] += ((idx1 - idx0 + 1) * LAZY[node]);
        if (idx0 != idx1)
        {
            LAZY[2 * node] += LAZY[node];
            LAZY[2 * node + 1] += LAZY[node];
        }
        LAZY[node] = 0;
    }
}

void update(int node, int idx0, int idx1, int left, int right, ll diff)
{
    propagate(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return;
    }

    if (left <= idx0 && idx1 <= right)
    {
        SEG_TREE[node] += ((idx1 - idx0 + 1) * diff);
        if (idx0 != idx1)
        {
            LAZY[2 * node] += diff;
            LAZY[2 * node + 1] += diff;
        }
        propagate(node, idx0, idx1);
        return;
    }

    int mid = (idx0 + idx1) / 2;
    update(2 * node, idx0, mid, left, right, diff);
    update(2 * node + 1, mid + 1, idx1, left, right, diff);
    SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

ll query(int node, int idx0, int idx1, int left, int right)
{
    propagate(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return SEG_TREE[node];
    }

    int mid = (idx0 + idx1) / 2;
    return query(2 * node, idx0, mid, left, right) +  query(2 * node + 1, mid + 1, idx1, left, right);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> Q0 >> Q1;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i];
    }
    init(1, 1, N);

    for (int i = 1; i <= (Q0 + Q1); i++)
    {
        int a, b, c;
        if (b > c)
        {
            int tmp = b;
            b = c;
            c = tmp;
        }

        std::cin >> a >> b >> c;
        if (a == 1)
        {
            std::cout << query(1, 1, N, b, c) << '\n';
        }
        else
        {
            ll d;
            std::cin >> d;
            update(1, 1, N, b, c, d);
        }
    }

    return 0;
}