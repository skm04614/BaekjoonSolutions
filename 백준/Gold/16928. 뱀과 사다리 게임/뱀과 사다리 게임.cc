#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int MAP[101]; // 1 <= x <= 100
int RECORD[101];
int PORTALS[101];

int Q[101];
int L;
int R;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N, M;
	std::cin >> N >> M;
	for (int i = 0; i < N + M; i++)
	{
		int src, dest;
		std::cin >> src >> dest;
		PORTALS[src] = dest;
	}

	L = R = -1;
	Q[++R] = 1;
	RECORD[1] = 1;

	while (R > L)
	{
		const int current_pos = Q[++L];

		for (int i = 1; i <= 6; i++)
		{
			int next_pos = current_pos + i;
			if (next_pos > 100)
			{
				continue;
			}

			while (PORTALS[next_pos])
			{
				next_pos = PORTALS[next_pos];
			}

			if (RECORD[next_pos])
			{
				continue;
			}

			RECORD[next_pos] = RECORD[current_pos] + 1;
			Q[++R] = next_pos;
		}
	}

	std::cout << RECORD[100] - 1;

	return 0;
}