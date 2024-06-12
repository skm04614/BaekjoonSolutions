#include <iostream>

using namespace std;

int sol(int n) {
	static int record[2][10];

	for (int i = 0; i < 10; i++) {
		record[1][i] = 1;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < 10; j++) {
			record[i % 2][j] = 0;
			for (int k = 0; k <= j; k++) {
				record[i % 2][j] += record[(i - 1) % 2][k];
			}
			record[i % 2][j] %= 10007;
		}
	}

	int result = 0;
	for (int i = 0; i < 10; i++) {
		result += record[n % 2][i];
	}
	result %= 10007;

	return result;
}


int main(void) {
	int n;
	cin >> n;
    cout << sol(n) << endl;

	return 0;
}