#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using uint = unsigned int;

constexpr uint INF = 0xFFFFFFFFu;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

int K;

struct MaxHeap
{
    uint data[110];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }

    uint peek() const
    {
        return data[1];
    }

    void push(int v)
    {
        data[++size] = v;

        int c = size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p] >= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }

        if (size > K)
        {
            pop();
        }
    }

    uint pop()
    {
        uint ret = data[1];

        swap(data[1], data[size--]);

        int p = 1;
        int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && data[c | 1] >= data[c])
            {
                c |= 1;
            }

            if (data[p] >= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            p = c;
            c = p << 1;
        }

        return ret;
    }
};

MaxHeap COST[1010];
int N;

struct Edge
{
    int v;
    uint w;
    Edge* next;
};

Edge POOL[250250];
Edge* EDGES[1010];

struct Element
{
    int v;
    uint cost;

    bool operator<=(const Element& other) const
    {
        return cost <= other.cost;
    }
};

struct MinHeap
{
    Element data[6000600];
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
        int v;
        std::cin >> v;
        Edge& e = POOL[i];
        std::cin >> e.v >> e.w;

        e.next = EDGES[v];
        EDGES[v] = &e;
    }

    COST[1].push(0);
    for (int i = 2; i <= N; ++i)
    {
        COST[i].push(INF);
    }

    HQ.push({ 1, 0 });
    while (!HQ.empty())
    {
        const Element c = HQ.pop();
        if (c.cost > COST[c.v].peek())
        {
            continue;
        }

        for (const Edge* e = EDGES[c.v]; e; e = e->next)
        {
            MaxHeap& h = COST[e->v];
            const uint cost = c.cost + e->w;
            if (cost >= h.peek() && h.getSize() >= K)
            {
                continue;
            }

            h.push(cost);
            HQ.push({ e->v, cost });
        }
    }

    for (int i = 1; i <= N; ++i)
    {
        if (COST[i].getSize() < K || COST[i].peek() == INF)
        {
            std::cout << -1 << '\n';
        }
        else
        {
            std::cout << COST[i].peek() << '\n';
        }
    }

    return 0;
}