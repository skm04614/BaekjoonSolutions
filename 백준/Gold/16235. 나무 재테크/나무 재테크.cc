#include <stdio.h>

#define MAX_TREES 1000
#define SWAP(a, b) {int temp = (a); (a) = (b); (b) = temp;}

typedef struct _Tile {
	int nutrition;
	int nT;
	int alive;
	int trees[MAX_TREES];
} Tile;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[8] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1} };

Tile Map[10][10];
int Add[10][10];
int Size;
int Years;

void append(int y, int x, int age) {
	Map[y][x].trees[Map[y][x].nT++] = age;
	for (int i = Map[y][x].nT - 1; i >= 1; i--) {
		if (Map[y][x].trees[i] >= Map[y][x].trees[i - 1]) {
			return;
		}
		SWAP(Map[y][x].trees[i], Map[y][x].trees[i - 1]);
	}
}

int isValidCoords(int y, int x) {
	return y >= 0 && y < Size && x >= 0 && x < Size;
}

void input(void) {
	int M;
	scanf("%d %d %d", &Size, &M, &Years);
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			scanf("%d", &Add[i][j]);
			Map[i][j].nutrition = 5;
		}
	}
	int y, x, age;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &y, &x, &age);
		append(y - 1, x - 1, age);
	}
}

void spring(void) {
	for (int y = 0; y < Size; y++) {
		for (int x = 0; x < Size; x++) {
			int idx = 0;
			while (idx < Map[y][x].nT && Map[y][x].nutrition >= Map[y][x].trees[idx]) {
				Map[y][x].nutrition -= Map[y][x].trees[idx];
				Map[y][x].trees[idx++]++;
			}
			Map[y][x].alive = idx;
		}
	}
}

void summer(void) {
	for (int y = 0; y < Size; y++) {
		for (int x = 0; x < Size; x++) {
			for (int k = Map[y][x].alive; k < Map[y][x].nT; k++) {
				Map[y][x].nutrition += Map[y][x].trees[k] / 2;
				Map[y][x].trees[k] = 0;
			}
			Map[y][x].nT = Map[y][x].alive;
		}
	}
}

void fall(void) {
	for (int y = 0; y < Size; y++) {
		for (int x = 0; x < Size; x++) {
			for (int k = 0; k < Map[y][x].nT; k++) {
				if ((Map[y][x].trees[k] % 5)) {
					continue;
				}
				for (int d = 0; d < 8; d++) {
					int ny = y + DIRS[d].dy;
					int nx = x + DIRS[d].dx;
					if (isValidCoords(ny, nx)) {
						append(ny, nx, 1);
					}
				}
			}
		}
	}
}

void winter(void) {
	for (int y = 0; y < Size; y++) {
		for (int x = 0; x < Size; x++) {
			Map[y][x].nutrition += Add[y][x];
		}
	}
}

int countTrees(void) {
	int trees = 0;
	for (int y = 0; y < Size; y++) {
		for (int x = 0; x < Size; x++) {
			trees += Map[y][x].nT;
		}
	}
	return trees;
}

int main(void) {
	//freopen("input.txt", "r", stdin);
	input();

	for (int t = 0; t < Years; t++) {
		spring();
		summer();
		fall();
		winter();
	}
	printf("%d\n", countTrees());

	return 0;
}