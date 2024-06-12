#include <cstdio>

int gRec[2][3] = {};

inline int max(const int& n, const int& m)
{
	return n > m ? n : m;
}

int main(void)
{
	int N = 0;
	scanf("%d", &N);
	scanf("%d", &gRec[0][1]);

	int* curr = gRec[0];
	int* prev = gRec[1];
	int val = 0;
	for (int i = 1; i < N; i++)
	{
		curr = gRec[i % 2];
		prev = gRec[(i + 1) % 2];
		scanf("%d", &val);
		curr[0] = max(max(prev[0], prev[1]), prev[2]);
		curr[1] = prev[0] + val;
		curr[2] = prev[1] + val;
	}

	printf("%d", max(max(curr[0], curr[1]), curr[2]));
	return 0;
}