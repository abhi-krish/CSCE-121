#include <iostream>
#include "provided.h"
#include "functions.h"

using std::cout; using std::cin; using std::endl; using std::getline;

int main(){
    int ngames;
    int duration;
    string FileTitle;
    string FilePrefs;
    string FilePlan;
    cout << "Please enter the number of games and the duration:";
    cin >> ngames;
    cin >> duration;
    if (!(ngames <= 200 && ngames > 0 && duration <= 365 && duration > 0)){
        cout << " Invalid input." << endl;
        return 0;
    }
    else{
    cout << " Please enter name of file with titles:";
    cin >> FileTitle;
    cout << " Please enter name of file with preferences:";
    cin >> FilePrefs;
    cout << " Please enter name of file with plan:";
    cin >> FilePlan;
    string gameTitles[MAX_NB_GAMES];
    int prefs[MAX_NB_GAMES];
    int plan[366];
    if ( FileTitle != "titles.txt"){
        cout << " Invalid titles file." << endl;
    }
    else{
        try{

        readPrefs(FilePrefs, ngames, prefs);
        readPlan(FilePlan, plan);
        readGameTitles(FileTitle, ngames, gameTitles);
        int start = findBestVacation(duration, prefs, plan);
        cout << " Best start day is " << start << endl;
        cout << "Games to be played:" << endl;
        printGamesPlayedInVacation(start, duration, plan, gameTitles, ngames);
        }
        catch (std::runtime_error& runtimeError){
            cout << runtimeError.what() << endl;
        }
        catch(std::invalid_argument& invalidArgument){
            cout << invalidArgument.what() << endl;
        }
    }
}
return 0;
}