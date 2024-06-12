#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull INF = 0x7FFFFFFFFFFFFFFF;

struct Edge
{
    int dest;
    int w;
    Edge* next;

    Edge(int dest, int w, Edge* next) : dest{ dest }, w{ w }, next { next }
    {

    }

    ~Edge()
    {
        if (next)
        {
            delete next;
            next = nullptr;
        }
    }
};

Edge* EDGES[100100];

struct Element
{
    int v;
    ull cost;

    bool operator<=(const Element& other) const
    {
        return cost <= other.cost;
    }
};

inline void swap(Element& e1, Element& e2)
{
    Element tmp = e1;
    e1 = e2;
    e2 = tmp;
}

struct MinHeap
{
    Element data[1000100];
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
            if (data[c >> 1] <= data[c])
            {
                break;
            }

            swap(data[c], data[c >> 1]);
            c >>= 1;
        }
    }

    Element pop()
    {
        Element ret = data[1];
        data[1] = data[size--];

        int p = 1;
        while (p << 1 <= size)
        {
            int c = p << 1;
            if ((c | 1) <= size && data[c] <= data[c | 1])
            {
                c |= 1;
            }

            if (data[p] <= data[c])
            {
                break;
            }

            swap(data[c], data[p]);
            p = c;
        }

        return ret;
    }
} HQ;

ull COST[100100];
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (register int i = 1; i <= N; i++)
    {
        COST[i] = INF;
    }

    int M;
    std::cin >> M;
    for (register int i = 1; i <= M; i++)
    {
        int src, dest, w;
        std::cin >> src >> dest >> w;
        EDGES[src] = new Edge{ dest, w, EDGES[src] };
    }

    int src, dest;
    std::cin >> src >> dest;

    COST[src] = 0;
    HQ.push({ src, COST[src] });

    while (!HQ.empty())
    {
        const Element current = HQ.pop();
        if (current.cost > COST[current.v])
        {
            continue;
        }

        for (Edge* e = EDGES[current.v]; e; e = e->next)
        {
            if (COST[e->dest] <= COST[current.v] + e->w)
            {
                continue;
            }

            COST[e->dest] = COST[current.v] + e->w;
            HQ.push({ e->dest, COST[e->dest] });
        }
    }

    std::cout << COST[dest];

    for (register int i = 1; i <= N; i++)
    {
        if (EDGES[i])
        {
            delete EDGES[i];
            EDGES[i] = nullptr;
        }
    }

    return 0;
}