#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

int max(int x, int y)
{
    return x > y ? x : y;
}

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
int SOL[100100];
int M;

int CNT[100100];
int CNT_TABLE[100100];

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
    
    std::cin >> M;
    for (int i = 1; i <= M; ++i)
    {
        Query& q = QUERIES[i];
        std::cin >> q.l >> q.r;
        q.nth = i;
        q.k = q.l / K;
    }

    sort(QUERIES, M);

    int max_cnt = 0;
    int l = 1;
    int r = 0;

    for (int i = 1; i <= M; ++i)
    {
        const Query& q = QUERIES[i];

        while (r < q.r)
        {
            int& cnt = CNT[ARR[++r]];

            --CNT_TABLE[cnt];
            ++CNT_TABLE[++cnt];

            max_cnt = max(max_cnt, cnt);
        }

        while (r > q.r)
        {
            int& cnt = CNT[ARR[r--]];

            if (--CNT_TABLE[cnt] == 0 && max_cnt == cnt)
            {
                max_cnt--;
            }
            ++CNT_TABLE[--cnt];
        }

        while (l < q.l)
        {
            int& cnt = CNT[ARR[l++]];

            if (--CNT_TABLE[cnt] == 0 && max_cnt == cnt)
            {
                max_cnt--;
            }
            ++CNT_TABLE[--cnt];
        }

        while (l > q.l)
        {
            int& cnt = CNT[ARR[--l]];

            --CNT_TABLE[cnt];
            ++CNT_TABLE[++cnt];

            max_cnt = max(max_cnt, cnt);
        }

        SOL[q.nth] = max_cnt;
    }

    for (int i = 1; i <= M; ++i)
    {
        std::cout << SOL[i] << '\n';
    }

    return 0;
}