#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

struct Element
{
	int val[10];

	Element() : val{}
	{

	}

	void rotate(int cnt)
	{
		cnt %= 10;
		if (cnt == 0)
		{
			return;
		}

		Element tmp = *this;

		for (int i = 0; i < 10; i++)
		{
			val[(i + cnt) % 10] = tmp.val[i];
		}
	}

	Element& operator+=(const Element& other)
	{
		for (int i = 0; i < 10; i++)
		{
			val[i] += other.val[i];
		}
		return *this;
	}
	
	Element operator+(const Element& other) const
	{
		Element result;
		for (int i = 0; i < 10; i++)
		{
			result.val[i] = val[i] + other.val[i];
		}
		return result;
	}

	int sum() const
	{
		int res = 0;
		for (int i = 0; i < 10; i++)
		{
			res += i * val[i];
		}
		return res;
	}
};

Element ARR[250250];
Element SEG_TREE[1001000];
int LAZY[1001000];
int N;

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
		SEG_TREE[node].rotate(LAZY[node]);
		if (idx0 != idx1)
		{
			LAZY[2 * node] += LAZY[node];
			LAZY[2 * node + 1] += LAZY[node];
		}
		LAZY[node] = 0;
	}
}

void increment(int node, int idx0, int idx1, int left, int right)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		SEG_TREE[node].rotate(1);
		if (idx0 != idx1)
		{
			LAZY[2 * node]++;
			LAZY[2 * node + 1]++;
		}
		return;
	}

	int mid = (idx0 + idx1) / 2;
	increment(2 * node, idx0, mid, left, right);
	increment(2 * node + 1, mid + 1, idx1, left, right);

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

int query(int node, int idx0, int idx1, int left, int right)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node].sum();
	}

	int mid = (idx0 + idx1) / 2;
	return query(2 * node, idx0, mid, left, right) + query(2 * node + 1, mid + 1, idx1, left, right);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int M;
	std::cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		char c;
		std::cin >> c;
		ARR[i].val[c - '0']++;
	}
	init(1, 1, N);

	for (int i = 1; i <= M; i++)
	{
		int left, right;
		std::cin >> left >> right;
		std::cout << query(1, 1, N, left, right) << '\n';
		increment(1, 1, N, left, right);
	}
	
	return 0;
}