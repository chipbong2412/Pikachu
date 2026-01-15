#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <queue>
#include <vector>

#include "Coordinate.h"

using namespace std;

#define EASY 1
#define MEDIUM 2
#define HARD 3

// Defining the direction for path finding
enum Direction { NORTH = 0, EAST = 1, WEST = 2, SOUTH = 3, NEUTRAL = 4 };

// Abstract base class for board data and logic
class Board {
protected:
    int height;
    int width;
    int distinct_letter;

public:
    Board(int h, int w, int distinctLetters)
        : height(h), width(w), distinct_letter(distinctLetters) {}

    virtual ~Board() = default;

    // Getters
    int getHeight() const { return height; }
    int getWidth() const { return width; }
    int getDistinctLetter() const { return distinct_letter; }

    // Abstract methods
    // Initializing the 2D board
    virtual void initBoard() = 0;
    // Get the letter at the specified position
    virtual char getLetter(Coordinate pos) = 0;
    // Remove a cell at position pos
    virtual void removeCell(Coordinate pos) = 0;
    // Shuffle the board if no more valid pairs exist
    virtual void shuffleBoard() = 0;

    // Common logic methods
    // Check if a point p is in the board
    bool isInBoard(Coordinate p);
    // Check if there is no more cells on the board
    bool isBoardEmpty();
    // Check if the cell at position is valid (not removed)
    bool isValid(Coordinate pos);
    // Check if a point has been visited before
    bool isVisited(Coordinate point, vector<Coordinate> path);
    // Path finding function using bfs
    bool bfs(Coordinate start, Coordinate end, vector<Coordinate> &path);
    // Find a valid pair
    bool findValidPair(Coordinate &pos1, Coordinate &pos2);
    // Debug function, print the board into console
    void printBoard();
};

#endif