#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Person
{
	int weight;
	int height;

	bool operator>(const Person& other) const
	{
		return height > other.height && weight > other.weight;
	}
};

Person POOL[51];
int N;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> POOL[i].height >> POOL[i].weight;
	}

	for (int i = 0; i < N; i++)
	{
		int rank = 1;
		for (int j = 0; j < N; j++)
		{
			if (POOL[j] > POOL[i])
			{
				rank++;
			}
		}
		std::cout << rank << ' ';
	}

	return 0;
}