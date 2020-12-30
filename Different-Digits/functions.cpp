#include <iostream>
#include "functions.h"

bool is_valid_range(int a, int b){
    bool check;
    if (a <= b && a > 0 && b <= 10000) {
        check = true;
    }
    else {
        check = false;
    }
    return check;

}

int count_digit_occurrences(int number, int digit) {
    int counter = 0;
    while (number > 0) {
        int finaldigit = number % 10;
        if (finaldigit == digit){
            counter++;
        }
        number = number / 10;
        }
    return counter;
}

bool has_repeated_digits(int number) {
    int i;
    for(i = 0; i <= 9; i++){
        int counter = count_digit_occurrences(number, i);
        if (counter > 1) {
            bool flag = true;
            return flag;
    }
    }
    return false;

}

int count_valid_numbers(int a, int b) {
    int i;
    int nonvalidnum = 0;
    if (b < 10){
        return (b - a + 1);
    }
    for (i = a; i <= b; i++) {
        if (has_repeated_digits(i)) {
            nonvalidnum += 1;
        }
        else{
            nonvalidnum = nonvalidnum + 0;
        }
    }
    //return nonvalidnum;
    return (b - a + 1) - nonvalidnum;
    // std::cout << "There are" << (a - b + 1) - nonvalidnum << "valid numbers between" << a << "and" << b << std::endl;
}