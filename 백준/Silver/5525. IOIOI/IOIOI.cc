#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int N;
int M;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;

	int target_len = 2 * N + 1;
	int current_len = 0;
	bool flag = true;
	int cnt = 0;
	for (int i = 0; i < M; i++)
	{
		char c;
		std::cin >> c;

		if (flag == (c == 'I'))
		{
			current_len++;
			flag ^= true;
		}
		else
		{
			if (current_len >= target_len)
			{
				cnt += ((current_len + 2 - target_len) / 2);
			}

			flag = (c != 'I');
			current_len = (c == 'I');
		}
	}

	if (current_len >= target_len)
	{
		cnt += ((current_len + 2 - target_len) / 2);
	}

	std::cout << cnt;


	return 0;
}