#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[1000100];
int N;

void init()
{
	for (int i = 1; i <= 1000000; i++)
	{
		PARENT[i] = i;
	}
}

int find(int v)
{
	if (v == PARENT[v])
	{
		return v;
	}

	return (PARENT[v] = find(PARENT[v]));
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

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int M;
	std::cin >> N >> M;
	init();
	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		if (a == 1)
		{
			std::cout << (find(b) == find(c) ? "YES" : "NO") << '\n';
		}
		else
		{
			_union(b, c);
		}
	}

	return 0;
}