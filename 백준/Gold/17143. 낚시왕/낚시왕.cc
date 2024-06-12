#include <stdio.h>

#define SWAP_SHARK(s1, s2) {Shark temp = (s1); (s1) = (s2); (s2) = temp;}

typedef struct _Shark {
	int y;
	int x;
	int speed;
	int dir;
	int size;
	int isDead;
} Shark;

typedef struct _Coords {
	int y;
	int x;
} Coords;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[5] = { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int Map[101][101];
int NRow, NCol;

Shark Sharks[10001];
int NS;

int isOutOfBound(int y, int x) {
	return y <= 0 || x <= 0 || y > NRow || x > NCol;
}

void qSort(Shark *s, int lower, int upper) {
	if (lower >= upper) {
		return;
	}

	int target = lower;
	for (int left = lower; left < upper; left++) {
		if (s[left].size > s[upper].size) {
			SWAP_SHARK(s[left], s[target]);
			target++;
		}
	}

	SWAP_SHARK(s[target], s[upper]);

	qSort(s, lower, target - 1);
	qSort(s, target + 1, upper);
}

int changeDir(int dir) {
	switch (dir) {
	case 1:
		return 2;
	case 2:
		return 1;
	case 3:
		return 4;
	case 4:
		return 3;
	default:
		return 0;
	}
}

void init(void) {
	scanf("%d %d %d", &NRow, &NCol, &NS);
	for (int id = 1; id <= NS; id++) {
		scanf("%d", &Sharks[id].y);
		scanf("%d", &Sharks[id].x);
		scanf("%d", &Sharks[id].speed);
		scanf("%d", &Sharks[id].dir);
		scanf("%d", &Sharks[id].size);
	}

	qSort(Sharks, 1, NS);
	for (int id = 1; id <= NS; id++) {
		Map[Sharks[id].y][Sharks[id].x] = id;
	}
}

int adjust(int coord, int lim) {
	if (coord <= 0) {
		return 2 - coord;
	}
	else if (coord > lim) {
		return 2 * lim - coord;
	}

	return coord;
}

void moveShark(int id) {
	if (Sharks[id].isDead) {
		return;
	}

	int y = Sharks[id].y;
	int x = Sharks[id].x;
	int d = Sharks[id].dir;
	int v = Sharks[id].speed;
	Map[y][x] = 0;


	y += v % (2 * (NRow - 1)) * DIRS[d].dy;
	x += v % (2 * (NCol - 1)) * DIRS[d].dx;

	while (isOutOfBound(y, x)) {
		d = changeDir(d);
		y = adjust(y, NRow);
		x = adjust(x, NCol);
	}

	Sharks[id].y = y;
	Sharks[id].x = x;
	Sharks[id].dir = d;
}

int hunt(int x) {
	for (int y = 1; y <= NRow; y++) {
		if (Map[y][x]) {
			int id = Map[y][x];
			Map[y][x] = 0;
			Sharks[id].isDead = 1;
			return Sharks[id].size;
		}
	}
	return 0;
}

int sol(void) {
	int total = 0;
	for (int x = 1; x <= NCol; x++) {
		total += hunt(x);
		for (int id = 1; id <= NS; id++) {
			moveShark(id);
		}
		for (int id = 1; id <= NS; id++) {
			if (Sharks[id].isDead) {
				continue;
			}

			if (Map[Sharks[id].y][Sharks[id].x]) {
				Sharks[id].isDead = 1;
				continue;
			}
			Map[Sharks[id].y][Sharks[id].x] = id;
		}
	}

	return total;
}

int main(void) {
	init();
	printf("%d", sol());

	return 0;
}