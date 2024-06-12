#include <iostream>


using ull = unsigned long long;

ull VISITED[550000];

void set_visited(int num)
{
	int idx = (num - 1) / 64;
	int pos = (num - 1) % 64;

	if (!(VISITED[idx] & (1llu << pos)))
	{
		std::cout << num << ' ';
	}
	VISITED[idx] |= (1llu << pos);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int val;
	while (std::cin >> val)
	{
		set_visited(val);
	}

	return 0;
}