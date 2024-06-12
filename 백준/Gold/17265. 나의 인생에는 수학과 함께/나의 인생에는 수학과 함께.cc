#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char MAP[7][7];
int RECORD_MAX[7][7];
int RECORD_MIN[7][7];
int N;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int max(int x, int y)
{
	return x > y ? x : y;
}

struct Coords
{
	int y;
	int x;

	Coords move(int opt) const
	{
		switch (opt)
		{
		case 0:
			return { y + 1, x };
		default:
			return { y, x + 1 };
		}
	}

	bool is_out_of_bounds() const
	{
		return y < 0 || x < 0 || y >= N || x >= N;
	}
};

void sol(const Coords num)
{
	if (num.y == N - 1 && num.x == N - 1)
	{
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		const Coords op = num.move(i);
		if (op.is_out_of_bounds())
		{
			continue;
		}

		for (int j = 0; j < 2; j++)
		{
			const Coords num2 = op.move(j);
			if (num2.is_out_of_bounds())
			{
				continue;
			}

			int result_max = 0;
			int result_min = 0;
			switch (MAP[op.y][op.x])
			{
			case '+':
				result_max = RECORD_MAX[num.y][num.x] + (MAP[num2.y][num2.x] - '0');
				result_min = RECORD_MIN[num.y][num.x] + (MAP[num2.y][num2.x] - '0');
				break;
			case '-':
				result_max = RECORD_MAX[num.y][num.x] - (MAP[num2.y][num2.x] - '0');
				result_min = RECORD_MIN[num.y][num.x] - (MAP[num2.y][num2.x] - '0');
				break;
			default:
				result_max = RECORD_MAX[num.y][num.x] * (MAP[num2.y][num2.x] - '0');
				result_min = RECORD_MIN[num.y][num.x] * (MAP[num2.y][num2.x] - '0');
				break;
			}
			RECORD_MAX[num2.y][num2.x] = max(RECORD_MAX[num2.y][num2.x], result_max);
			RECORD_MIN[num2.y][num2.x] = min(RECORD_MIN[num2.y][num2.x], result_min);

			sol(num2);
		}
	}
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
			RECORD_MAX[i][j] = -0x7FFFFFFF;
			RECORD_MIN[i][j] = 0x7FFFFFFF;
		}
	}

	RECORD_MAX[0][0] = RECORD_MIN[0][0] = (MAP[0][0] - '0');
	sol({ 0, 0 });
	std::cout << RECORD_MAX[N - 1][N - 1] << ' ' << RECORD_MIN[N - 1][N - 1];

	return 0;
}