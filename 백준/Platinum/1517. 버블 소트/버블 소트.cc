#include <iostream>

struct Element
{
    int val;
    int idx;

    bool operator>(const Element& other) const
    {
        if (val == other.val)
        {
            return idx > other.idx;
        }

        return val > other.val;
    }
};

Element ARR[500500];
int SEG_TREE[2002000];
int N;

template <typename T>
inline void __swap(T& n, T& m)
{
    T tmp = n;
    n = m;
    m = tmp;
}

void __heapify(Element* arr, int size)
{
    for (register int s = 1; s <= size; s++)
    {
        register int c = s;
        while (c > 1)
        {
            register int p = c >> 1;
            if (arr[p] > arr[c])
            {
                break;
            }

            __swap(arr[p], arr[c]);
            c = p;
        }
    }
}

void heap_sort(Element* arr, int size)
{
    __heapify(arr, size);

    for (register int s = size; s >= 1; s--)
    {
        int max_s = s;
        __swap(arr[1], arr[max_s--]);

        register int p = 1;
        register int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && arr[c | 1] > arr[c])
            {
                c |= 1;
            }

            if (arr[p] > arr[c])
            {
                break;
            }

            __swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

void increment(int node, int idx0, int idx1, int target_idx)
{
    if (target_idx < idx0 || target_idx > idx1)
    {
        return;
    }

    if (target_idx == idx0 && target_idx == idx1)
    {
        ++SEG_TREE[node];
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    increment(node << 1, idx0, mid, target_idx);
    increment(node << 1 | 1, mid + 1, idx1, target_idx);

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
    for (register int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i].val;
        ARR[i].idx = i;
    }

    heap_sort(ARR, N);

    unsigned long long sol = 0;
    for (register int i = 1; i <= N; i++)
    {
        sol += query(1, 1, N, ARR[i].idx, N);
        increment(1, 1, N, ARR[i].idx);
    }
    std::cout << sol;

    return 0;
}