#include <iostream>
#include "money.h"

using namespace std;

int main() {
    Money empt;
    cout << empt << "There is must be nothing!" << endl;

    Money a(5, 4);
    cout << a << endl;
    string str1;
    string str2;
    while (true) {
        cin >> str1;
        cin >> str2;
        Money a = str1;
        Money b = str2;
        cout << a << " and " << b << ": += " << (a + b) << " -= " << (a - b) << endl;
        break;
    }
    // Money b = {1,5,9};
    // Money c = {4,3,8};
    
    // Money d = string("99");
    // Money f = string("2");
    // cout << d << endl;
    // cout << f << endl;
    // cout << d - f << endl;
    // cout << d + f << endl;

    return 0;
}