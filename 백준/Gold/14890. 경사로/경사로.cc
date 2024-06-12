#include <stdio.h>

int Map[100][100];
int N;
int L;

void input(void) {
	scanf("%d %d", &N, &L);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
}

int isValidRow(int r) {
	int cnt = 0;
	int lastVal = Map[r][0];
	for (int c = 0; c < N; c++) {
		if (Map[r][c] == lastVal) {
			cnt++;
		}
		else if (Map[r][c] == lastVal - 1) {
			if (cnt < 0) {
				return 0;
			}
			cnt = 1 - L;
		}
		else if (Map[r][c] == lastVal + 1) {
			if (cnt < L) {
				return 0;
			}
			cnt = 1;
		}
		else {
			return 0;
		}
		lastVal = Map[r][c];
	}

	return cnt >= 0;
}

int isValidCol(int c) {
	int cnt = 0;
	int lastVal = Map[0][c];
	for (int r = 0; r < N; r++) {
		if (Map[r][c] == lastVal) {
			cnt++;
		}
		else if (Map[r][c] == lastVal - 1) {
			if (cnt < 0) {
				return 0;
			}
			cnt = 1 - L;
		}
		else if (Map[r][c] == lastVal + 1) {
			if (cnt < L) {
				return 0;
			}
			cnt = 1;
		}
		else {
			return 0;
		}
		lastVal = Map[r][c];
	}

	return cnt >= 0;
}

int count(void) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		cnt += isValidRow(i);
		cnt += isValidCol(i);
	}
	return cnt;
}

int main(void) {
	input();
	printf("%d", count());

	return 0;
}