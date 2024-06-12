#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int N;
int X_RECORD[101];
bool VISITED[101];
int CNT;

inline int abs_diff(int n, int m)
{
	return n > m ? n - m : m - n;
}

void sol(int depth)
{
	if (depth == N)
	{
		CNT++;
		return;
	}

	for (int x = 0; x < N; x++)
	{
		if (VISITED[x])
		{
			continue;
		}

		bool diagonal_skip = false;
		for (int y = 0; y < depth; y++)
		{
			if (abs_diff(X_RECORD[y], x) == abs_diff(y, depth))
			{
				diagonal_skip = true;
				break;
			}
		}
		
		if (diagonal_skip)
		{
			continue;
		}

		VISITED[x] = true;
		X_RECORD[depth] = x;
		sol(depth + 1);
		X_RECORD[depth] = 0;
		VISITED[x] = false;
	}
}


int main(void)
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		X_RECORD[i] = -1;
		VISITED[i] = false;
	}
	CNT = 0;

	sol(0);
	printf("%d", CNT);

	return 0;
}
