#include <cstdio>
#include <iostream>

int map[501][501];
bool visited[501][501];
int n;
int m;

int solution(int i, int j)
{
	if (i < 0 || j < 0 || i >= n || j >= m)
	{
		return 0;
	}

	if (!map[i][j])
	{
		return 0;
	}

	if (visited[i][j])
	{
		return 0;
	}
	visited[i][j] = true;
	
	return map[i][j] + solution(i + 1, j) + solution(i - 1, j) + solution(i, j + 1) + solution(i, j - 1);
}

int main(void)
{
	std::cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cin >> map[i][j];
		}
	}

	int max_area = 0;
	int cnt = 0;
	int area = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			area = solution(i, j);
			cnt += area > 0;
			max_area = max_area > area ? max_area : area;
		}
	}

	printf("%d\n%d", cnt, max_area);

	return 0;
}