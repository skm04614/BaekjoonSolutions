#include <stdio.h>

#define MAX_SIZE 500
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int numbers[MAX_SIZE + 1][MAX_SIZE + 1];

int sol(int(*numbers)[MAX_SIZE + 1], int idx, int depth, int size) {
	static result[MAX_SIZE + 1][MAX_SIZE + 1];
	if (depth == size) {
		return 0;
	}

	if (!result[depth][idx]) {
		result[depth][idx] = numbers[depth][idx] + MAX(sol(numbers, idx, depth + 1, size), sol(numbers, idx + 1, depth + 1, size));
	}

	return result[depth][idx];
}

int main(void) {
	int size;
	scanf("%d", &size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j <= i; j++) {
			scanf("%d", &numbers[i][j]);
		}
	}

	printf("%d", sol(numbers, 0, 0, size));

	return 0;
}