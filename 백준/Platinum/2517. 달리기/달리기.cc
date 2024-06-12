#include <iostream>

int RAW[500500];
int ARR[500500];
int N;

inline void swap(int& n, int& m)
{
    int tmp = n;
    n = m;
    m = tmp;
}

void sort_to(const int* src, int* dest, int size)
{
    for (int s = 1; s <= size; s++)
    {
        dest[s] = src[s];

        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (dest[p] >= dest[c])
            {
                break;
            }

            swap(dest[p], dest[c]);
            c = p;
        }
    }

    for (int s = size; s >= 1; s--)
    {
        swap(dest[1], dest[s]);

        const int max_s = s - 1;
        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && dest[c | 1] >= dest[c])
            {
                c |= 1;
            }

            if (dest[p] >= dest[c])
            {
                break;
            }

            swap(dest[p], dest[c]);

            p = c;
            c = p << 1;
        }
    }
}

int find_idx(const int* arr, int l, int r, int tgt)
{
    for (;;)
    {
        int mid = (l + r) >> 1;

        if (arr[mid] == tgt)
        {
            return mid;
        }

        if (tgt < arr[mid])
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
}


int SEG_TREE[2002000];

void update(int node, int idx0, int idx1, int tgt_idx)
{
    if (idx1 < tgt_idx || tgt_idx < idx0)
    {
        return;
    }

    if (tgt_idx == idx0 && tgt_idx == idx1)
    {
        SEG_TREE[node] = 1;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, tgt_idx);
    update(node << 1 | 1, mid + 1, idx1, tgt_idx);

    SEG_TREE[node] = SEG_TREE[node << 1] + SEG_TREE[node << 1 | 1];
}

int query(int node, int idx0, int idx1, int left, int right)
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
    return query(node << 1, idx0, mid, left, right) + query(node << 1 | 1, mid + 1, idx1, left, right);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> RAW[i];
    }
    
    sort_to(RAW, ARR, N);

    for (int i = 1; i <= N; i++)
    {
        const int val = find_idx(ARR, 1, N, RAW[i]);

        update(1, 1, N, val);
        std::cout << query(1, 1, N, val, N) << '\n';
    }

    return 0;
}
