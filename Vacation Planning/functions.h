#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>


using std::string;

void readPrefs(string fileName, int ngames, int prefs[]);

void readPlan(string fileName, int plan[]);

int computeFunLevel(int start, int duration, int prefs[], int plan[]);

int findBestVacation(int duration, int prefs[], int plan[]);

#endif