#include <stdio.h>

#define SWAP(x, y) {Number temp = (x); (x) = (y); (y) = temp;}

typedef struct _Number {
	int val;
	int occurrences;
} Number;

int arr[200][200];
int NRow, NCol;
int R, C, Target;
Number Numbers[201];

void input(void) {
	scanf("%d %d %d", &R, &C, &Target);
	R--;
	C--;
	NRow = NCol = 3;
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
}

void clearNumbers(void) {
	for (int i = 0; i <= 200; i++) {
		Numbers[i].val = Numbers[i].occurrences = 0;
	}
}

int cmpNumber(Number n1, Number n2) {
	if (!n1.val && !n2.val) {
		return 0;
	}

	if (!n1.val) {
		return 1;
	}

	if (!n2.val) {
		return -1;
	}

	if (n1.occurrences != n2.occurrences) {
		return n1.occurrences - n2.occurrences;
	}

	return n1.val - n2.val;
}

void quickSort(Number *p, int lower, int upper) {
	if (lower >= upper) {
		return;
	}

	int target = lower;
	for (int left = lower; left < upper; left++) {
		if (cmpNumber(p[left], p[upper]) < 0) {
			SWAP(p[target], p[left]);
			target++;
		}
	}
	SWAP(p[target], p[upper]);

	quickSort(p, lower, target - 1);
	quickSort(p, target + 1, upper);
}

int sortRow(int r) {
	clearNumbers();
	int unqCounts = 0;
	for (int val, j = 0; j < NCol; j++) {
		val = arr[r][j];
		if (val && !Numbers[val].occurrences) {
			unqCounts++;
		}
		Numbers[val].val = val;
		Numbers[val].occurrences++;
	}
	unqCounts = unqCounts > 50 ? 50 : unqCounts;

	quickSort(Numbers, 0, 200);
	for (int j = 0; j < unqCounts; j++) {
		arr[r][2 * j] = Numbers[j].val;
		arr[r][2 * j + 1] = Numbers[j].occurrences;
	}
	for (int j = 2 * unqCounts; j < NCol; j++) {
		arr[r][j] = 0;
	}
	return unqCounts;
}

int sortCol(int c) {
	clearNumbers();
	int unqCounts = 0;
	for (int val, i = 0; i < NRow; i++) {
		val = arr[i][c];
		if (val && !Numbers[val].occurrences) {
			unqCounts++;
		}
		Numbers[val].val = val;
		Numbers[val].occurrences++;
	}
	unqCounts = unqCounts > 50 ? 50 : unqCounts;

	quickSort(Numbers, 0, 200);
	for (int i = 0; i < unqCounts; i++) {
		arr[2 * i][c] = Numbers[i].val;
		arr[2 * i + 1][c] = Numbers[i].occurrences;
	}
	for (int i = 2 * unqCounts; i < NRow; i++) {
		arr[i][c] = 0;
	}
	return unqCounts;
}

void rOP(void) {
	int result = 1;
	for (int r = 0; r < NRow; r++) {
		int temp = sortRow(r);
		result = result > temp ? result : temp;
	}
	NCol = 2 * result;
}

void cOP(void) {
	int result = 1;
	for (int c = 0; c < NCol; c++) {
		int temp = sortCol(c);
		result = result > temp ? result : temp;
	}
	NRow = 2 * result;
}

int main(void) {
	input();
	int time;
	for (time = 0; time <= 100; time++) {
		if (arr[R][C] == Target) {
			break;
		}

		if (NRow >= NCol) {
			rOP();
		}
		else {
			cOP();
		}
	}

	if (time > 100) {
		printf("-1");
	}
	else {
		printf("%d", time);
	}

	return 0;
}
