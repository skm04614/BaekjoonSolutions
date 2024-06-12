#include <stdio.h>

#define WHITE	0
#define RED		1
#define BLUE	2

typedef struct _Tile {
	int c;
	int h;
	int pile[10];
} Tile;

typedef struct _Horse {
	int y;
	int x;
	int dir;
	int idx;
} Horse;

const int DY[5] = { 0, 0, 0, -1, 1 };
const int DX[5] = { 0, 1, -1, 0, 0 };
const int REV_DIR[5] = { 0, 2, 1, 4, 3 };

Tile Map[13][13];
int N;
Horse H[11];
int K;

void input(void) {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &Map[i][j].c);
		}
	}

	int y, x;
	for (int k = 1; k <= K; k++) {
		scanf("%d %d %d", &y, &x, &H[k].dir);
		H[k].y = y;
		H[k].x = x;
		H[k].idx = 0;
		Map[y][x].pile[0] = k;
		Map[y][x].h = 1;
	}
}

int isOutOfBound(int y, int x) {
	return y <= 0 || y > N || x <= 0 || x > N;
}

int move(int k) {
	int y = H[k].y;
	int x = H[k].x;
	int dir = H[k].dir;
	int ny = y + DY[dir];
	int nx = x + DX[dir];
	int lower = H[k].idx;
	int upper = Map[y][x].h;
	int nh;
	int ktemp;

	if (isOutOfBound(ny, nx) || Map[ny][nx].c == BLUE) {
		H[k].dir = dir = REV_DIR[dir];
		ny = y + DY[dir];
		nx = x + DX[dir];
		if (isOutOfBound(ny, nx) || Map[ny][nx].c == BLUE) {
			return 0;
		}
	}

	nh = Map[ny][nx].h;
	if (nh + upper - lower >= 4) {
		return 1;
	}

	for (int dh = 0; dh < upper - lower; dh++) {
		if (Map[ny][nx].c == RED) {
			ktemp = Map[ny][nx].pile[nh + dh] = Map[y][x].pile[upper - 1 - dh];
			Map[y][x].pile[upper - 1 - dh] = 0;
		} else {
			ktemp = Map[ny][nx].pile[nh + dh] = Map[y][x].pile[lower + dh];
			Map[y][x].pile[lower + dh] = 0;
		}
		H[ktemp].y = ny;
		H[ktemp].x = nx;
		H[ktemp].idx = nh + dh;
	}
	Map[y][x].h -= (upper - lower);
	Map[ny][nx].h += (upper - lower);
	return 0;
}

int sol(void) {
	for (int t = 1; t <= 1000; t++) {
		for (int k = 1; k <= K; k++) {
			if (move(k)) {
				return t;
			}
		}
	}
	return -1;
}

int main(void) {
	input();
	printf("%d", sol());

	return 0;
}