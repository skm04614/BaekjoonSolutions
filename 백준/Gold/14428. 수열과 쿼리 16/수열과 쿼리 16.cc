#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int ARR[100010];
int N;

int MIN_IDX_SEG_TREE[400040];

void init(int node, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		MIN_IDX_SEG_TREE[node] = idx0;
		return;
	}

	int mid = (idx0 + idx1) / 2;
	init(2 * node, idx0, mid);
	init(2 * node + 1, mid + 1, idx1);

	if (ARR[MIN_IDX_SEG_TREE[2 * node]] <= ARR[MIN_IDX_SEG_TREE[2 * node + 1]])
	{
		MIN_IDX_SEG_TREE[node] = MIN_IDX_SEG_TREE[2 * node];
	}
	else
	{
		MIN_IDX_SEG_TREE[node] = MIN_IDX_SEG_TREE[2 * node + 1];
	}
}

void apply_change(int node, int idx0, int idx1, int target_idx, int v)
{
	if (target_idx < idx0 || idx1 < target_idx)
	{
		return;
	}

	if (idx0 == idx1)
	{
		ARR[target_idx] = v;
		return;
	}

	int mid = (idx0 + idx1) / 2;
	apply_change(2 * node, idx0, mid, target_idx, v);
	apply_change(2 * node + 1, mid + 1, idx1, target_idx, v);

	if (ARR[MIN_IDX_SEG_TREE[2 * node]] <= ARR[MIN_IDX_SEG_TREE[2 * node + 1]])
	{
		MIN_IDX_SEG_TREE[node] = MIN_IDX_SEG_TREE[2 * node];
	}
	else
	{
		MIN_IDX_SEG_TREE[node] = MIN_IDX_SEG_TREE[2 * node + 1];
	}
}

int query_min_idx(int node, int idx0, int idx1, int left, int right)
{
	if (idx0 > right || idx1 < left)
	{
		return left;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return MIN_IDX_SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	int left_candidate_idx = query_min_idx(2 * node, idx0, mid, left, right);
	int right_candidate_idx = query_min_idx(2 * node + 1, mid + 1, idx1, left, right);
	if (ARR[left_candidate_idx] <= ARR[right_candidate_idx])
	{
		return left_candidate_idx;
	}
	else
	{
		return right_candidate_idx;
	}
}

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
	init(1, 1, N);

	int M;
	std::cin >> M;
	for (int i = 1; i <= M; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		if (a == 1)
		{
			apply_change(1, 1, N, b, c);
		}
		else
		{
			std::cout << query_min_idx(1, 1, N, b, c) << '\n';
		}
	}


	return 0;
}