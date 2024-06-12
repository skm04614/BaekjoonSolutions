#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

struct Seg
{
    int min_tree[200200];
    int max_tree[200200];
    int bias;

    Seg() : min_tree{}, max_tree{}, bias{}
    {

    }

    void init(int N)
    {
        for (bias = 1; bias < N; bias <<= 1);
        --bias;
    }

    void update(int idx, int val)
    {
        idx += bias;
        min_tree[idx] = max_tree[idx] = val;

        while (idx >>= 1)
        {
            min_tree[idx] = min(min_tree[idx << 1], min_tree[idx << 1 | 1]);
            max_tree[idx] = max(max_tree[idx << 1], max_tree[idx << 1 | 1]);
        }
    }

    int query(int l, int r)
    {
        l += bias;
        r += bias;

        int _min = 0x7FFFFFFF;
        int _max = 0;

        while (l < r)
        {
            if (l & 1)
            {
                _min = min(min_tree[l], _min);
                _max = max(max_tree[l], _max);
                ++l;
            }

            if (~r & 1)
            {
                _min = min(min_tree[r], _min);
                _max = max(max_tree[r], _max);
                --r;
            }

            l >>= 1;
            r >>= 1;
        }

        if (l == r)
        {
            _min = min(min_tree[r], _min);
            _max = max(max_tree[r], _max);
        }

        return _max - _min;
    }
};

Seg SEG;
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int Q;
    std::cin >> N >> Q;
    SEG.init(N);
    for (int i = 1; i <= N; ++i)
    {
        int val;
        std::cin >> val;
        SEG.update(i, val);
    }

    while (Q--)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << SEG.query(l, r) << '\n';
    }


    return 0;
}