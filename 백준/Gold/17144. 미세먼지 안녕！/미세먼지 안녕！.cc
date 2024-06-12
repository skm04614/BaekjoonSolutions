#include <stdio.h>

#define SWAP(a, b) {int temp = (a); (a) = (b); (b) = temp;}

typedef struct _Tile {
	int y;
	int x;
	int m;
} Tile;

typedef struct _Queue {
	Tile e[50 * 50];
	int rp;
	int wp;
} Queue;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[4] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };

int Map[50][50];
int NRow, NCol;
int T;
Tile CircTop, CircBot;
Queue Q;

int isQEmpty(void) {
	return Q.rp == Q.wp;
}

void enqueue(int y, int x, int m) {
	Q.e[Q.wp].y = y;
	Q.e[Q.wp].x = x;
	Q.e[Q.wp].m = m;
	Q.wp++;
}

Tile dequeue(void) {
	return Q.e[Q.rp++];
}

void input(void) {
	scanf("%d %d %d", &NRow, &NCol, &T);
	int val, n = 0;
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			scanf("%d", &val);
			if (val == -1) {
				Map[i][j] = 0;
				if (!n) {
					CircTop.y = i;
					CircTop.x = j;
				}
				else {
					CircBot.y = i;
					CircBot.x = j;
				}
				n++;
			}
			else {
				Map[i][j] = val;
			}
		}
	}
}

void init(void) {
	Q.rp = Q.wp = 0;
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			if (Map[i][j] > 0) {
				enqueue(i, j, Map[i][j]);
			}
		}
	}
}

int isOutOfBound(int y, int x) {
	return y < 0 || y >= NRow || x < 0 || x >= NCol;
}

void spreadTile(int y, int x, int m) {
	int ny, nx;
	int amount = m / 5;
	for (int d = 0; d < 4; d++) {
		ny = y + DIRS[d].dy;
		nx = x + DIRS[d].dx;

		if (isOutOfBound(ny, nx)) {
			continue;
		}
		if (ny == CircTop.y && nx == CircTop.x) {
			continue;
		}
		if (ny == CircBot.y && nx == CircBot.x) {
			continue;
		}
		Map[y][x] -= amount;
		Map[ny][nx] += amount;
	}
}

void spread(void) {
	while (!isQEmpty()) {
		Tile curr = dequeue();
		spreadTile(curr.y, curr.x, curr.m);
	}
}

void circulate(void) {
	int d = 0;
	int y = CircTop.y + DIRS[d].dy;
	int x = CircTop.x + DIRS[d].dx;
	while (y != CircTop.y || x != CircTop.x) {
		SWAP(Map[CircTop.y][CircTop.x], Map[y][x]);

		y += DIRS[d].dy;
		x += DIRS[d].dx;
		if (isOutOfBound(y, x)) {
			y -= DIRS[d].dy;
			x -= DIRS[d].dx;
			d = (d + 1) % 4;
			y += DIRS[d].dy;
			x += DIRS[d].dx;
		}
	}
	Map[CircTop.y][CircTop.x] = 0;

	d = 0;
	y = CircBot.y + DIRS[d].dy;
	x = CircBot.x + DIRS[d].dx;
	while (y != CircBot.y || x != CircBot.x) {
		SWAP(Map[CircBot.y][CircBot.x], Map[y][x]);

		y += DIRS[d].dy;
		x += DIRS[d].dx;
		if (isOutOfBound(y, x)) {
			y -= DIRS[d].dy;
			x -= DIRS[d].dx;
			d = (d + 4 - 1) % 4;
			y += DIRS[d].dy;
			x += DIRS[d].dx;
		}
	}
	Map[CircBot.y][CircBot.x] = 0;
}

void progress(void) {
	init();
	spread();
	circulate();
}

int count(void) {
	int cnt = 0;
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			cnt += Map[i][j];
		}
	}

	return cnt;
}

int main(void) {
	input();

	for (int t = 0; t < T; t++) {
		progress();
	}

	printf("%d", count());

	return 0;
}