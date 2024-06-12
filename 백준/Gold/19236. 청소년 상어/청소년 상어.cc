#include <stdio.h>

#define SWAP_FISH(f1, f2) {Fish temp = (f1); (f1) = (f2); (f2) = temp;}

typedef struct _Fish {
	int id;
	int dir;
} Fish;

typedef struct _Shark {
	int y;
	int x;
	int dir;
	int size;
} Shark;

typedef struct _Map {
	Fish f[4][4];
} Map;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[9] = { {0, 0}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1} };

Map M;
int Max;

int isOutOfBound(int y, int x) {
	return y < 0 || y >= 4 || x < 0 || x >= 4;
}

int devour(Map *m, Shark *ps, int y, int x) {
	if (m->f[y][x].id == 0 && m->f[y][x].dir == 0) {
		return 0;
	}

	ps->y = y;
	ps->x = x;
	ps->dir = m->f[y][x].dir;
	ps->size += m->f[y][x].id;
	m->f[y][x].id = m->f[y][x].dir = 0;
	return 1;
}

void moveFish(Map *m, Shark *ps, int id) {
	int ny, nx;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (m->f[y][x].id == id) {
				ny = y + DIRS[m->f[y][x].dir].dy;
				nx = x + DIRS[m->f[y][x].dir].dx;
				while ((ny == ps->y && nx == ps->x) || isOutOfBound(ny, nx)) {
					m->f[y][x].dir = 1 + (m->f[y][x].dir % 8);
					ny = y + DIRS[m->f[y][x].dir].dy;
					nx = x + DIRS[m->f[y][x].dir].dx;
				}
				SWAP_FISH(m->f[y][x], m->f[ny][nx]);
				return;
			}
		}
	}
}

void move(Map *m, Shark *ps) {
	for (int id = 1; id <= 16; id++) {
		moveFish(m, ps, id);
	}
}

void input(void) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			scanf("%d %d", &M.f[i][j].id, &M.f[i][j].dir);
		}
	}
}

void DFS(Shark s, Map m) {
	Max = Max > s.size ? Max : s.size;

	Shark ts;
	Map tm;
	for (int i = 1; i <= 3; i++) {
		ts = s;
		tm = m;
		move(&tm, &ts);
		int ny = ts.y + i * DIRS[ts.dir].dy;
		int nx = ts.x + i * DIRS[ts.dir].dx;
		if (isOutOfBound(ny, nx) || tm.f[ny][nx].id == 0) {
			continue;
		}
		devour(&tm, &ts, ny, nx);

		DFS(ts, tm);
	}
}

int main(void) {
	input();
	Shark s = { 0, 0 };
	devour(&M, &s, 0, 0);
	DFS(s, M);
	printf("%d", Max);

	return 0;
}