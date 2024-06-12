#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using uint = unsigned int;

struct Block
{
    uint c0;
    uint c1;
};
Block BLOCKS[100100];
int N;

uint COORDS[400400];
int C;

inline uint max(uint x, uint y)
{
    return x > y ? x : y;
}

template <typename T>
inline void __swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

void sort_unique_coords()
{
    for (int s = 1; s <= C; s++)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (COORDS[p] >= COORDS[c])
            {
                break;
            }

            __swap(COORDS[p], COORDS[c]);
            c = p;
        }
    }

    for (int s = C; s >= 1; s--)
    {
        __swap(COORDS[1], COORDS[s]);
        const int max_s = s - 1;

        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && COORDS[c | 1] >= COORDS[c])
            {
                c |= 1;
            }

            if (COORDS[p] >= COORDS[c])
            {
                break;
            }

            __swap(COORDS[p], COORDS[c]);
            p = c;
            c = p << 1;
        }
    }

    uint* tmp = new uint[sizeof(COORDS) / sizeof(COORDS[0])]{};
    int idx = 0;
    tmp[++idx] = COORDS[1];
    for (int i = 2; i <= C; i++)
    {
        if (tmp[idx] == COORDS[i])
        {
            continue;
        }

        tmp[++idx] = COORDS[i];
    }

    for (int i = 0; i < sizeof(COORDS) / sizeof(COORDS[0]); i++)
    {
        COORDS[i] = tmp[i];
    }
    C = idx;

    delete[] tmp;
}

int get_coords_idx(uint coords)
{
    int lower = 1;
    int upper = C;
    for (;;)
    {
        int mid = (lower + upper) >> 1;
        if (coords == COORDS[mid])
        {
            return mid;
        }

        if (coords < COORDS[mid])
        {
            upper = mid - 1;
        }
        else
        {
            lower = mid + 1;
        }
    }
}

uint SEG_TREE[1600200];
uint LAZY[1600200];

void propagate(int node, int idx0, int idx1)
{
    if (LAZY[node])
    {
        SEG_TREE[node] = max(LAZY[node], SEG_TREE[node]);
        if (idx0 != idx1)
        {
            LAZY[node << 1] = max(LAZY[node], LAZY[node << 1]);
            LAZY[node << 1 | 1] = max(LAZY[node], LAZY[node << 1 | 1]);
        }
        LAZY[node] = 0;
    }
}

void update(int node, int idx0, int idx1, int left, int right, uint val)
{
    propagate(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return;
    }

    if (left <= idx0 && idx1 <= right)
    {
        LAZY[node] = val;
        propagate(node, idx0, idx1);
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    update(node << 1, idx0, mid, left, right, val);
    update(node << 1 | 1, mid + 1, idx1, left, right, val);
    SEG_TREE[node] = max(SEG_TREE[node << 1], SEG_TREE[node << 1 | 1]);
}

uint query(int node, int idx0, int idx1, int left, int right)
{
    propagate(node, idx0, idx1);

    if (idx1 < left || right < idx0)
    {
        return 0;
    }

    if (left <= idx0 && idx1 <= right)
    {
        return SEG_TREE[node];
    }

    int mid = (idx0 + idx1) >> 1;
    return max(query(node << 1, idx0, mid, left, right), query(node << 1 | 1, mid + 1, idx1, left, right));
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        uint w, d;
        std::cin >> w >> d;

        Block& block = BLOCKS[i];

        block.c0 = d;
        block.c1 = d + w - 1;

        COORDS[++C] = block.c0 - 1;
        COORDS[++C] = block.c0;
        COORDS[++C] = block.c1;
        COORDS[++C] = block.c1 + 1;
    }

    sort_unique_coords();

    for (int i = 1; i <= N; i++)
    {
        Block& block = BLOCKS[i];

        int left = get_coords_idx(block.c0);
        int right = get_coords_idx(block.c1);

        uint h = query(1, 1, C, left, right);
        update(1, 1, C, left, right, h + 1);
    }
    std::cout << query(1, 1, C, 1, C);

    return 0;
}