#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Edge
{
    int v;
    int w;
    Edge* next;

    Edge(int v, int w, Edge* next) : v{ v }, w{ w }, next{ next }
    {

    }

    ~Edge()
    {
        delete next;
        next = nullptr;
    }
};

Edge* EDGES[510];
bool MAP[510][510];

int N;
int M;
int S;
int E;

void init()
{
    for (int i = 0; i < N; ++i)
    {
        delete EDGES[i];
        EDGES[i] = nullptr;

        for (int j = 0; j < N; ++j)
        {
            MAP[i][j] = false;
        }
    }
}

struct Element
{
    int v;
    int cost;

    bool operator<=(const Element& other) const
    {
        return cost <= other.cost;
    }
};

struct MinHeap
{
    Element data[250250];
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

struct Record
{
    int v;
    Record* next;

    Record(int v, Record* next) : v{ v }, next{ next }
    {

    }

    ~Record()
    {
        delete next;
        next = nullptr;
    }
};

int COST[510];
Record* REC[510];

void destroy_rec_edge(int node)
{
    for (Record* r = REC[node]; r; r = r->next)
    {
        MAP[r->v][node] = false;
        destroy_rec_edge(r->v);
    }

    delete REC[node];
    REC[node] = nullptr;
}

void dijkstra()
{
    for (int i = 0; i < N; ++i)
    {
        COST[i] = INF;
        delete REC[i];
        REC[i] = nullptr;
    }

    COST[S] = 0;
    HQ.push({ S, COST[S] });
    while (!HQ.empty())
    {
        Element c = HQ.pop();
        if (c.cost > COST[c.v])
        {
            continue;
        }

        for (const Edge* e = EDGES[c.v]; e; e = e->next)
        {
            if (MAP[c.v][e->v] == false)
            {
                continue;
            }

            if (COST[e->v] < COST[c.v] + e->w)
            {
                continue;
            }
            else if (COST[e->v] > COST[c.v] + e->w)
            {
                delete REC[e->v];
                REC[e->v] = nullptr;

                COST[e->v] = COST[c.v] + e->w;
                HQ.push({ e->v, COST[e->v] });
            }

            REC[e->v] = new Record{ c.v, REC[e->v] };
        }
    }

    if (COST[E] == INF)
    {
        return;
    }

    destroy_rec_edge(E);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (;;)
    {
        std::cin >> N >> M;
        if (N == 0 && M == 0)
        {
            break;
        }

        init();

        std::cin >> S >> E;

        while (M--)
        {
            int v0, v1, w;
            std::cin >> v0 >> v1 >> w;

            MAP[v0][v1] = true;

            EDGES[v0] = new Edge{ v1, w, EDGES[v0] };
        }

        dijkstra();

        int min_cost = COST[E];
        if (min_cost == INF)
        {
            std::cout << -1 << '\n';
            continue;
        }

        for (;;)
        {
            dijkstra();

            if (COST[E] != min_cost)
            {
                break;
            }
        }

        std::cout << (COST[E] == INF ? -1 : COST[E]) << '\n';
    }

     return 0;
}