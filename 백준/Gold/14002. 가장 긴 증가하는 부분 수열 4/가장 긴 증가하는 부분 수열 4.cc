#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int ARR[1000100];
int LEN[1000100];
int N;

int RECORD[1000100];
int R;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	RECORD[0] = -0x7FFFFFFF;

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> ARR[i];

		if (ARR[i] > RECORD[R])
		{
			RECORD[++R] = ARR[i];
			LEN[i] = R;
		}
		else
		{
			int left = 0;
			int right = R;
			int mid = 0;
			for (;;)
			{
				if (left > right)
				{
					RECORD[left] = ARR[i];
					LEN[i] = left;
					break;
				}

				mid = (left + right) / 2;
				if (RECORD[mid] < ARR[i])
				{
					left = mid + 1;
				}
				else if (RECORD[mid] > ARR[i])
				{
					right = mid - 1;
				}
				else
				{
					LEN[i] = mid;
					break;
				}
			}
		}
	}

	std::cout << R << '\n';

	int TARGET = R;
	for (int i = N - 1; i >= 0 && TARGET > 0; i--)
	{
		if (LEN[i] == TARGET)
		{
			RECORD[TARGET] = ARR[i];
			TARGET--;
		}
	}

	for (int l = 1; l <= R; l++)
	{
		std::cout << RECORD[l] << ' ';
	}

	return 0;
}