#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Line
{
    int a;
    int b;

    bool operator>=(const Line& other) const
    {
        if (a == other.a)
        {
            return b >= other.b;
        }

        return a > other.a;
    }
};

Line ARR[4000400];
int M;

void sort(Line* arr, int size)
{
    for (int s = 1; s <= size; ++s)
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

    for (int s = size; s >= 1; --s)
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

struct Seg
{
    int tree[8080];
    int bias;

    Seg() : tree{}, bias{}
    {

    }

    void init(int N)
    {
        for (bias = 1; bias < N; bias <<= 1);
        --bias;
    }

    void update(int idx)
    {
        idx += bias;
        ++tree[idx];

        while (idx >>= 1)
        {
            ++tree[idx];
        }
    }

    int query(int l, int r)
    {
        l += bias;
        r += bias;

        int res = 0;
        while (l < r)
        {
            if (l & 1)
            {
                res += tree[l++];
            }

            if (~r & 1)
            {
                res += tree[r--];
            }

            l >>= 1;
            r >>= 1;
        }

        if (l == r)
        {
            res += tree[r];
        }

        return res;
    }
} SEG;

int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 1; i <= M; ++i)
    {
        std::cin >> ARR[i].a >> ARR[i].b;
    }
    sort(ARR, M);

    SEG.init(N);
    unsigned long long sol = 0;
    for (int i = 1; i <= M; ++i)
    {
        const int x = ARR[i].b;
        SEG.update(x);
        sol += SEG.query(x + 1, N);
    }
    std::cout << sol;

    return 0;
}