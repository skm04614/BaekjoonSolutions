#include <stdio.h>

#define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct _Tile {
	int y;
	int x;
} Tile;

typedef struct _Union {
	Tile tiles[50 * 50];
	int n;
	int population;
} Union;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[4] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int Map[50][50];
int VisitCheck[50][50];
int Size;
int Lower, Upper;
int Time;
Union Uni;

void input(void) {
	scanf("%d %d %d", &Size, &Lower, &Upper);
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
}

void init(void) {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			VisitCheck[i][j] = 0;
		}
	}
}

int isOutOfBound(int y, int x) {
	return (y < 0) || (y >= Size) || (x < 0) || (x >= Size);
}

int FF(int y, int x) {
	if (VisitCheck[y][x] == 1 || isOutOfBound(y, x)) {
		return 0;
	}

	VisitCheck[y][x] = 1;
	Uni.tiles[Uni.n].y = y;
	Uni.tiles[Uni.n].x = x;
	Uni.n++;
	Uni.population += Map[y][x];
	int cnt = 1;
	for (int i = 0; i < 4; i++) {
		int ny = y + DIRS[i].dy;
		int nx = x + DIRS[i].dx;
		int diff = Map[y][x] - Map[ny][nx];
		if (ABS(diff) >= Lower && ABS(diff) <= Upper) {
			cnt += FF(y + DIRS[i].dy, x + DIRS[i].dx);
		}
	}
	return cnt;
}

void reallocate(void) {
	for (int i = 0; i < Uni.n; i++) {
		Map[Uni.tiles[i].y][Uni.tiles[i].x] = Uni.population / Uni.n;
	}
}

int main(void) {
	input();
	int isOver;
	for (;; Time++) {
		init();
		isOver = 1;
		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++) {
				if (FF(i, j) > 1) {
					reallocate();
					isOver = 0;
				}
				Uni.n = Uni.population = 0;
			}
		}

		if (isOver) {
			break;
		}
	}

	printf("%d", Time);

	return 0;
}