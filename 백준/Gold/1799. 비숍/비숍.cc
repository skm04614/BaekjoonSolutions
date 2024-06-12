#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int MAP[12][12];
int DIAG_MAP[24][24];
int N;

unsigned long long SOL;

int get_diag_idx(int axis, int y, int x)
{
	return axis ? (N - 1) - (y - x) : y + x;
}

void sol(int depth, unsigned int axis_record, unsigned long long cnt)
{
	if (depth == 2 * N - 1)
	{
		SOL = SOL > cnt ? SOL : cnt;
		return;
	}

	if (2 * N - 1 - depth + cnt <= SOL)
	{
		return;
	}

	for (int i = 0; i < 2 * N - 1; i++)
	{
		if (DIAG_MAP[depth][i] == 0 || axis_record & (1u << i))
		{
			continue;
		}

		sol(depth + 1, axis_record | (1u << i), cnt + 1);
	}
	sol(depth + 1, axis_record, cnt);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cin >> MAP[i][j];
			DIAG_MAP[get_diag_idx(0, i, j)][get_diag_idx(1, i, j)] = MAP[i][j];
		}
	}
	sol(0, 0, 0);
	std::cout << SOL;
	

	return 0;
}