#include <stdio.h>

typedef struct _Rotation {
	int x;
	int d;
	int k;
} Rotation;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int Plates[51][50];
int VC[51][50];
int N, M;
Rotation Rot[50];
int T;
int Cnt;

void input(void) {
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &Plates[i][j]);
		}
	}
	for (int i = 0; i < T; i++) {
		scanf("%d %d %d", &Rot[i].x, &Rot[i].d, &Rot[i].k);
	}
	Cnt = N * M;
}

void rotate(int *p, int size, int dir, int step) {
	int temp;
	if (!dir) {
		for (int k = 0; k < step; k++) {
			temp = p[size - 1];
			for (int i = size - 1; i > 0; i--) {
				p[i] = p[i - 1];
			}
			p[0] = temp;
		}
	}
	else {
		for (int k = 0; k < step; k++) {
			temp = p[0];
			for (int i = 0; i < size - 1; i++) {
				p[i] = p[i + 1];
			}
			p[size - 1] = temp;
		}
	}
}

int isOutOfBound(int y, int x) {
	return y < 1 || y > N;
}

int isValidOrigin(int y, int x) {
	for (int i = 0; i < 4; i++) {
		int ny = y + DIRS[i].dy;
		int nx = (x + M + DIRS[i].dx) % M;

		if (isOutOfBound(ny, nx)) {
			continue;
		}

		if (Plates[ny][nx] == Plates[y][x]) {
			return 1;
		}
	}

	return 0;
}

void FF(int y, int x, int val, int isOrigin) {
	if (isOutOfBound(y, x) || VC[y][x] == 1 || Plates[y][x] != val) {
		return;
	}

	VC[y][x] = 1;

	if (isOrigin && !isValidOrigin(y, x)) {
		return;
	}

	Plates[y][x] = 0;
	for (int i = 0; i < 4; i++) {
		FF(y + DIRS[i].dy, (x + M + DIRS[i].dx) % M, val, 0);
	}
}

void update(void) {
	int temp = 0;
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			temp += (Plates[i][j] > 0);
			sum += Plates[i][j];
		}
	}

	if (temp < Cnt) {
		Cnt = temp;
		return;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (Plates[i][j] == 0) {
				continue;
			}

			if (Cnt * Plates[i][j] > sum) {
				Plates[i][j]--;
			}
			else if (Cnt * Plates[i][j] < sum) {
				Plates[i][j]++;
			}
		}
	}

}

void initVC(void) {
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			VC[i][j] = !(Plates[i][j]);
		}
	}
}

void sol(void) {
	for (int i = 0; i < T; i++) {
		for (int j = Rot[i].x; j <= N; j += Rot[i].x) {
			rotate(Plates[j], M, Rot[i].d, Rot[i].k);
		}
		initVC();
		for (int y = 1; y <= N; y++) {
			for (int x = 0; x < M; x++) {
				FF(y, x, Plates[y][x], 1);
			}
		}
		update();
	}
}

int getSum(void) {
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			sum += Plates[i][j];
		}
	}

	return sum;
}

int main(void) {
	input();
	sol();
	printf("%d", getSum());

	return 0;
}