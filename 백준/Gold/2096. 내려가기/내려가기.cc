#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int DP_MIN[2][3];
int DP_MAX[2][3];

inline int max(int x, int y)
{
	return x > y ? x : y;
}

inline int min(int x, int y)
{
	return x < y ? x : y;
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N;
	std::cin >> N;

	int p = 0;
	int c = 1;
	int val[3];
	for (int i = 0; i < N; i++)
	{
		std::cin >> val[0] >> val[1] >> val[2];

		DP_MAX[c][0] = DP_MIN[c][0] = val[0];
		DP_MAX[c][1] = DP_MIN[c][1] = val[1];
		DP_MAX[c][2] = DP_MIN[c][2] = val[2];

		DP_MAX[c][0] += max(DP_MAX[p][0], DP_MAX[p][1]);
		DP_MAX[c][1] += max(max(DP_MAX[p][0], DP_MAX[p][1]), DP_MAX[p][2]);
		DP_MAX[c][2] += max(DP_MAX[p][1], DP_MAX[p][2]);

		DP_MIN[c][0] += min(DP_MIN[p][0], DP_MIN[p][1]);
		DP_MIN[c][1] += min(min(DP_MIN[p][0], DP_MIN[p][1]), DP_MIN[p][2]);
		DP_MIN[c][2] += min(DP_MIN[p][1], DP_MIN[p][2]);

		p ^= 1;
		c ^= 1;
	}

	int sol_max = max(max(DP_MAX[p][0], DP_MAX[p][1]), DP_MAX[p][2]);
	int sol_min = min(min(DP_MIN[p][0], DP_MIN[p][1]), DP_MIN[p][2]);
	std::cout << sol_max << ' ' << sol_min;

	return 0;
}