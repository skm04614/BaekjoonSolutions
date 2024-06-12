#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Relationship
{
	int v;
	Relationship* next;

	Relationship(int v, Relationship* next) : v{ v }, next{ next }
	{
	}

	~Relationship()
	{
		if (next)
		{
			delete next;
			next = nullptr;
		}
	}
};

Relationship* REL[100100];

struct EulerNode
{
	int start;
	int end;
};

EulerNode EN[100100];
int E;

void dfs(int node)
{
	E++;
	EN[node].start = E;

	for (Relationship* r = REL[node]; r; r = r->next)
	{
		dfs(r->v);
	}
	delete REL[node];
	REL[node] = nullptr;

	EN[node].end = E;
}

using ull = unsigned long long;
ull SEG_TREE[400400];
ull LAZY[400400];

void propagate(int node, int idx0, int idx1)
{
	if (LAZY[node])
	{
		SEG_TREE[node] += (idx1 - idx0 + 1) * LAZY[node];

		if (idx0 != idx1)
		{
			LAZY[2 * node] += LAZY[node];
			LAZY[2 * node + 1] += LAZY[node];
		}

		LAZY[node] = 0;
	}
}

void increment(int node, int idx0, int idx1, int left, int right, int k)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		LAZY[node] += k;
		propagate(node, idx0, idx1);
		return;
	}

	int mid = (idx0 + idx1) / 2;
	increment(2 * node, idx0, mid, left, right, k);
	increment(2 * node + 1, mid + 1, idx1, left, right, k);

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

ull query(int node, int idx0, int idx1, int target_idx)
{
	propagate(node, idx0, idx1);

	if (idx1 < target_idx || target_idx < idx0)
	{
		return 0;
	}

	if (idx0 == target_idx && idx1 == target_idx)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return query(2 * node, idx0, mid, target_idx) + query(2 * node + 1, mid + 1, idx1, target_idx);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	
	int N;
	int Q;
	std::cin >> N >> Q;
	for (int i = 1; i <= N; i++)
	{
		int parent;
		std::cin >> parent;
		if (parent == -1)
		{
			continue;
		}

		REL[parent] = new Relationship{ i, REL[parent] };
	}
	
	dfs(1);

	for (int i = 1; i <= Q; i++)
	{
		int a, b;
		std::cin >> a >> b;
		if (a == 1)
		{
			int c;
			std::cin >> c;

			increment(1, 1, N, EN[b].start, EN[b].end, c);
		}
		else
		{
			std::cout << query(1, 1, N, EN[b].start) << '\n';
		}
	}

	return 0;
}