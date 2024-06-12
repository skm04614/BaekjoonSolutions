#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int MIN = 1000001;
int MAX = -1000001;


int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int val;
		scanf("%d", &val);
		MIN = MIN < val ? MIN : val;
		MAX = MAX > val ? MAX : val;
	}
	printf("%d %d", MIN, MAX);

	return 0;
}