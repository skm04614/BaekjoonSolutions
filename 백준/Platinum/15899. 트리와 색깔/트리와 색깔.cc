#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull MOD = 1000000007;

struct Edge
{
	int v_dest;
	Edge* next;
};
Edge POOL[400400];
Edge* EDGES[200200];
int M;

struct EulerNode
{
	int start;
	int end;
};

EulerNode EN[200200];
int COLOR[200200];
int ARR[200200];
bool VISITED[200200];

int N;
int C;

int dfs(int node, int cnt)
{
	EN[node].start = ++cnt;
	VISITED[node] = true;

	for (Edge* edge = EDGES[node]; edge; edge = edge->next)
	{
		if (VISITED[edge->v_dest])
		{
			continue;
		}
		cnt = dfs(edge->v_dest, cnt);
	}

	EN[node].end = cnt;

	return cnt;
}

struct MergeSortTree
{
	int* seg_tree[800800];

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
				seg_tree[i] = nullptr;
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

		seg_tree[node] = new int[idx1 - idx0 + 1] {};
		int* current_tree = seg_tree[node];
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

	int query_leq(int node, int idx0, int idx1, int left, int right, int c)
	{
		if (idx1 < left || right < idx0)
		{
			return 0;
		}

		if (left <= idx0 && idx1 <= right)
		{
			const int* tree = seg_tree[node];
			int lower = 0;
			int upper = (idx1 - idx0);

			for (;;)
			{
				if (lower > upper)
				{
					break;
				}

				int mid = (lower + upper) >> 1;
				if (c < tree[mid])
				{
					upper = mid - 1;
				}
				else
				{
					lower = mid + 1;
				}
			}
			return lower;
		}

		int mid = (idx0 + idx1) >> 1;
		return query_leq(node << 1, idx0, mid, left, right, c) + query_leq(node << 1 | 1, mid + 1, idx1, left, right, c);
	}
} MST;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M >> C;
	for (int i = 1; i <= N; i++)
	{
		std::cin >> COLOR[i];
	}

	for (int i = 0; i < N - 1; i++)
	{
		int v0, v1;
		std::cin >> v0 >> v1;

		Edge& e1 = POOL[i << 1];
		Edge& e2 = POOL[i << 1 | 1];

		e1.v_dest = v1;
		e1.next = EDGES[v0];
		EDGES[v0] = &e1;

		e2.v_dest = v0;
		e2.next = EDGES[v1];
		EDGES[v1] = &e2;
	}

	dfs(1, 0);

	for (int i = 1; i <= N; i++)
	{
		ARR[EN[i].start] = COLOR[i];
	}

	MST.init(1, 1, N);
	
	ull sol = 0;
	for (int i = 0; i < M; i++)
	{
		int root, c;
		std::cin >> root >> c;

		sol = (sol + MST.query_leq(1, 1, N, EN[root].start, EN[root].end, c)) % MOD;
	}
	std::cout << sol;

	return 0;
}