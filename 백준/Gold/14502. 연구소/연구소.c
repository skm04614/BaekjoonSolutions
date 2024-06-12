#include <stdio.h>

#define MAX_SIZE 8

typedef struct _Virus {
	int y;
	int x;
} Virus;

typedef struct _Queue {
	Virus viruses[MAX_SIZE * MAX_SIZE];
	int start;
	int end;
} Queue;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

int map[MAX_SIZE][MAX_SIZE];
int test[MAX_SIZE][MAX_SIZE];
const Direction dirs[4] = { {1 ,0}, {0, 1}, {-1, 0}, {0, -1} };
Queue original, used;

void init(const int ROW, const int COL) {
	used = original;
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			test[r][c] = map[r][c];
		}
	}
}

int isEmpty(void) {
	return used.end == used.start;
}

int isValid(int r, int c, const int ROW, const int COL) {
	return (r >= 0) && (r < ROW) && (c >= 0) && (c < COL);
}

int putWall(int n, const int ROW, const int COL) {
	int r = n / COL;
	int c = n % COL;
	if (test[r][c])
		return 0;

	test[r][c] = 1;
	return 1;
}

int countSafeZone(const int ROW, const int COL) {
	int count = 0;
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			count += !test[r][c];
		}
	}
	return count;
}
#define DEBUG 0
#if DEBUG == 1
void debug(const int ROW, const int COL) {
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			printf("%d ", test[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}
#endif

int main(void) {
	int ROW, COL;
	scanf("%d %d", &ROW, &COL);
	for (int r = 0; r < ROW; r++) {
		for (int c = 0; c < COL; c++) {
			scanf("%d", &map[r][c]);
			if (map[r][c] == 2) {
				original.viruses[original.end].y = r;
				original.viruses[original.end].x = c;
				original.end++;
			}
		}
	}

	int maxCount = 0;
	for (int i = 0; i < ROW * COL; i++) {
		for (int j = i + 1; j < ROW * COL; j++) {
			for (int k = j + 1; k < ROW * COL; k++) {
				init(ROW, COL);
				int walls = putWall(i, ROW, COL) + putWall(j, ROW, COL) + putWall(k, ROW, COL);
				if (walls < 3) {
					continue;
				}
				while (!isEmpty()) {
					Virus current = used.viruses[used.start++];
					for (int j = 0; j < 4; j++) {
						int y = current.y + dirs[j].dy;
						int x = current.x + dirs[j].dx;
						if (isValid(y, x, ROW, COL) && !test[y][x]) {
							test[y][x] = 2;
							used.viruses[used.end].y = y;
							used.viruses[used.end].x = x;
							used.end++;
						}
					}
				}
				#if DEBUG == 1
					debug(ROW, COL);
				#endif

				int count = countSafeZone(ROW, COL);
				maxCount = maxCount > count ? maxCount : count;
			}
		}
	}

	printf("%d", maxCount);

	return 0;
}