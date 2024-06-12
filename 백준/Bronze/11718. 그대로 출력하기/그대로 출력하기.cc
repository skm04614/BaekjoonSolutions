#include <iostream>
using namespace std;

char Sentence[101];

int main(void) {
	while (cin.getline(Sentence, 101)) {
		cout << Sentence << endl;
	}

	return 0;
}