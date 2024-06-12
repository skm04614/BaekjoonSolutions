#include <stdio.h>

#define WALL -1
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct _Tile {
	int y;
	int x;
	int c;
} Tile;

typedef struct _CCTV {
	int nRot;
	int dir[4][4];
} CCTV;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
const CCTV CCTV_TYPES[6] = {
	{0},
	{4, {{0, 0, 0, 1}, {0, 0, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0}}},
	{2, {{0, 1, 0, 1}, {1, 0, 1, 0}}},
	{4, {{0, 0, 1, 1}, {0, 1, 1, 0}, {1, 1, 0, 0}, {1, 0, 0, 1}}},
	{4, {{0, 1, 1, 1}, {1, 1, 1, 0}, {1, 1, 0, 1}, {1, 0, 1, 1}}},
	{1, {{1, 1, 1, 1}}}
};

int Map[8][8];
int NRow, NCol;
Tile CTiles[8];
int C;
int Min = 64;

void input(void) {
	scanf("%d %d", &NRow, &NCol);
	int val;
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			scanf("%d", &val);
			Map[i][j] = val == 6 ? WALL : 0;
			if (val >= 1 && val <= 5) {
				CTiles[C].y = i;
				CTiles[C].x = j;
				CTiles[C].c = val;
				C++;
			}
		}
	}
}

int isValidCoords(int y, int x) {
	return y >= 0 && y < NRow && x >= 0 && x < NCol;
}

void surveil(Tile cctv, int r, int inc) {
	CCTV ct = CCTV_TYPES[cctv.c];
	int y, x;
	for (int d = 0; d < 4; d++) {
		if (ct.dir[r][d] == 1) {
			y = cctv.y;
			x = cctv.x;
			while (isValidCoords(y, x) && Map[y][x] != WALL) {
				Map[y][x] += inc;
				y += DIRS[d].dy;
				x += DIRS[d].dx;
			}
		}
	}
}

int count(void) {
	int cnt = 0;
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			cnt += (Map[i][j] == 0);
		}
	}
	return cnt;
}

void DFS(int n) {
	if (n == C) {
		int cnt = count();
		Min = MIN(Min, cnt);
		return;
	}

	for (int r = 0; r < CCTV_TYPES[CTiles[n].c].nRot; r++) {
		surveil(CTiles[n], r, 1);
		DFS(n + 1);
		surveil(CTiles[n], r, -1);
	}
}

int main(void) {
	input();
	DFS(0);

	printf("%d", Min);

	return 0;
}