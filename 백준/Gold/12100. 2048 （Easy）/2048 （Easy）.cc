#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int Original[20][20];
int Board[20][20];
int N;
int Max;

void input(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Original[i][j]);
		}
	}
}

void init(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Board[i][j] = Original[i][j];
		}
	}
}

void moveUp(void) {
	int idx;
	int n1, n2;
	for (int j = 0; j < N; j++) {
		idx = 0;
		for (int i = 0; i < N; i++) {
			if (Board[i][j] == 0 || i == idx) {
				continue;
			}

			n1 = Board[i][j];
			if (Board[idx][j] == 0) {
				Board[i][j] = 0;
				Board[idx][j] = n1;
			}
			else if (Board[idx][j] == Board[i][j]) {
				n2 = Board[idx][j];
				Board[i][j] = Board[idx][j] = 0;
				Board[idx++][j] = n1 + n2;
			}
			else {
				Board[i][j] = 0;
				Board[++idx][j] = n1;
			}
		}
	}
}

void moveDown(void) {
	int idx;
	int n1, n2;
	for (int j = 0; j < N; j++) {
		idx = N - 1;
		for (int i = N - 1; i >= 0; i--) {
			if (Board[i][j] == 0 || i == idx) {
				continue;
			}

			n1 = Board[i][j];
			if (Board[idx][j] == 0) {
				Board[i][j] = 0;
				Board[idx][j] = n1;
			}
			else if (Board[idx][j] == Board[i][j]) {
				n2 = Board[idx][j];
				Board[i][j] = Board[idx][j] = 0;
				Board[idx--][j] = n1 + n2;
			}
			else {
				Board[i][j] = 0;
				Board[--idx][j] = n1;
			}
		}
	}
}

void moveLeft(void) {
	int idx;
	int n1, n2;
	for (int i = 0; i < N; i++) {
		idx = 0;
		for (int j = 0; j < N; j++) {
			if (Board[i][j] == 0 || j == idx) {
				continue;
			}

			n1 = Board[i][j];
			if (Board[i][idx] == 0) {
				Board[i][j] = 0;
				Board[i][idx] = n1;
			}
			else if (Board[i][idx] == Board[i][j]) {
				n2 = Board[i][idx];
				Board[i][j] = Board[i][idx] = 0;
				Board[i][idx++] = n1 + n2;
			}
			else {
				Board[i][j] = 0;
				Board[i][++idx] = n1;
			}
		}
	}
}

void moveRight(void) {
	int idx;
	int n1, n2;
	for (int i = 0; i < N; i++) {
		idx = N - 1;
		for (int j = N - 1; j >= 0; j--) {
			if (Board[i][j] == 0 || j == idx) {
				continue;
			}

			n1 = Board[i][j];
			if (Board[i][idx] == 0) {
				Board[i][j] = 0;
				Board[i][idx] = n1;
			}
			else if (Board[i][idx] == Board[i][j]) {
				n2 = Board[i][idx];
				Board[i][j] = Board[i][idx] = 0;
				Board[i][idx--] = n1 + n2;
			}
			else {
				Board[i][j] = 0;
				Board[i][--idx] = n1;
			}
		}
	}
}

void move(int type) {
	switch (type) {
	case 0:
		moveUp();
		return;
	case 1:
		moveDown();
		return;
	case 2:
		moveLeft();
		return;
	case 3:
		moveRight();
		return;
	}
}

int getMax(void) {
	int max = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			max = MAX(max, Board[i][j]);
		}
	}
	return max;
}

void DFS(int n) {
	static int record[5];
	if (n == 5) {
		init();
		for (int i = 0; i < 5; i++) {
			move(record[i]);
		}

		Max = MAX(Max, getMax());
		return;
	}

	for (int i = 0; i < 4; i++) {
		record[n] = i;
		DFS(n + 1);
	}
}

int main(void) {
	input();
	DFS(0);
	printf("%d", Max);

	return 0;
}