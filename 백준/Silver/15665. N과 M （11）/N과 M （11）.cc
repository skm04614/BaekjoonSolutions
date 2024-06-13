#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[9];
int RECORD[9];
int N, M;

void sol(int depth)
{
	if (depth == M)
	{
		for (int i = 0; i < M; i++)
		{
			std::cout << RECORD[i] << ' ';
		}
		std::cout << '\n';
		return;
	}
	
	int last_chosen_val = 0;
	for (int i = 0; i < N; i++)
	{
		if (ARR[i] == last_chosen_val)
		{
			continue;
		}

		last_chosen_val = ARR[i];
		RECORD[depth] = ARR[i];
		sol(depth + 1);
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		std::cin >> ARR[i];
	}

	for (int i = 0; i < N; i++)
	{
		int _i = i;
		for (int j = i + 1; j < N; j++)
		{
			if (ARR[j] < ARR[_i])
			{
				_i = j;
			}
		}

		int tmp = ARR[_i];
		ARR[_i] = ARR[i];
		ARR[i] = tmp;
	}

	sol(0);

	return 0;
}