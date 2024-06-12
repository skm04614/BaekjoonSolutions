#include <iostream>

constexpr int INF = 0x7FFFFFFF;

enum
{
    START,
    V1,
    V2
};

struct Edge
{
    int dest;
    int w;
    Edge* next;

    Edge(int dest, int w, Edge* next) : dest{ dest }, w{ w }, next{ next }
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

Edge* EDGES[810];

int N, M;

int COST[3][810];
int V[4];

inline int min(int x, int y)
{
    return x < y ? x : y;
}

template <typename T>
void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

void cleanup(void)
{
    for (register int i = 0; i < 810; i++)
    {
        if (EDGES[i])
        {
            delete EDGES[i];
            EDGES[i] = nullptr;
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
    Element data[8000];
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
            if (c + 1 <= size && data[c + 1] <= data[c])
            {
                ++c;
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

    void reset()
    {
        size = 0;
    }
} HQ;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (register int i = 1; i <= N; i++)
    {
        COST[START][i] = COST[V1][i] = COST[V2][i] = INF;
    }

    for (register int i = 1; i <= M; i++)
    {
        int src, dest, w;
        std::cin >> src >> dest >> w;

        EDGES[src] = new Edge{ dest, w, EDGES[src] };
        EDGES[dest] = new Edge{ src, w, EDGES[dest] };
    }
    
    V[START] = 1;
    std::cin >> V[V1] >> V[V2];

    for (int n = 0; n < 3; n++)
    {
        int* cost = COST[n];

        cost[V[n]] = 0;
        HQ.push({ V[n], cost[V[n]] });

        while (!HQ.empty())
        {
            const Element current = HQ.pop();

            if (current.cost > cost[current.v])
            {
                continue;
            }

            for (Edge* edge = EDGES[current.v]; edge; edge = edge->next)
            {
                if (current.cost + edge->w >= cost[edge->dest])
                {
                    continue;
                }

                cost[edge->dest] = current.cost + edge->w;
                HQ.push({ edge->dest, cost[edge->dest] });
            }
        }

        HQ.reset();
    }

    int sol = INF;
    if (COST[START][V[V1]] < INF && COST[V1][V[V2]] < INF && COST[V2][N] < INF)
    {
        sol = min(sol, COST[START][V[V1]] + COST[V1][V[V2]] + COST[V2][N]);
    }

    if (COST[START][V[V2]] < INF && COST[V2][V[V1]] < INF && COST[V1][N] < INF)
    {
        sol = min(sol, COST[START][V[V2]] + COST[V2][V[V1]] + COST[V1][N]);
    }
    std::cout << (sol == INF ? -1 : sol);

    cleanup();

    return 0;
}