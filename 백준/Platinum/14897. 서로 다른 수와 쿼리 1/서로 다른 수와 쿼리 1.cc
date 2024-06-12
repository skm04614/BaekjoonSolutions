#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[1000100];
int N;
int K;

int sqrt(int val)
{
    int res = 0;
    for (res = 1; res * res < val; ++res);
    return res;
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

void compress(int* arr, int size)
{
    int* tmp = new int[size + 10];
    for (int s = 1; s <= size; ++s)
    {
        tmp[s] = arr[s];
    }

    sort(tmp, size);

    int* compressed = new int[size + 10] {};
    int c = 0;
    for (int s = 1; s <= size; ++s)
    {
        if (compressed[c] == tmp[s])
        {
            continue;
        }

        compressed[++c] = tmp[s];
    }

    for (int i = 1; i <= size; ++i)
    {
        int l = 1;
        int r = c;
        for (;;)
        {
            int mid = (l + r) >> 1;

            if (ARR[i] == compressed[mid])
            {
                ARR[i] = mid;
                break;
            }

            if (ARR[i] < compressed[mid])
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
    }

    delete[] tmp;
    delete[] compressed;
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

Query QUERIES[1000100];

int CNT[1000100];
int SOL[1000100];
int RES;
int M;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    K = sqrt(N);
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
    }

    compress(ARR, N);
    
    std::cin >> M;
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
    for (int i = 1; i <= M; ++i)
    {
        const Query& q = QUERIES[i];

        while (r < q.r)
        {
            const int val = ARR[++r];

            if (CNT[val] == 0)
            {
                ++RES;
            }

            ++CNT[val];
        }

        while (r > q.r)
        {
            const int val = ARR[r--];

            if (CNT[val] == 1)
            {
                --RES;
            }

            --CNT[val];
        }

        while (l < q.l)
        {
            const int val = ARR[l++];

            if (CNT[val] == 1)
            {
                --RES;
            }

            --CNT[val];
        }

        while (l > q.l)
        {
            const int val = ARR[--l];

            if (CNT[val] == 0)
            {
                ++RES;
            }

            ++CNT[val];
        }

        SOL[q.nth] = RES;
    }

    for (int i = 1; i <= M; ++i)
    {
        std::cout << SOL[i] << '\n';
    }

    return 0;
}