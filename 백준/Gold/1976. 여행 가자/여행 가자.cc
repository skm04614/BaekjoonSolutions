#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[210];
int N;

void init(void)
{
	for (register int v = 1; v <= N; v++)
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

int CITIES[1010];
int M;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;

	init();

	for (register int i = 1; i <= N; i++)
	{
		for (register int j = 1; j <= N; j++)
		{
			register int c;
			std::cin >> c;

			if (c)
			{
				_union(i, j);
			}
		}
	}

	for (register int i = 1; i <= M; i++)
	{
		std::cin >> CITIES[i];
	}

	bool success = true;
	for (register int i = 1; i <= M; i++)
	{
		if (find(CITIES[i]) != find(CITIES[1]))
		{
			success = false;
			break;
		}
	}

	std::cout << (success ? "YES" : "NO");

	return 0;
}