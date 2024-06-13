#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int S[1001000];
int CNT[1010];
int N, M;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> M;

	CNT[0] = 1;
	
	unsigned long long res = 0;
	for (int i = 1; i <= N; ++i)
	{
		int val;
		std::cin >> val;
		S[i] = (S[i - 1] + val) % M;

		res += (CNT[S[i]]);

		++CNT[S[i]];
	}
	std::cout << res;

	return 0;
}