#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int ARR[100010];
int N;
int SOL = 0x7FFFFFFF;
int SOL_VALS[2] = { -0x7FFFFFFF, 0x7FFFFFFF };


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> ARR[i];
	}
	
	int left = 0;
	int right = N - 1;

	while (left < right)
	{
		int sum = ARR[left] + ARR[right];
		int abs_sum = abs(sum);

		if (abs_sum < SOL)
		{
			SOL = abs_sum;
			SOL_VALS[0] = ARR[left];
			SOL_VALS[1] = ARR[right];
		}

		if (sum < 0)
		{
			left++;
		}
		else
		{
			right--;
		}
	}

	std::cout << SOL_VALS[0] << ' ' << SOL_VALS[1];

	return 0;
}