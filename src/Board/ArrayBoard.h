#ifndef ARRAYBOARD_H
#define ARRAYBOARD_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Board.h"

class ArrayBoard : public Board {
private:
    char **letter_board;

public:
    ArrayBoard(int h, int w, int distinctLetters);
    ~ArrayBoard();

    // Initializing the 2D array board
    void initBoard() override;
    // Get the letter from the array board
    char getLetter(Coordinate pos) override;
    // Remove a cell from the array board
    void removeCell(Coordinate pos) override;
    // Shuffle the array board
    void shuffleBoard() override;
};

#endif