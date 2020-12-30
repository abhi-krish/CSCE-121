#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "functions.h"

using std::runtime_error;  using std::getline; using std::string; using std::ifstream; using std::invalid_argument; using std::endl; using std::cout;

void readPrefs(string fileName, int ngames, int prefs[]){
    ifstream inFS;
    int dayNum;
    int rating;
    inFS.open(fileName);
    if (!inFS.is_open()){
        throw runtime_error("Invalid preferences file.");
    }
    for (int i = 0; i < ngames; i++){
        prefs[i] = 0;
    }
    if (inFS.is_open()){
        while(!inFS.eof()){
            inFS >> dayNum;
            if (inFS.good()){
                //cout << "prefs: " << prefs[9];
                if (dayNum > 0 && dayNum <= ngames){
                    inFS >> rating;
                    //cout << "prefs: " << prefs[7];
                    if(inFS.good()){
                        if (rating >= 0 && rating < 6){
                            //cout << "prefs: " << prefs[7];
                            prefs[dayNum] = rating;
                            //cout << "prefs: " << prefs[98];
                        }
                    }
                }
            }
        }
        //cout << "prefs" << prefs[98];
    }
    inFS.close();
}
            
void readPlan(string fileName, int plan[]){
    ifstream inFS;
    inFS.open(fileName);
    if (!inFS.is_open()){
         throw runtime_error("Invalid plan file.");
    }
    int day;
    int gameNum;
    while (!inFS.eof()){
        inFS >> day;
        if (inFS.good()){
            if (day > 0 && day <= 365){
                inFS >> gameNum;
                plan[day] = gameNum;
            }
            else{
                inFS >> gameNum;
            }
        }
        else{
            inFS >> gameNum;
        }
    }
    inFS.close();
    
}

int computeFunLevel(int start, int duration, int prefs[], int plan[]){
    int sum = 0;
    if ((start + duration) > 366){
        throw invalid_argument("Invalid Argument");
    }
    for (int i = start; i <= (start + duration - 1); i++){
        int game = plan[i];
        int rating = prefs[game];
        sum += rating;
        }
    return sum;
}

int findBestVacation(int duration, int prefs[], int plan[]){
    if (duration > 365){
        throw invalid_argument("Invalid Argument");
    }
    int max = 0;
    int location;
    for (int start = 1; start <= 366 - duration; start++){
        int newmax = computeFunLevel(start, duration, prefs, plan);
        if (newmax > max){
            max = newmax;
            location = start;
        }
    }
    return location;
}