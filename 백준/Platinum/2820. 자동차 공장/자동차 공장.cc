#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

struct Connection
{
	int target;
	Connection* next;

	Connection(int target, Connection* next) : target{ target }, next{ next }
	{

	}

	~Connection()
	{
		if (next)
		{
			delete next;
			next = nullptr;
		}
	}
};
Connection* C[500500];

struct EulerNode
{
	int start;
	int end;
};
EulerNode ER[500500];

int ARR[500500];
ll SEG_TREE[2002000];
ll LAZY[2002000];
int R;

int N;
int M;

void dfs(int node)
{
	++R;
	ER[node].start = R;

	for (Connection* c = C[node]; c; c = c->next)
	{
		dfs(c->target);
	}

	delete C[node];
	C[node] = nullptr;

	ER[node].end = R;
}


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

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

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

void update(int node, int idx0, int idx1, int left, int right, ll k)
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
	update(2 * node, idx0, mid, left, right, k);
	update(2 * node + 1, mid + 1, idx1, left, right, k);

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

ll query(int node, int idx0, int idx1, int left, int right)
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

	int mid = (idx0 + idx1) / 2;
	return query(2 * node, idx0, mid, left, right) + query(2 * node + 1, mid + 1, idx1, left, right);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;

	int* tmp = new int[N + 100] {};
	std::cin >> tmp[1];
	for (int i = 2; i <= N; i++)
	{
		int parent;
		std::cin >> tmp[i] >> parent;
		C[parent] = new Connection{ i, C[parent] };
	}

	R = 0;
	dfs(1);

	for (int i = 1; i <= N; i++)
	{
		ARR[ER[i].start] = tmp[i];
	}
	delete[] tmp;

	init(1, 1, N);

	for (int i = 1; i <= M; i++)
	{
		char q;
		int a;
		std::cin >> q >> a;
		if (q == 'p')
		{
			int b;
			std::cin >> b;
			update(1, 1, N, ER[a].start + 1, ER[a].end, b);
		}
		else
		{
			std::cout << query(1, 1, N, ER[a].start, ER[a].start) << '\n';
		}
	}

	return 0;
}