#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Query
{
    int nth;
    int lp;
    int l;
    int r;

    bool operator>=(const Query& other) const
    {
        if (lp == other.lp)
        {
            return r >= other.r;
        }

        return lp > other.lp;
    }
};

int sqrt(int val)
{
    int k;
    for (k = 1; k * k < val; k++);
    return k;
}

int ARR[300300];
int N;
int K;

int COLORS[10010];
int C;

Query QUERIES[10010];
int SOL[10010];
int M;

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

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> C;
    K = sqrt(N);

    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i];
    }

    std::cin >> M;
    for (int i = 1; i <= M; i++)
    {
        Query& q = QUERIES[i];
        std::cin >> q.l >> q.r;
        
        q.nth = i;
        q.lp = q.l / K;
    }

    sort(QUERIES, M);
    
    int l = 1;
    int r = 0;
    for (int i = 1; i <= M; i++)
    {
        const Query& q = QUERIES[i];

        while (r < q.r) ++COLORS[ARR[++r]];
        while (r > q.r) --COLORS[ARR[r--]];
        while (l < q.l) --COLORS[ARR[l++]];
        while (l > q.l) ++COLORS[ARR[--l]];

        for (int c = 1; c <= C; ++c)
        {
            if (COLORS[c] > ((r - l + 1) / 2))
            {
                SOL[q.nth] = c;
                break;
            }
        }
    }

    for (int i = 1; i <= M; i++)
    {
        if (SOL[i] > 0)
        {
            std::cout << "yes " << SOL[i];
        }
        else
        {
            std::cout << "no";
        }
        std::cout << '\n';
    }

    return 0;
}