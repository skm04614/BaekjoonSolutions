#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int mbti_diff(int mbti_1, int mbti_2)
{
	int mbti_difference = mbti_1 ^ mbti_2;

	int res = 0;
	for (int i = 0; i < 4; i++)
	{
		res += (mbti_difference & 1);
		mbti_difference >>= 1;
	}
	return res;
}

int min(int x, int y)
{
	return x < y ? x : y;
}

int sol(int* arr, int depth)
{
	static int record[3] = {};

	if (depth == 3)
	{
		return mbti_diff(record[0], record[2]) + mbti_diff(record[1], record[2]) + mbti_diff(record[0], record[1]);
	}

	int res = 0x7FFFFFFF;
	for (int i = 0; i < 16; i++)
	{
		if (arr[i] == 0)
		{
			continue;
		}

		record[depth] = i;
		arr[i]--;
		res = min(res, sol(arr, depth + 1));
		arr[i]++;
	}

	return res;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		int N;
		std::cin >> N;
		int cnt[16] = {};
		for (int n = 0; n < N; n++)
		{
			char _mbti[5];
			std::cin >> _mbti;

			int mbti = 0;
			mbti |= (_mbti[0] == 'I') << 3;
			mbti |= (_mbti[1] == 'S') << 2;
			mbti |= (_mbti[2] == 'T') << 1;
			mbti |= (_mbti[3] == 'P') << 0;

			cnt[mbti]++;
		}
		std::cout << sol(cnt, 0) << '\n';
	}
	
	return 0;
}