#include <stdio.h>

#define UP		0
#define DOWN	1
#define FRONT	2
#define BACK	3
#define LEFT	4
#define RIGHT	5
#define SWAP(n1, n2) {int temp = (n1); (n1) = (n2); (n2) = temp;}

const char COLORS[6] = { 'w', 'y', 'r', 'o', 'g', 'b' };

int Cube[6][3][3];
int *U[12] = {
	&Cube[FRONT][0][0], &Cube[FRONT][0][1], &Cube[FRONT][0][2],
	&Cube[RIGHT][0][0], &Cube[RIGHT][0][1], &Cube[RIGHT][0][2],
	&Cube[BACK][0][0], &Cube[BACK][0][1], &Cube[BACK][0][2],
	&Cube[LEFT][0][0], &Cube[LEFT][0][1], &Cube[LEFT][0][2]
};

int *D[12] = {
	&Cube[FRONT][2][2], &Cube[FRONT][2][1], &Cube[FRONT][2][0],
	&Cube[LEFT][2][2], &Cube[LEFT][2][1], &Cube[LEFT][2][0],
	&Cube[BACK][2][2], &Cube[BACK][2][1], &Cube[BACK][2][0],
	&Cube[RIGHT][2][2], &Cube[RIGHT][2][1], &Cube[RIGHT][2][0]
};

int *R[12] = {
	&Cube[FRONT][0][2], &Cube[FRONT][1][2], &Cube[FRONT][2][2],
	&Cube[DOWN][2][0], &Cube[DOWN][1][0], &Cube[DOWN][0][0],
	&Cube[BACK][2][0], &Cube[BACK][1][0], &Cube[BACK][0][0],
	&Cube[UP][0][2], &Cube[UP][1][2], &Cube[UP][2][2]
};

int *L[12] = {
	&Cube[FRONT][2][0], &Cube[FRONT][1][0], &Cube[FRONT][0][0],
	&Cube[UP][2][0], &Cube[UP][1][0], &Cube[UP][0][0],
	&Cube[BACK][0][2], &Cube[BACK][1][2], &Cube[BACK][2][2],
	&Cube[DOWN][0][2], &Cube[DOWN][1][2], &Cube[DOWN][2][2]
};

int *F[12] = {
	&Cube[UP][2][2], &Cube[UP][2][1], &Cube[UP][2][0],
	&Cube[LEFT][0][2], &Cube[LEFT][1][2], &Cube[LEFT][2][2],
	&Cube[DOWN][2][2], &Cube[DOWN][2][1], &Cube[DOWN][2][0],
	&Cube[RIGHT][2][0], &Cube[RIGHT][1][0], &Cube[RIGHT][0][0]
};

int *B[12] = {
	&Cube[UP][0][0], &Cube[UP][0][1], &Cube[UP][0][2],
	&Cube[RIGHT][0][2], &Cube[RIGHT][1][2], &Cube[RIGHT][2][2],
	&Cube[DOWN][0][0], &Cube[DOWN][0][1], &Cube[DOWN][0][2],
	&Cube[LEFT][2][0], &Cube[LEFT][1][0], &Cube[LEFT][0][0]
};

void initCube(void) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				Cube[i][j][k] = i;
			}
		}
	}
}

void shiftCCW(int **p) {
	int temp = *p[12 - 1];
	for (int i = 12 - 1; i > 0; i--) {
		*p[i] = *p[i - 1];
	}
	*p[0] = temp;
}

void shiftCW(int **p) {
	int temp = *p[0];
	for (int i = 0; i < 12 - 1; i++) {
		*p[i] = *p[i + 1];
	}
	*p[12 - 1] = temp;
}

void rotateSideCCW(int(*p)[3]) {
	for (int i = 0; i < 3 / 2; i++) {
		for (int j = 0; j < (3 + 1) / 2; j++) {
			SWAP(p[i][j], p[3 - 1 - j][i]);
			SWAP(p[i][j], p[3 - 1 - i][3 - 1 - j]);
			SWAP(p[i][j], p[j][3 - 1 - i]);
		}
	}
}

void rotateSideCW(int(*p)[3]) {
	for (int i = 0; i < 3 / 2; i++) {
		for (int j = 0; j < (3 + 1) / 2; j++) {
			SWAP(p[i][j], p[j][3 - 1 - i]);
			SWAP(p[i][j], p[3 - 1 - i][3 - 1 - j]);
			SWAP(p[i][j], p[3 - 1 - j][i]);
		}
	}
}


void rotate(char side, char dir) {
	int (*targetSide)[3];
	int **targetRing;
	switch (side) {
	case 'L':
		targetSide = Cube[LEFT];
		targetRing = L;
		break;
	case 'R':
		targetSide = Cube[RIGHT];
		targetRing = R;
		break;
	case 'U':
		targetSide = Cube[UP];
		targetRing = U;
		break;
	case 'D':
		targetSide = Cube[DOWN];
		targetRing = D;
		break;
	case 'F':
		targetSide = Cube[FRONT];
		targetRing = F;
		break;
	case 'B':
		targetSide = Cube[BACK];
		targetRing = B;
		break;
	default:
		targetSide = NULL;
		targetRing = NULL;
	}

	if (dir == '+') {
		rotateSideCW(targetSide);
		for (int i = 0; i < 3; i++) {
			shiftCW(targetRing);
		}
	}
	else {
		rotateSideCCW(targetSide);
		for (int i = 0; i < 3; i++) {
			shiftCCW(targetRing);
		}
	}
}

void printUP(void) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%c", COLORS[Cube[UP][i][j]]);
		}
		printf("\n");
	}
}


int main(void) {
	int tc;
	scanf("%d", &tc);
	int nCom;
	char side, dir;
	for (int i = 0; i < tc; i++) {
		initCube();
		scanf("%d", &nCom);
		for (int j = 0; j < nCom; j++) {
			scanf(" %c %c", &side, &dir);
			rotate(side, dir);
		}
		printUP();
	}

	return 0;
}