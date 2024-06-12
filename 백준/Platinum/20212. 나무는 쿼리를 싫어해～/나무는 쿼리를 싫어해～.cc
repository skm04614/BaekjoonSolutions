#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

using ll = long long;

struct Query
{
    int n;
    int opt;
    int idx0;
    int idx1;
    ll k;
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

Query QUERIES[50050];
int QIDX[50050];
int Q;

void sort_qidx(void)
{
    for (register int s = 1; s <= Q; s++)
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

    for (register int s = Q; s >= 1; s--)
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

int COORDS[200200];
int PREFIX[200200];
int PREFIX_TREE[800800];
int C;

void init_prefix_tree(int node, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        PREFIX_TREE[node] = PREFIX[idx0];
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    init_prefix_tree(node << 1, idx0, mid);
    init_prefix_tree(node << 1 | 1, mid + 1, idx1);
    
    PREFIX_TREE[node] = PREFIX_TREE[node << 1] + PREFIX_TREE[node << 1 | 1];
}

void sort_and_unique_coords(void)
{
    for (register int s = 1; s <= C; s++)
    {
        register int c = s;
        while (c > 1)
        {
            register int p = c >> 1;
            if (COORDS[p] >= COORDS[c])
            {
                break;
            }

            swap(COORDS[p], COORDS[c]);
            c = p;
        }
    }

    for (register int s = C; s >= 1; s--)
    {
        swap(COORDS[1], COORDS[s]);

        const int max_s = s - 1;

        register int p = 1;
        register int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && COORDS[c | 1] >= COORDS[c])
            {
                c |= 1;
            }

            if (COORDS[p] >= COORDS[c])
            {
                break;
            }

            swap(COORDS[p], COORDS[c]);
            p = c;
            c = p << 1;
        }
    }

    int* result = new int[200200] {};
    int c = 0;
    for (register int i = 1; i <= C; i++)
    {
        if (COORDS[i] == result[c])
        {
            continue;
        }

        result[++c] = COORDS[i];
    }

    for (register int i = 1; i <= c; i++)
    {
        COORDS[i] = result[i];
        PREFIX[i] = COORDS[i] - COORDS[i - 1];
    }
    for (register int i = c + 1; i <= C; i++)
    {
        COORDS[i] = 0;
        PREFIX[i] = 0;
    }
    C = c;

    init_prefix_tree(1, 1, C);

    delete[] result;
}

int coords_to_cidx(int coords)
{
    register int left = 1;
    register int right = C;
    for (;;)
    {
        register int mid = (left + right) >> 1;
        if (coords == COORDS[mid])
        {
            return mid;
        }
        
        if (coords < COORDS[mid])
        {
            right = mid - 1;
        }

        if (coords > COORDS[mid])
        {
            left = mid + 1;
        }
    }
}

ll SEG_TREE[800800];
ll LAZY[800800];

void propagate(int node, int idx0, int idx1)
{
    if (LAZY[node])
    {
        SEG_TREE[node] += LAZY[node] * PREFIX_TREE[node];
        if (idx0 != idx1)
        {
            LAZY[node << 1] += LAZY[node];
            LAZY[node << 1 | 1] += LAZY[node];
        }
        LAZY[node] = 0;
    }
}

void update(int node, int idx0, int idx1, int left, int right, ll k)
{
    propagate(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return;
    }

    if (left <= idx0 && idx1 <= right)
    {
        LAZY[node] += k;
        propagate(node, idx0, idx1);
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, left, right, k);
    update(node << 1 | 1, mid + 1, idx1, left, right, k);

    SEG_TREE[node] = SEG_TREE[node << 1] + SEG_TREE[node << 1 | 1];
}

ll result(int node, int idx0, int idx1, int left, int right)
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

    int mid = (idx0 + idx1) >> 1;
    return result(node << 1, idx0, mid, left, right) + result(node << 1 | 1, mid + 1, idx1, left, right);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n_1 = 0;
    std::cin >> Q;
    for (register int i = 1; i <= Q; i++)
    {
        QIDX[i] = i;
        Query& query = QUERIES[i];
        
        std::cin >> query.opt >> query.idx0 >> query.idx1;
        COORDS[++C] = query.idx0;
        COORDS[++C] = query.idx0 - 1;
        COORDS[++C] = query.idx1;
        COORDS[++C] = query.idx1 + 1;
        if (query.opt == 1)
        {
            query.n = ++n_1;
            std::cin >> query.k;
        }
        else
        {
            std::cin >> query.n;
        }
    }

    sort_qidx();
    sort_and_unique_coords();

    for (register int i = 1; i <= Q; i++)
    {
        Query& query = QUERIES[QIDX[i]];

        if (query.opt == 1)
        {
            update(1, 1, C, coords_to_cidx(query.idx0), coords_to_cidx(query.idx1), query.k);
        }
        else
        {
            query.result = result(1, 1, C, coords_to_cidx(query.idx0), coords_to_cidx(query.idx1));
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