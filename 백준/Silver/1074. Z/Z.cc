#include <iostream>

using namespace std;

void sol(int &result, int x, int y, int x0, int y0, int L) {
	if (L == 1) {
		return;
	}
	int xm = x0 + L / 2;
	int ym = y0 + L / 2;

	int inc = L * L / 4;
	if (y < ym) {
		if (x < xm) {
			sol(result, x, y, x0, y0, L / 2);
		}
		else {
			result += inc;
			sol(result, x, y, xm, y0, L / 2);
		}
	}
	else {
		if (x < xm) {
			result += 2 * inc;
			sol(result, x, y, x0, ym, L / 2);
		}
		else {
			result += 3 * inc;
			sol(result, x, y, xm, ym, L / 2);
		}
	}
}

int main(void) {
	int result = 0;
	int n, x, y;
	cin >> n >> y >> x;
	sol(result, x, y, 0, 0, 1u << n);
	cout << result;

	return 0;
}