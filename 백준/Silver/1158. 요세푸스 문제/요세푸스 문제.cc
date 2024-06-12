#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cmath>


struct Element
{
	Element() : Element(0, nullptr, nullptr) {}
	Element(int val, Element* prev, Element* next) : val{ val }, prev{ prev }, next { next } {}

	int val;
	Element* prev;
	Element* next;
} Pool[500010];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, k;
	std::cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		Pool[i] = Element{ i, &Pool[i - 1], & Pool[i + 1]};
	}
	Pool[n].next = &Pool[1];
	Pool[0].next = &Pool[1];
	Pool[1].prev = &Pool[n];

	Element* current = &Pool[0];

	std::cout << '<';
	for (int j = 0; j < n - 1; j++)
	{
		for (int i = 0; i < k; i++)
		{
			current = current->next;
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;
		std::cout << current->val << ", ";
	}

	std::cout << current->next->val << '>';

	return 0;
}