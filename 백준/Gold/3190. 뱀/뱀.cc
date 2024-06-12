#include <stdio.h>

#define FRUIT 1
#define OCCUPIED 2
#define TAIL 9999

typedef struct _Tile {
	int y;
	int x;
} Tile;

typedef struct _Obj {
	Tile body[100 * 100];
	int d;
	int hIdx;
} Obj;

typedef struct _Command {
	int t;
	int change;
} Command;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int Map[101][101];
int Size;
Command Commands[100];
Obj Snake;
int NCom;

void input(void) {
	scanf("%d", &Size);
	int nFruit, y, x;
	scanf("%d", &nFruit);
	for (int i = 0; i < nFruit; i++) {
		scanf("%d %d", &y, &x);
		Map[y][x] = FRUIT;
	}
	scanf("%d", &NCom);
	int t;
	char com;
	for (int i = 0; i < NCom; i++) {
		scanf("%d %c", &t, &com);
		Commands[i].t = t;
		Commands[i].change = (com == 'D') ? 1 : 3;
	}

	Snake.hIdx = TAIL;
	Snake.body[TAIL].y = Snake.body[TAIL].x = 1;
	Map[1][1] = OCCUPIED;
	Snake.d = 0;
}

int isOutOfBound(int y, int x) {
	return y <= 0 || y > Size || x <= 0 || x > Size;
}

int move(void) {
	int ny = Snake.body[Snake.hIdx].y + DIRS[Snake.d].dy;
	int nx = Snake.body[Snake.hIdx].x + DIRS[Snake.d].dx;

	if (isOutOfBound(ny, nx) || Map[ny][nx] == OCCUPIED) {
		return 0;
	}

	if (Map[ny][nx] == FRUIT) {
		Snake.hIdx--;
		Snake.body[Snake.hIdx].y = ny;
		Snake.body[Snake.hIdx].x = nx;
	}
	else {
		Map[Snake.body[TAIL].y][Snake.body[TAIL].x] = 0;
		for (int i = TAIL; i > Snake.hIdx; i--) {
			Snake.body[i] = Snake.body[i - 1];
		}
		Snake.body[Snake.hIdx].y = ny;
		Snake.body[Snake.hIdx].x = nx;
	}
	Map[ny][nx] = OCCUPIED;
	return 1;
}

int main(void) {
	input();
	int t = 0;
	int nextCom = 0;
	for (;; t++) {
		if (nextCom < NCom && t == Commands[nextCom].t) {
			Snake.d = (Snake.d + Commands[nextCom].change) % 4;
			nextCom++;
		}

		if (!move()) {
			break;
		}
	}

	printf("%d", t + 1);

	return 0;
}
