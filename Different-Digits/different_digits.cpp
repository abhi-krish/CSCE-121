#include <iostream>
#include "functions.h"

using std::endl; using std::cout; using std::cin;

int main() {
int a;
int b;
cout << "Enter numbers 0 < a <= b <= 10000: ";
cin >> a;
cin >> b;

if (is_valid_range(a, b)) {
    cout << "There are " << count_valid_numbers(a,b) << " valid numbers between " << a << " and " << b << endl;

}
else {
    cout << "Invalid input" << endl;
}
return 0;
}