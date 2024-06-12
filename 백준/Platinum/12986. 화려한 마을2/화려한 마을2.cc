#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int BIAS = 100001;

inline int max(int x, int y)
{
    return x > y ? x : y;
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

inline int sqrt(int val)
{
    int ret = 0;
    for (ret = 1; ret * ret < val; ++ret);
    return ret;
}

int ARR[100100];
int N;
int K;

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
Query QUERIES[100100];
int RES[100100];
int Q;

int CNT[200200];
int SIZE_CNT[200200];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> Q;
    K = sqrt(N);
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
        ARR[i] += BIAS;
    }

    for (int i = 1; i <= Q; ++i)
    {
        Query& q = QUERIES[i];

        q.nth = i;
        std::cin >> q.l >> q.r;
        q.k = q.l / K;
    }

    sort(QUERIES, Q);

    int res = 0;
    int l = 1;
    int r = 0;
    for (int i = 1; i <= Q; ++i)
    {
        const Query& q = QUERIES[i];

        while (r < q.r)
        {
            int cnt = ++CNT[ARR[++r]];
            res = max(res, cnt);

            --SIZE_CNT[cnt - 1];
            ++SIZE_CNT[cnt];
        }

        while (l > q.l)
        {
            int cnt = ++CNT[ARR[--l]];
            res = max(res, cnt);

            --SIZE_CNT[cnt - 1];
            ++SIZE_CNT[cnt];
        }

        while (r > q.r)
        {
            int cnt = --CNT[ARR[r--]];

            if (--SIZE_CNT[cnt + 1] == 0 && cnt + 1 == res)
            {
                --res;
            }
            ++SIZE_CNT[cnt];
        }

        while (l < q.l)
        {
            int cnt = --CNT[ARR[l++]];

            if (--SIZE_CNT[cnt + 1] == 0 && cnt + 1 == res)
            {
                --res;
            }
            ++SIZE_CNT[cnt];
        }

        RES[q.nth] = res;
    }

    for (int i = 1; i <= Q; ++i)
    {
        std::cout << RES[i] << '\n';
    }

    return 0;
}