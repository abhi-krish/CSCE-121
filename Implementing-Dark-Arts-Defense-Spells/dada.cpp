/*
DADA function definitions
*/

#include "dada.h"
#include <cmath>

int amax(const double x[], const unsigned int len) {
    int temp;
    if (len == 0){
        return -1;
    }
    double maximum = abs(x[0]);
    unsigned int i;
    for (i = 0; i < len; i++){
        if (abs(x[i]) > maximum){
            maximum = abs(x[i]);
            temp = i;
        }
    }
    return temp;
}

double asum(const double x[], const unsigned int len) {
    double sum = 0;
    unsigned int i;
    for(i = 0; i < len; i++){
        sum += abs(x[i]);
    }
    return sum;
}

void axpy(const double a, const double x[], double y[], const unsigned int len) {
    unsigned int i;
    for (i = 0; i < len; i++){
        y[i] = a * x[i] + y[i];
    }
}

void copy(const double x[], double y[], const unsigned int len) {
    unsigned int i;
    for(i =0; i<len; i++){
    x[i] == y[i];
    }
}

double dot(const double x[], const double y[], const unsigned int len) {
    double total = 0;
    unsigned int i;
    for (i = 0; i < len; i++){
    total += x[i] * y[i];
    }
return total;
}

double norm2(const double x[], const unsigned int len) {
    return sqrt(dot(x,x,len));
}

void scale(const double a, double x[], const unsigned int len) {
    unsigned int i;
    for(i = 0; i < len; i++){
        x[i] = x[i] * a;
    }
}

void swap(double x[], double y[], const unsigned int len) {
    double list;
    unsigned int i;
    for( i = 0; i < len; i++){
        list = x[i];
        x[i] = y[i];
        y[i] = list;
    }
}