#include <stdio.h>

int Data[1000000];
int N;
int B, C;

void input(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &Data[i]);
	}
	scanf("%d %d", &B, &C);
}

long long count(void) {
	long long result = 0;
	for (int i = 0; i < N; i++) {
		Data[i] -= B;
		result++;
		if (Data[i] > 0) {
			result += (Data[i] / C) + (Data[i] % C ? 1 : 0);
		}
	}
	return result;
}

int main(void) {
	input();
	printf("%lld", count());

	return 0;
}