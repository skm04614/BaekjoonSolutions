#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(const int& x, const int& y)
{
    return x < y ? x : y;
}

inline int max(const int& x, const int& y)
{
    return x > y ? x : y;
}

inline void swap(int& n, int& m)
{
    int tmp = n;
    n = m;
    m = tmp;
}

struct Edge
{
    int dest;
    Edge* next;
};

Edge POOL[100100];
int K;

Edge* EDGES[1010];
int TIME[1010];
int RECORD[1010];
int IN_DEGREE[1010];
int N;

struct MinHeap
{
    int idx[1010];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    void reset()
    {
        size = 0;
    }

    void push(int v)
    {
        idx[++size] = v;

        register int c = size;
        while (c > 1)
        {
            register int p = c >> 1;
            if (IN_DEGREE[idx[p]] <= IN_DEGREE[idx[c]])
            {
                break;
            }

            swap(idx[p], idx[c]);
            c = p;
        }
    }

    int pop()
    {
        int ret = idx[1];
        swap(idx[1], idx[size--]);

        register int p = 1;
        register int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && IN_DEGREE[idx[c | 1]] <= IN_DEGREE[idx[c]])
            {
                c |= 1;
            }

            if (IN_DEGREE[idx[p]] <= IN_DEGREE[idx[c]])
            {
                break;
            }

            swap(idx[p], idx[c]);
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

    int T;
    std::cin >> T;
    while (T--)
    {
        HQ.reset();

        std::cin >> N >> K;

        for (register int v = 1; v <= N; v++)
        {
            EDGES[v] = nullptr;
            std::cin >> TIME[v];
            RECORD[v] = 0;
        }

        for (register int i = 1; i <= K; i++)
        {
            Edge& edge = POOL[i];

            int src;
            std::cin >> src >> edge.dest;
            ++IN_DEGREE[edge.dest];
            edge.next = EDGES[src];
            EDGES[src] = &edge;
        }

        int target;
        std::cin >> target;

        for (register int v = 1; v <= N; v++)
        {
            if (IN_DEGREE[v] == 0)
            {
                HQ.push(v);
                RECORD[v] = TIME[v];
            }
        }

        while (!HQ.empty())
        {
            const int v0 = HQ.pop();

            for (Edge* edge = EDGES[v0]; edge; edge = edge->next)
            {
                const int v1 = edge->dest;

                RECORD[v1] = max(RECORD[v1], RECORD[v0] + TIME[v1]);

                if (--IN_DEGREE[v1] == 0)
                {
                    HQ.push(v1);
                }
            }
        }

        std::cout << RECORD[target] << '\n';
    }

    return 0;
}