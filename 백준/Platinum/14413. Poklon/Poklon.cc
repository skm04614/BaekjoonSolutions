#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int sqrt(int val)
{
    int ret = 0;
    for (ret = 1; ret * ret < val; ++ret);
    return ret;
}

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void sort(T* arr, int size)
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

int ARR[500500];
int N;
int K;

void compress(int* arr, int size)
{
    int* tmp = new int[size + 10] {};
    for (int i = 1; i <= size; ++i)
    {
        *(tmp + i) = *(arr + i);
    }

    sort(tmp, size);
    
    int* compressed = new int[size + 10] {};
    int n = 0;
    for (int i = 1; i <= size; ++i)
    {
        if (compressed[n] == tmp[i])
        {
            continue;
        }

        compressed[++n] = tmp[i];
    }

    for (int i = 1; i <= size; ++i)
    {
        const int tgt = arr[i];

        int l = 1;
        int r = n;
        for (;;)
        {
            int mid = (l + r) >> 1;
            if (tgt == compressed[mid])
            {
                arr[i] = mid;
                break;
            }

            if (tgt < compressed[mid])
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
    }

    delete[] compressed;
    delete[] tmp;
}

struct Query
{
    int nth;
    int l;
    int r;
    int k;

    bool operator>=(const Query& other) const
    {
        if (k == other.k)
        {
            return r >= other.r;
        }
        return k > other.k;
    }
};

Query QUERIES[500500];
int SOL[500500];
int CNT[500500];
int M;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    K = sqrt(N);

    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
    }

    compress(ARR, N);

    for (int i = 1; i <= M; ++i)
    {
        Query& q = QUERIES[i];
        std::cin >> q.l >> q.r;
        q.k = q.l / K;
        q.nth = i;
    }

    sort(QUERIES, M);

    int l = 1;
    int r = 0;
    int cnt = 0;
    for (int i = 1; i <= M; ++i)
    {
        const Query& q = QUERIES[i];

        while (r < q.r)
        {
            const int c = ++CNT[ARR[++r]];

            if (c == 2)
            {
                ++cnt;
            }
            else if (c == 3)
            {
                --cnt;
            }
        }

        while (r > q.r)
        {
            const int c = --CNT[ARR[r--]];

            if (c == 2)
            {
                ++cnt;
            }
            else if (c == 1)
            {
                --cnt;
            }
        }

        while (l < q.l)
        {
            const int c = --CNT[ARR[l++]];

            if (c == 2)
            {
                ++cnt;
            }
            else if (c == 1)
            {
                --cnt;
            }
        }

        while (l > q.l)
        {
            const int c = ++CNT[ARR[--l]];

            if (c == 2)
            {
                ++cnt;
            }
            else if (c == 3)
            {
                --cnt;
            }
        }

        SOL[q.nth] = cnt;
    }

    for (int i = 1; i <= M; ++i)
    {
        std::cout << SOL[i] << '\n';
    }

    return 0;
}