#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[10001];
int K;
int N;
int MAX_LEN;

void sol(long long lower, long long upper)
{
	if (lower > upper)
	{
		return;
	}

	long long mid = (lower + upper) / 2;
	int cnt = 0;
	for (int k = 0; k < K; k++)
	{
		cnt += (ARR[k] / mid);
	}

	if (cnt < N)
	{
		sol(lower, mid - 1);
	}
	else
	{
		MAX_LEN = MAX_LEN > mid ? MAX_LEN : mid;
		sol(mid + 1, upper);
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> K >> N;
	for (int i = 0; i < K; i++)
	{
		std::cin >> ARR[i];
	}
	
	sol(1, 0x7FFFFFFF);
	std::cout << MAX_LEN; 

	return 0;
}