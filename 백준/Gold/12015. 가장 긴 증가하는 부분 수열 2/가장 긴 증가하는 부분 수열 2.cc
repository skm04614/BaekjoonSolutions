#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int RECORD[1000001];
int M;

void insert_val(int val)
{
	if (M == 0 || val > RECORD[M - 1] )
	{
		RECORD[M++] = val;
		// copy?
		return;
	}

	int left = 0;
	int right = M - 1;
	int mid = 0;
	int insert_idx = 0;
	for (;;)
	{
		if (left > right)
		{
			RECORD[insert_idx] = val;
			return;
		}

		mid = (left + right) / 2;
		if (RECORD[mid] == val)
		{
			return;
		}
		else if (RECORD[mid] > val)
		{
			insert_idx = mid;
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}


}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N;
	std::cin >> N;

	int sol = 0;
	for (int i = 0; i < N; i++)
	{
		int val;
		std::cin >> val;
		insert_val(val);
	}
	std::cout << M;

	return 0;
}