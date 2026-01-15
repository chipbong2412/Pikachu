#ifndef LINKEDBOARD_H
#define LINKEDBOARD_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "2DLinkedList.h"
#include "Board.h"

class LinkedBoard : public Board {
private:
    List2D list_board;

public:
    LinkedBoard(int h, int w, int distinctLetters);
    ~LinkedBoard();

    // Initializing the linked list board
    void initBoard() override;
    // Get the letter from the linked list board
    char getLetter(Coordinate pos) override;
    // Remove a cell from the linked list board
    void removeCell(Coordinate pos) override;
    // Shuffle the linked list board
    void shuffleBoard() override;
};

#endif