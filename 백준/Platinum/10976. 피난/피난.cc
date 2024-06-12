#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int SIZE = 210;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

inline int min(int x, int y)
{
    return x < y ? x : y;
}

struct Adj
{
    int v;
    Adj* next;
};

Adj POOL[SIZE * SIZE];
Adj* ADJ[SIZE];
int C[SIZE][SIZE];
int F[SIZE][SIZE];

void reset()
{
    for (int i = 0; i < SIZE; ++i)
    {
        ADJ[i] = nullptr;
        for (int j = 0; j < SIZE; ++j)
        {
            C[i][j] = F[i][j] = 0;
        }
    }
}

int ORIGIN[SIZE];
int Q[SIZE];
int LP, RP;

void clear()
{
    LP = RP = -1;
    for (int i = 0; i < SIZE; i++)
    {
        ORIGIN[i] = 0;
    }
}

int edmonds_karp(int src, int sink)
{
    int max_flow = 0;
    for (;;)
    {
        clear();

        ORIGIN[src] = -1;
        Q[++RP] = src;
        while (RP > LP)
        {
            const int c = Q[++LP];
            for (const Adj* adj = ADJ[c]; adj; adj = adj->next)
            {
                const int n = adj->v;
                if (C[c][n] - F[c][n] > 0 && !ORIGIN[n])
                {
                    ORIGIN[n] = c;
                    Q[++RP] = n;
                    if (n == sink)
                    {
                        LP = RP;
                        break;
                    }
                }
            }
        }

        if (!ORIGIN[sink])
        {
            break;
        }

        int f = 0x7FFFFFFF;
        for (int v = sink; v != src; v = ORIGIN[v])
        {
            f = min(f, C[ORIGIN[v]][v] - F[ORIGIN[v]][v]);
        }

        max_flow += f;

        for (int v = sink; v != src; v = ORIGIN[v])
        {
            F[ORIGIN[v]][v] += f;
            F[v][ORIGIN[v]] -= f;
        }
    }

    return max_flow;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {
        reset();

        int n, m;
        std::cin >> n >> m;
        for (int i = 0; i < m; ++i)
        {
            int v0, v1;
            std::cin >> v0 >> v1;
            if (v1 < v0)
            {
                swap(v0, v1);
            }

            ++C[v0][v1];
        }

        int a = 0;
        for (int i = 1; i < SIZE; ++i)
        {
            for (int j = 1; j < i; ++j)
            {
                if (C[i][j] || C[j][i])
                {
                    Adj& adj1 = POOL[a++];
                    
                    adj1.v = j;
                    adj1.next = ADJ[i];
                    ADJ[i] = &adj1;

                    Adj& adj2 = POOL[a++];

                    adj2.v = i;
                    adj2.next = ADJ[j];
                    ADJ[j] = &adj2;
                }
            }
        }

        std::cout << edmonds_karp(1, n) << '\n';
    }

    return 0;
}
