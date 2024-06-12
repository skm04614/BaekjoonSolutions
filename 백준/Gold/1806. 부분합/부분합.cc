#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int ARR[100010];
int N;
int S;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> S;
	for (int i = 0; i < N; i++)
	{
		std::cin >> ARR[i];
	}

	int left = 0;
	int right = 0;
	int sol = 0x7FFFFFFF;
	int sum = ARR[0];
	while (left <= N - 1 && right <= N - 1)
	{
		if (sum >= S)
		{
			sol = sol < (right - left + 1) ? sol : (right - left + 1);
			sum -= ARR[left++];
		}
		else
		{
			sum += ARR[++right];
		}
	}

	if (sol == 0x7FFFFFFF)
	{
		sol = 0;
	}

	std::cout << sol;
	
	return 0;
}