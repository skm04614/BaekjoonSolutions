#include <iostream>
using namespace std;

int fibonacci(int n) {
	static int fibo[41] = { 0, 1, 1 };
	if (n && !fibo[n]) {
		fibo[n] = fibonacci(n - 1) + fibonacci(n - 2);
	}

	return fibo[n];
}

int main(void) {
	int tc, n;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		cin >> n;
		if (!n) {
			cout << "1 0" << endl;
		}
		else {
			cout << fibonacci(n - 1) << ' ' << fibonacci(n) << endl;
		}
	}
	
	return 0;
}