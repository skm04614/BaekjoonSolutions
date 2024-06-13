#include <stdio.h>

int Map[21][21];
int Sector[21][21];
int N;

void input(void) {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
}

void updateSectors(int y, int x, int d1, int d2) {
	int flag = 0;
	int xl = x + d1;
	int xr = x + d1;
	for (int r = 1; r <= N; r++) {
		if (r == y - d1) {
			flag = 1;
		}

		for (int c = 1; c <= N; c++) {
			if (flag && xl <= c && c <= xr) {
				Sector[r][c] = 5;
			}
			else if (1 <= r && r < y && 1 <= c && c <= x + d1) {
				Sector[r][c] = 1;
			}
			else if (1 <= r && r <= y - d1 + d2 && x + d1 < c && c <= N) {
				Sector[r][c] = 2;
			}
			else if (y <= r && r <= N && 1 <= c && c < x + d2) {
				Sector[r][c] = 3;
			}
			else {
				Sector[r][c] = 4;
			}
		}

		if (flag) {
			if (r < y) {
				xl--;
			}
			else {
				xl++;
			}

			if (r < y - d1 + d2) {
				xr++;
			}
			else {
				xr--;
			}
		}
	}
}

int popDiff(void) {
	static int population[6];
	for (int s = 1; s <= 5; s++) {
		population[s] = 0;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			population[Sector[i][j]] += Map[i][j];
		}
	}

	int min = 0x7FFFFFFF;
	int max = 0x80000000;
	for (int s = 1; s <= 5; s++) {
		min = min < population[s] ? min : population[s];
		max = max > population[s] ? max : population[s];
	}
	return max - min;
}

//d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N
int sol(void) {
	int min = 0x7FFFFFFF;
	int result;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			for (int d1 = 1; d1 <= N - 1; d1++) {
				for (int d2 = 1; d2 <= N - 1; d2++) {
					if (y - d1 < 1 || y + d2 > N || x + d1 + d2 > N) {
						continue;
					}
					updateSectors(y, x, d1, d2);
					result = popDiff();
					if (min > result) {
						min = result;
					}
				}
			}
		}
	}

	return min;
}

int main(void) {
	input();
	printf("%d", sol());

	return 0;
}