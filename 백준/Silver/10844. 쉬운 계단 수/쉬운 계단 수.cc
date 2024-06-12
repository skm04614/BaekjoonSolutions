#include <iostream>

using namespace std;

int sol(int N) {
	static int arr[2][10];
	const static int suppress = 1000000000;

	arr[1][0] = 0;
	for (int i = 1; i < 10; i++) {
		arr[1][i] = 1;
	}

	for (int ntmp = 2; ntmp <= N; ntmp++) {
		for (int i = 0; i < 10; i++) {
			arr[ntmp % 2][i] = ((i != 0) * arr[(ntmp - 1) % 2][i - 1] \
				+ (i != 9) * arr[(ntmp - 1) % 2][i + 1]) % suppress;
		}
	}

	int result = 0;
	for (int j = 0; j < 10; j++) {
		result += arr[N % 2][j];
		result %= suppress;
	}
	return result;
}


int main(void) {
	int n;
	cin >> n;
	cout << sol(n);

	return 0;
}