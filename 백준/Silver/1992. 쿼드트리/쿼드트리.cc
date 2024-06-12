#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

#define SIZE 64

using namespace std;

int Map[SIZE][SIZE];
int N;

void sol(int x0, int y0, int L) {
	if (L <= 0) {
		return;
	}

	int flag = 0;
	int temp = Map[y0][x0];
	for (int y = y0; y < y0 + L; y++) {
		for (int x = x0; x < x0 + L; x++) {
			if (temp != Map[y][x]) {
				flag = 1;
				break;
			}
		}

		if (flag) {
			break;
		}
	}

	if (flag) {
		cout << "(";
		sol(x0, y0, L / 2);
		sol(x0 + L / 2, y0, L / 2);
		sol(x0, y0 + L / 2, L / 2);
		sol(x0 + L / 2, y0 + L / 2, L / 2);
		cout << ")";
	}
	else {
		cout << temp;
	}

}

int main(void) {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d", &Map[i][j]);
		}
	}
	sol(0, 0, N);

	return 0;
}