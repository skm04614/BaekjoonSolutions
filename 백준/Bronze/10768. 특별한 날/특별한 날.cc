#include <iostream>
using namespace std;

int main(void) {
    int month, date;
    cin >> month >> date;
    
    if (month == 2 && date == 18) {
        cout << "Special";
    } else if (month > 2 || (month == 2 && date > 18)) {
        cout << "After";
    } else {
        cout << "Before";
    }
    
    return 0;
}