#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[200200];
int ROOT[200200];
int N;

void init(void)
{
	for (int v = 1; v <= N; v++)
	{
		PARENT[v] = v;
	}
}

int find(int v)
{
	if (v == PARENT[v])
	{
		return v;
	}

	return PARENT[v] = find(PARENT[v]);
}

void _union(int v1, int v2)
{
	v1 = find(v1);
	v2 = find(v2);

	if (v1 < v2)
	{
		PARENT[v2] = v1;
	}
	else
	{
		PARENT[v1] = v2;
	}
}

struct Instruction
{
	int opt;
	int v1;
	int v2;
	bool result;
};

Instruction INST[400400];
int Q;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> Q;

	init();

	for (int v = 2; v <= N; v++)
	{
		std::cin >> ROOT[v];
	}

	Q += N - 1;
	for (int i = 0; i < Q; i++)
	{
		Instruction& inst = INST[i];

		std::cin >> inst.opt >> inst.v1;
		if (inst.opt == 1)
		{
			std::cin >> inst.v2;
		}
	}

	for (int i = Q - 1; i >= 0; i--)
	{
		Instruction& inst = INST[i];

		if (inst.opt == 0)
		{
			_union(inst.v1, ROOT[inst.v1]);
		}
		else
		{
			inst.result = find(inst.v1) == find(inst.v2);
		}
	}

	for (int i = 0; i < Q; i++)
	{
		Instruction& inst = INST[i];

		if (inst.opt == 1)
		{
			std::cout << (inst.result ? "YES" : "NO") << '\n';
		}
	}

	return 0;
}