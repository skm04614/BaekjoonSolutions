#include <stdio.h>

int Numbers[11];
int N;
int OpStock[4];
int Max;
int Min;

int op(int x, int y, int type) {
	switch (type) {
	case 0:
		return x + y;
	case 1:
		return x - y;
	case 2:
		return x * y;
	case 3:
		return x / y;
	default:
		return 0;
	}
}

void DFS(int n, int result) {
	if (n == N - 1) {
		Max = Max > result ? Max : result;
		Min = Min < result ? Min : result;
	}

	for (int i = 0; i < 4; i++) {
		if (!OpStock[i]) {
			continue;
		}

		OpStock[i]--;
		DFS(n + 1, op(result, Numbers[n + 1], i));
		OpStock[i]++;
	}
}

void input(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &Numbers[i]);
	}

	for (int i = 0; i < 4; i++) {
		scanf("%d", &OpStock[i]);
	}

	Min = 0x7FFFFFFF;
	Max = 0x80000000;
}

int main(void) {
	input();
	DFS(0, Numbers[0]);
	printf("%d\n%d", Max, Min);
	return 0;
}