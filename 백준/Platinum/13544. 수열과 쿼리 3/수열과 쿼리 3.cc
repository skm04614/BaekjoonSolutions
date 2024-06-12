#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull ARR[100100];
int N;

struct MergeSortTree
{
    ull* seg_tree[400400];

    MergeSortTree() : seg_tree{}
    {
        for (int i = 0; i < 400400; i++)
        {
            if (seg_tree[i])
            {
                delete[] seg_tree[i];
            }
        }
    }

    void init(int node, int idx0, int idx1)
    {
        if (idx0 == idx1)
        {
            seg_tree[node] = new ull[1]{ ARR[idx0] };
            return;
        }

        int mid = (idx0 + idx1) / 2;
        init(2 * node, idx0, mid);
        init(2 * node + 1, mid + 1, idx1);

        ull*& current_tree = seg_tree[node];
        current_tree = new ull[idx1 - idx0 + 1]{};
        int idx = 0;

        const ull* left_tree = seg_tree[2 * node];
        int left = 0;
        const int left_max = mid - idx0;

        const ull* right_tree = seg_tree[2 * node + 1];
        int right = 0;
        const int right_max = idx1 - (mid + 1);

        for (;;)
        {
            if (left > left_max || right > right_max)
            {
                break;
            }

            if (left_tree[left] < right_tree[right])
            {
                current_tree[idx++] = left_tree[left++];
            }
            else
            {
                current_tree[idx++] = right_tree[right++];
            }
        }

        while (left <= left_max)
        {
            current_tree[idx++] = left_tree[left++];
        }

        while (right <= right_max)
        {
            current_tree[idx++] = right_tree[right++];
        }
    }

    ull query(int node, int idx0, int idx1, ull left, ull right, ull k) const
    {
        if (idx1 < left || right < idx0)
        {
            return 0;
        }

        if (left <= idx0 && idx1 <= right)
        {
            const ull* tree = seg_tree[node];

            int lower = 0;
            int upper = idx1 - idx0;
            int mid;
            for (;;)
            {
                if (lower > upper)
                {
                    break;
                }

                mid = (lower + upper) / 2;
                if (tree[mid] <= k)
                {
                    lower = mid + 1;
                }
                else
                {
                    upper = mid - 1;
                }
            }

            return (idx1 - idx0) - upper;
        }

        int mid = (idx0 + idx1) / 2;
        return query(2 * node, idx0, mid, left, right, k) + query(2 * node + 1, mid + 1, idx1, left, right, k);
    }
} MST;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i];
    }

    MST.init(1, 1, N);
    
    int M;
    std::cin >> M;

    ull last_ans = 0;
    while (M--)
    {
        ull a, b, c;
        std::cin >> a >> b >> c;
        a ^= last_ans;
        b ^= last_ans;
        c ^= last_ans;

        last_ans = MST.query(1, 1, N, a, b, c);
        std::cout << last_ans << '\n';
    }

    return 0;
}