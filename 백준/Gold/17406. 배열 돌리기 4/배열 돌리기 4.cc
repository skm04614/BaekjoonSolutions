#include <stdio.h>
#include <string.h>

#define SWAP(n1, n2) {int temp = (n1); (n1) = (n2); (n2) = temp;}

typedef struct _Command {
	int r;
	int c;
	int s;
} Command;

const int DY[4] = { 0, 1, 0, -1 };
const int DX[4] = { 1, 0, -1, 0 };

int Original[51][51];
int Copy[51][51];
int NRow;
int NCol;

Command C[6];
int VC[6];
int K;

int Min = 0x7FFFFFFF;

void input(void) {
	scanf("%d %d %d", &NRow, &NCol, &K);
	for (int i = 1; i <= NRow; i++) {
		for (int j = 1; j <= NCol; j++) {
			scanf("%d", &Original[i][j]);
		}
	}

	for (int k = 0; k < K; k++) {
		scanf("%d %d %d", &C[k].r, &C[k].c, &C[k].s);
	}
}

int val(int (*board)[51]) {
	int result = 0x7FFFFFF;
	int sum;
	for (int i = 1; i <= NRow; i++) {
		sum = 0;
		for (int j = 1; j <= NCol; j++) {
			sum += board[i][j];
			if (sum >= result) {
				break;
			}
		}
		result = result < sum ? result : sum;
	}
	return result;
}

void rotate(int (*board)[51], Command c) {
	int py, px, lim, ny, nx;
	for (int lv = 1; lv <= c.s; lv++) {
		ny = py = c.r - lv;
		nx = px = c.c - lv;
		lim = 2 * lv;
		for (int d = 0; d < 4; d++) {
			lim -= (d == 3);
			for (int j = 0; j < lim; j++) {
				ny += DY[d];
				nx += DX[d];

				SWAP(board[py][px], board[ny][nx]);
			}
		}
	}
}

void DFS(int depth) {
	static int rec[6];
	if (depth == K) {
		memcpy(Copy, Original, sizeof(Original));
		for (int r = 0; r < K; r++) {
			rotate(Copy, C[rec[r]]);
		}
		int result = val(Copy);
		Min = Min < result ? Min : result;
		return;
	}

	for (int i = 0; i < K; i++) {
		if (VC[i]) {
			continue;
		}

		VC[i] = 1;
		rec[depth] = i;
		DFS(depth + 1);
		VC[i] = 0;
	}
}

int main(void) {
	input();
	DFS(0);
	printf("%d", Min);

	return 0;
}