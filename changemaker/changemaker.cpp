#include <iostream>
using namespace std;
int main(){
    int cents;
    int dollars;
    int totalcents;
    int quarters;
    int remainingcents1;
    int dimes;
    int nickels;
    int pennies;
    int totalcoins;
    cout << "Enter dollars: ";
    cin >> dollars;
    cout << "Enter cents: ";
    cin >> cents;
    totalcents = (dollars * 100) + cents;
    quarters = totalcents / 25;
    remainingcents1 = totalcents % 25;
    dimes = remainingcents1 / 10;
    remainingcents1 = remainingcents1 % 10;
    nickels = remainingcents1 / 5;
    remainingcents1 = remainingcents1 % 5;
    pennies = remainingcents1;
    totalcoins = pennies + nickels + dimes + quarters;
    cout << "Pennies: " << pennies << endl;
    cout << "Nickels: " << nickels << endl;
    cout << "Dimes: " << dimes << endl;
    cout << "Quarters: " << quarters << endl << endl;
    cout << "Total coins used: " << totalcoins << endl;
return 0;
}
