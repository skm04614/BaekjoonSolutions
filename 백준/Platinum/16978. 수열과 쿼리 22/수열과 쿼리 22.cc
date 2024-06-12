#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Query
{
    int n;
    int opt;
    int a;
    int b;
    ll result;

    bool operator>=(const Query& other) const
    {
        if (n == other.n)
        {
            return opt >= other.opt;
        }

        return n > other.n;
    }
};

Query QUERIES[100100];
int QIDX[100100];
int Q;

void __heapify(int* idx, int size)
{
    for (register int s = 1; s <= size; s++)
    {
        register int c = s;
        while (c > 1)
        {
            register int p = c >> 1;
            if (QUERIES[QIDX[p]] >= QUERIES[QIDX[c]])
            {
                break;
            }

            swap(QIDX[p], QIDX[c]);
            c = p;
        }
    }
}

void sort(int* idx, int size)
{
    __heapify(idx, size);

    for (register int s = size; s >= 1; s--)
    {
        swap(QIDX[1], QIDX[s]);
        const int max_s = s - 1;

        register int p = 1;
        register int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && QUERIES[QIDX[c | 1]] >= QUERIES[QIDX[c]])
            {
                c |= 1;
            }

            if (QUERIES[QIDX[p]] >= QUERIES[QIDX[c]])
            {
                break;
            }

            swap(QIDX[p], QIDX[c]);
            p = c;
            c = p << 1;
        }
    }
}

ll ARR[100100];
ll SEG_TREE[400400];
int N;

void init(int node, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        SEG_TREE[node] = ARR[idx0];
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

    if (target_idx == idx0 && idx1 == target_idx)
    {
        SEG_TREE[node] = k;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, target_idx, k);
    update(node << 1 | 1, mid + 1, idx1, target_idx, k);

    SEG_TREE[node] = SEG_TREE[node << 1] + SEG_TREE[node << 1 | 1];
}

ll result(int node, int idx0, int idx1, int left, int right)
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
    return result(node << 1, idx0, mid, left, right) + result(node << 1 | 1, mid + 1, idx1, left, right);
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

    std::cin >> Q;
    int n1 = 0;
    for (register int i = 1; i <= Q; i++)
    {
        QIDX[i] = i;

        Query& q = QUERIES[i];
        std::cin >> q.opt;
        if (q.opt == 1)
        {
            q.n = ++n1;
        }
        else
        {
            std::cin >> q.n;
        }
        std::cin >> q.a >> q.b;
    }

    sort(QIDX, Q);

    for (register int i = 1; i <= Q; i++)
    {
        Query& query = QUERIES[QIDX[i]];

        if (query.opt == 1)
        {
            update(1, 1, N, query.a, query.b);
        }
        else
        {
            query.result = result(1, 1, N, query.a, query.b);
        }
    }

    for (register int i = 1; i <= Q; i++)
    {
        const Query& query = QUERIES[i];

        if (query.opt == 2)
        {
            std::cout << query.result << '\n';
        }

    }

    return 0;
}