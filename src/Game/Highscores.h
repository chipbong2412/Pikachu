#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>

#include "Result.h"
using namespace std;

// define the Highscores class to store the highest results
class Highscores {
private:
    vector<Result> records; // list of top highscorer

public:
    // Load the highscores from the file
    void loadHighscores();
    // Update the highscores according to the record
    void updateHighscores(Result record);
    // Display the highscores on the board
    void displayHighscores();
};

#endif