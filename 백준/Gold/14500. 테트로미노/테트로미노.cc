#include <stdio.h>

typedef struct _Tile {
	int y;
	int x;
} Tile;

typedef struct _Tetromino {
	Tile tiles[4];
} Tetromino;

Tile tiles[4] = { {0, 0}, {0, 1}, {0, 2}, {0, 3} };

const Tile Pieces[19][4] = {
	{{0, 0}, {0, 1}, {1, 0}, {1, 1}},
	{{0, 0}, {0, 1}, {0, 2}, {0, 3}}, {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
	{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, {{0, 0}, {0, 1}, {-1, 1}, {-1, 2}},
	{{0, 0}, {-1, 0}, {-1, 1}, {-2, 1}}, {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
	{{0, 0}, {1, 0}, {2, 0}, {2, 1}}, {{0, 0}, {0, 1}, {0, 2}, {1, 0}},
	{{0, 0}, {0, 1}, {1, 1}, {2, 1}}, {{0, 0}, {0, 1}, {0, 2}, {-1, 2}},
	{{0, 0}, {0, 1}, {-1, 1}, {-2, 1}}, {{0, 0}, {0, 1}, {0, 2}, {-1, 0}},
	{{0, 0}, {0, 1}, {1, 0}, {2, 0}}, {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
	{{0, 0}, {0, 1}, {0, 2}, {-1, 1}}, {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
	{{0, 0}, {0, 1}, {-1, 0}, {1, 0}}, {{0, 0}, {0, 1}, {-1, 1}, {1, 1}}
};
	
int Map[500][500];
int NRow, NCol;

void input(void) {
	scanf("%d %d", &NRow, &NCol);
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
}

int isValidCoords(int y, int x) {
	return (y >= 0) && (y < NRow) && (x >= 0) && (x < NCol);
}

int isValidPiece(const Tile *piece, int dy, int dx) {
	for (int i = 0; i < 4; i++) {
		if (!isValidCoords(piece[i].y + dy, piece[i].x + dx)) {
			return 0;
		}
	}
	return 1;
}

int sumOccupied(const Tile *piece, int dy, int dx) {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += Map[piece[i].y + dy][piece[i].x + dx];
	}
	return sum;
}

int sol(void) {
	int max = 0;
	int sum;
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			for (int k = 0; k < 19; k++) {
				if (isValidPiece(Pieces[k], i, j)) {
					sum = sumOccupied(Pieces[k], i, j);
					max = max > sum ? max : sum;
				}
			}
		}
	}
	return max;
}

int main(void) {
	input();
	printf("%d", sol());

	return 0;
}