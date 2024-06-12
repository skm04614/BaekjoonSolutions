#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int max(int n, int m)
{
	return n > m ? n : m;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int arr[3];
	std::cin >> arr[0] >> arr[1] >> arr[2];

	if (arr[1] > arr[0])
	{
		int tmp = arr[0];
		arr[0] = arr[1];
		arr[1] = tmp;
	}

	if (arr[2] > arr[0])
	{
		int tmp = arr[0];
		arr[0] = arr[2];
		arr[2] = tmp;
	}

	if (arr[2] > arr[1])
	{
		int tmp = arr[1];
		arr[1] = arr[2];
		arr[2] = tmp;
	}

	std::cout << arr[1];

	return 0;
}