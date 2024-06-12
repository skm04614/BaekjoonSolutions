#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Element
{
    int n;
    int idx;

    bool operator>=(const Element& other) const
    {
        return n >= other.n;
    }
};

Element ARR[100100];
int N;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

void __heapify(Element* arr, int size)
{
    for (int s = 1; s <= size; s++)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            c = p;
        }
    }
}

void sort(Element* arr, int size)
{
    __heapify(arr, size);

    for (int s = size; s >= 1; s--)
    {
        swap(arr[1], arr[s]);
        const int max_s = s - 1;

        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && arr[c | 1] >= arr[c])
            {
                c |= 1;
            }

            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

int SEG[400400];

void set(int node, int idx0, int idx1, int target_idx)
{
    if (idx1 < target_idx || target_idx < idx0)
    {
        return;
    }

    if (idx0 == target_idx && target_idx == idx1)
    {
        SEG[node] = 1;
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    set(node << 1, idx0, mid, target_idx);
    set(node << 1 | 1, mid + 1, idx1, target_idx);

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

int RECORD[100100];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i].n;
        ARR[i].idx = i;
    }

    sort(ARR, N);

    int sidx = ((N + 1) >> 1);
    int bidx = sidx + 1;
    bool sturn = (N & 1);

    for (int i = 1; i <= N; i++)
    {
        if (sturn)
        {
            int k = ARR[sidx--].idx;
            RECORD[i] = query(1, 1, N, 1, k);
            set(1, 1, N, k);
        }
        else
        {
            int k = ARR[bidx++].idx;
            RECORD[i] = query(1, 1, N, k, N);
            set(1, 1, N, k);
        }

        sturn = !sturn;
    }

    for (int i = N; i >= 1; i--)
    {
        std::cout << RECORD[i] << '\n';
    }

    return 0;
}