#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
constexpr ull INF = 0x7FFFFFFFFFFFFFFF;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

inline ull min(ull x, ull y)
{
    return x < y ? x : y;
}


struct Edge
{
    int v;
    ull w;
    Edge* next;
};

Edge POOL[100100];
Edge* EDGES[10010];
ull COST[21][10010];
int N;
int K;

struct Element
{
    int v;
    ull cost;
    int k;

    bool operator<=(const Element& other) const
    {
        return cost <= other.cost;
    }
};

struct MinHeap
{
    Element data[500500];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    void push(Element e)
    {
        data[++size] = e;

        int c = size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p] <= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    Element pop()
    {
        Element ret = data[1];
        swap(data[1], data[size--]);

        int p = 1;
        int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && data[c | 1] <= data[c])
            {
                c |= 1;
            }

            if (data[p] <= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            p = c;
            c = p << 1;
        }

        return ret;
    }
} HQ;


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> N >> M >> K;
    for (int i = 0; i < M; ++i)
    {
        int v1, v2;
        ull w;
        std::cin >> v1 >> v2 >> w;

        Edge& e1 = POOL[i << 1];
        Edge& e2 = POOL[i << 1 | 1];

        e1.v = v2;
        e1.w = w;
        e1.next = EDGES[v1];
        EDGES[v1] = &e1;

        e2.v = v1;
        e2.w = w;
        e2.next = EDGES[v2];
        EDGES[v2] = &e2;
    }

    for (int i = 2; i <= N; ++i)
    {
        for (int k = 0; k <= K; ++k)
        {
            COST[k][i] = INF;
        }
    }

    HQ.push({ 1, 0, 0 });
    while (!HQ.empty())
    {
        const Element c = HQ.pop();
        if (COST[c.k][c.v] < c.cost)
        {
            continue;
        }

        for (const Edge* e = EDGES[c.v]; e; e = e->next)
        {
            if (c.cost + e->w < COST[c.k][e->v])
            {
                COST[c.k][e->v] = c.cost + e->w;
                HQ.push({ e->v, COST[c.k][e->v], c.k });
            }

            if (c.k < K && c.cost < COST[c.k + 1][e->v])
            {
                COST[c.k + 1][e->v] = c.cost;
                HQ.push({ e->v, COST[c.k + 1][e->v], c.k + 1 });
            }
        }
    }

    ull cost = INF;
    for (int k = 0; k <= K; ++k)
    {
        cost = min(cost, COST[k][N]);
    }
    std::cout << cost;
   
    return 0;
}