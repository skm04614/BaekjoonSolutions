#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

struct Element
{
    int x;
    int t;

    Element move(int opt) const
    {
        if (opt == 0)
        {
            return { x - 1, t + 1 };
        }

        if (opt == 1)
        {
            return { x + 1, t + 1 };
        }

        return { x << 1, t + 1 };
    }

    bool is_out_of_bounds() const
    {
        return x < 0 || x > 500000;
    }
};

int N;
int K[1010];
int C;

int VISITED[2][500500];
Element Q[1100000];
int LP, RP;

int _bsearch(int* arr, int left, int right, int tgt)
{
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        if (arr[mid] == tgt)
        {
            return mid;
        }

        if (tgt > arr[mid])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> K[0];
    for (int i = 1; ; ++i, ++C)
    {
        K[i] = i + K[i - 1];
        if (K[i] > 500000)
        {
            break;
        }
    }

    Q[++RP] = { N, 1 };
    VISITED[0][N] = 1;
    while (RP > LP)
    {
        const Element c = Q[++LP];

        for (int i = 0; i < 3; ++i)
        {
            const Element n = c.move(i);

            if (n.is_out_of_bounds() || VISITED[n.t & 1][n.x])
            {
                continue;
            }

            Q[++RP] = n;
            VISITED[n.t & 1][n.x] = n.t;
        }
    }

    int sol = 0x7FFFFFFF;
    for (int i = 0; i < 2; ++i)
    {
        for (int x = 0; x <= 500000; ++x)
        {
            if (VISITED[i][x] == 0)
            {
                continue;
            }

            --VISITED[i][x];

            int t_k = _bsearch(K, 0, C, x);
            if (t_k == -1 || t_k < VISITED[i][x])
            {
                continue;
            }

            if ((t_k - VISITED[i][x]) % 2 == 0)
            {
                sol = min(sol, t_k);
            }
        }
    }
    std::cout << (sol == 0x7FFFFFFF ? -1 : sol);

    return 0;
}
