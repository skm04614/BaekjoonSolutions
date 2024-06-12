#include <stdio.h>

#define WALL 1
#define VISITED 2

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

int Map[50][50];
int NRow, NCol;
int SY, SX, SD;

void input(void) {
	scanf("%d %d", &NRow, &NCol);
	scanf("%d %d %d", &SY, &SX, &SD);
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
}

int FF(int y, int x, int d) {
	if (Map[y][x] == WALL) {
		return 0;
	}

	int cnt = (Map[y][x] == 0);
	Map[y][x] = VISITED;
	for (int temp, i = 0; i < 4; i++) {
		d = (d + 4 - 1) % 4;
		int ny = y + DIRS[d].dy;
		int nx = x + DIRS[d].dx;
		if (!Map[ny][nx]) {
			return cnt + FF(ny, nx, d);
		}
	}
	
	return cnt + FF(y - DIRS[d].dy, x - DIRS[d].dx, d);
}

int main(void) {
	input();

	printf("%d", FF(SY, SX, SD));

	return 0;
}