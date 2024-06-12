#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

bool VISITED_DFS[1010];
bool VISITED_BFS[1010];
bool MAP[1010][1010];
int N;
int M;
int START;

int Q[2020];
int left, right;

void dfs(int n)
{
	if (VISITED_DFS[n])
	{
		return;
	}
	VISITED_DFS[n] = true;
	printf("%d ", n);

	for (int i = 1; i <= N; i++)
	{
		if (MAP[i][n])
		{
			dfs(i);
		}
	}
}

void bfs(int n)
{
	VISITED_BFS[n] = true;
	Q[right++] = n;

	while (right > left)
	{
		int curr = Q[left++];
		printf("%d ", curr);

		for (int i = 1; i <= N; i++)
		{
			if (MAP[i][curr] && !VISITED_BFS[i])
			{
				VISITED_BFS[i] = true;
				Q[right++] = i;
			}
		}
	}
}

int main(void)
{
	scanf("%d %d %d", &N, &M, &START);

	int src, dest;
	for (int m = 0; m < M; m++)
	{
		scanf("%d %d", &src, &dest);
		MAP[src][dest] = MAP[dest][src] = true;
	}

	dfs(START);
	printf("\n");
	bfs(START);


	return 0;
}