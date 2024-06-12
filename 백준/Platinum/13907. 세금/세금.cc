#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull INF = 0x7FFFFFFFFFFFFFFF;

struct Edge
{
    int v;
    int w;
    Edge* next;
};

ull COST[1010][1010];
int N;

Edge POOL[60060];
Edge* EDGES[30030];
int M;

int K;

int S;
int D;

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

struct Element
{
    int v;
    int step;
    ull w;

    bool operator<=(const Element& other) const
    {
        return w <= other.w;
    }
};

struct MinHeap
{
    Element data[1001000];
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

    std::cin >> N >> M >> K >> S >> D;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            COST[i][j] = i == S ? 0 : INF;
        }
    }

    for (int i = 0; i < M; i++)
    {
        int v1, v2, w;
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

    HQ.push({ S, 0, 0 });

    while (!HQ.empty())
    {
        const Element current = HQ.pop();

        if (current.w > COST[current.v][current.step])
        {
            continue;
        }

        if (current.step == N - 1)
        {
            continue;
        }

        for (const Edge* e = EDGES[current.v]; e; e = e->next)
        {
            if (current.w + e->w >= COST[e->v][current.step + 1])
            {
                continue;
            }

            COST[e->v][current.step + 1] = current.w + e->w;
            HQ.push({ e->v, current.step + 1, current.w + e->w });
        }
    }

    ull sol = INF;

    for (int i = 1; i <= N; i++)
    {
        sol = min(sol, COST[D][i]);
    }
    std::cout << sol << '\n';

    while (K--)
    {
        sol = INF;
        int k;
        std::cin >> k;
        for (int i = 1; i <= N; i++)
        {
            COST[D][i] += (k * i);

            sol = min(sol, COST[D][i]);
        }
        std::cout << sol << '\n';
    }

    return 0;
}