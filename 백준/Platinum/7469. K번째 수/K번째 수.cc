#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[100100];
int N;

struct MergeSortTree
{
    int* seg_tree[400400];

    MergeSortTree() : seg_tree{}
    {

    }

    ~MergeSortTree()
    {
        for (int i = 0; i < sizeof(seg_tree) / sizeof(seg_tree[0]); i++)
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
            seg_tree[node] = new int[1] {ARR[idx0]};
            return;
        }

        int mid = (idx0 + idx1) >> 1;
        init(node << 1, idx0, mid);
        init(node << 1 | 1, mid + 1, idx1);
        
        int*& current_tree = seg_tree[node];
        current_tree = new int[idx1 - idx0 + 1] {};
        int idx = 0;

        const int* left_tree = seg_tree[node << 1];
        int left = 0;

        const int* right_tree = seg_tree[node << 1 | 1];
        int right = 0;

        for (;;)
        {
            if (left > (mid - idx0) || right > (idx1 - (mid + 1)))
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

        while (left <= (mid - idx0))
        {
            current_tree[idx++] = left_tree[left++];
        }

        while (right <= (idx1 - (mid + 1)))
        {
            current_tree[idx++] = right_tree[right++];
        }
    }

    int cnt(int node, int idx0, int idx1, int left, int right, int k) const
    {
        if (idx1 < left || right < idx0)
        {
            return 0;
        }

        if (left <= idx0 && idx1 <= right)
        {
            const int* current_tree = seg_tree[node];
            int lower = 0;
            int upper = idx1 - idx0;
            int mid;

            for (;;)
            {
                if (lower > upper)
                {
                    return lower;
                }

                mid = (lower + upper) >> 1;
                if (current_tree[mid] > k)
                {
                    upper = mid - 1;
                }
                else
                {
                    lower = mid + 1;
                }
            }
        }

        int mid = (idx0 + idx1) >> 1;
        return cnt(node << 1, idx0, mid, left, right, k) + cnt(node << 1 | 1, mid + 1, idx1, left, right, k);
    }

    int query(int node, int idx0, int idx1, int left, int right, int target_cnt)
    {
        int lower = static_cast<int>(-1e9);
        int upper = static_cast<int>(1e9);
        int mid;
        for (;;)
        {
            if (lower > upper)
            {
                return lower;
            }

            mid = (lower + upper) >> 1;
            int res = cnt(node, idx0, idx1, left, right, mid);
            if (res >= target_cnt)
            {
                upper = mid - 1;
            }
            else
            {
                lower = mid + 1;
            }
        }
    }
};

MergeSortTree MST;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int Q;
    std::cin >> N >> Q;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i];
    }

    MST.init(1, 1, N);

    while (Q--)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        std::cout << MST.query(1, 1, N, a, b, c) << '\n';
    }

    return 0;
}