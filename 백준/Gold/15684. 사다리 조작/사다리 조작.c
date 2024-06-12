#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int Map[31][11];
int NRow, NCol;
int H;

void input(void) {
	scanf("%d %d %d", &NCol, &H, &NRow);
	int a, b;
	for (int i = 0; i < H; i++) {
		scanf("%d %d", &a, &b);
		Map[a][b] = 1;
	}
}

int traverse(int x) {
	for (int y = 1; y <= NRow; y++) {
		if (Map[y][x]) {
			x++;
		}
		else if (x > 1 && Map[y][x - 1]) {
			x--;
		}
	}
	return x;
}

int isValid(void) {
	for (int x = 1; x <= NCol; x++) {
		if (x != traverse(x)) {
			return 0;
		}
	}
	return 1;
}

int DFS(int sy, int sx, int depth) {
	if (isValid()) {
		return depth;
	}

	if (depth == 3) {
		return 0x7FFFFFFF;
	}

	int min = 0x7FFFFFFF;
	int result;
	for (int y = sy; y <= NRow; y++) {
		if (y == sy) {
			for (int x = sx; x < NCol; x++) {
				if (Map[y][x] == 1) {
					continue;
				}
				Map[y][x] = 1;
				result = DFS(y, x + 1, depth + 1);
				min = MIN(min, result);
				Map[y][x] = 0;
			}
		}
		else {
			for (int x = 1; x < NCol; x++) {
				if (Map[y][x] == 1) {
					continue;
				}
				Map[y][x] = 1;
				result = DFS(y, x + 1, depth + 1);
				min = MIN(min, result);
				Map[y][x] = 0;
			}
		}
	}
	return min;
}

int main(void) {
	input();
	int result = DFS(1, 1, 0);
	printf("%d", result <= 3 ? result : -1);

	return 0;
}