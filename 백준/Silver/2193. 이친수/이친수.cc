#include <iostream>

using namespace std;

long long sol(int n) {
	static long long record[2][91];

	record[0][1] = 0;
	record[1][1] = 1;

	for (int i = 2; i <= n; i++) {
		record[0][i] = record[1][i - 1] + record[0][i - 1];
		record[1][i] = record[0][i - 1];
	}

	return record[0][n] + record[1][n];
}


int main(void) {
	int n;
	cin >> n;
	cout << sol(n) << endl;

	return 0;
}