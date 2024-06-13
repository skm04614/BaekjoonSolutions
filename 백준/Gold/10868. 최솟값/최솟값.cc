#include <iostream>

using ull = unsigned long long;

ull ARR[100010];

ull SEG_TREE[400040];

int N, M;

inline ull min(ull x, ull y)

{

	return x < y ? x : y;}

void init(int node, int idx0, int idx1)

{

	if (idx0 == idx1)

	{

		SEG_TREE[node] = ARR[idx0];

		return;

	}

	

	int mid = (idx0 + idx1) / 2;

	init(2 * node, idx0, mid);

	init(2 * node + 1, mid + 1, idx1);

	

	SEG_TREE[node] = min(SEG_TREE[2 * node], SEG_TREE[2 * node + 1]);

}

ull get_min(int node, int idx0, int idx1, int left, int right)

{

	if (idx0 > right || idx1 < left)

	{

		return 0xFFFFFFFF;

	}

    if (idx0 >= left && idx1 <= right)

    {

        return SEG_TREE [node];

    }

    int mid = (idx0 + idx1) / 2;

	return min(get_min(2 * node, idx0, mid, left, right), get_min(2 * node + 1, mid + 1, idx1, left, right));

}

int main(void)

{

	std::ios_base::sync_with_stdio(false);

	std::cin.tie(nullptr);

	std::cout.tie(nullptr);

    std::cin >> N >> M;

    for (int n = 0; n < N; n++)

    {

        std::cin >> ARR[n];

    }

    init(1, 0, N - 1);

    for (int m = 0; m < M; m++)

    {

        int left, right;

        std::cin >> left >> right;

        left--;

        right--;

        std::cout << get_min(1, 0, N - 1, left, right) << '\n';

    }

    

	return 0;

}