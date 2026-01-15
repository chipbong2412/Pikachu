#include "LinkedBoard.h"

#include <iostream>

using namespace std;

LinkedBoard::LinkedBoard(int h, int w, int distinctLetters)
    : Board(h, w, distinctLetters) {
    // Allocate linked list
    List temp;
    for (int i = 0; i < height + 2; i++) {
        list_board.addHead(temp);
    }

    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j < width + 2; j++) {
            list_board[i].addHead('#');
        }
    }
}

LinkedBoard::~LinkedBoard() {
    for (int i = 0; i < height + 2; i++) {
        list_board[i].del();
    }
    list_board.del();
}

void LinkedBoard::initBoard() {
    srand(time(NULL) + rand());
    vector<char> remaining_char;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (i <= height / 2) {
                char temp = rand() % distinct_letter + 65;
                list_board[i][j] = temp;
                remaining_char.push_back(temp);
            } else {
                int n = remaining_char.size();
                int index = rand() % n;
                list_board[i][j] = remaining_char[index];
                remaining_char.erase(remaining_char.begin() + index);
            }
        }
    }
}

char LinkedBoard::getLetter(Coordinate pos) { return list_board[pos.y][pos.x]; }

void LinkedBoard::removeCell(Coordinate pos) {
    list_board[pos.y].remove(pos.x);
}

void LinkedBoard::shuffleBoard() {
    Coordinate pos1, pos2;
    srand(time(0) + rand());

    while (!findValidPair(pos1, pos2)) {
        for (int n = 0; n < height * width; n++) {
            int i = rand() % height + 1;
            int j = rand() % width + 1;
            int k = rand() % height + 1;
            int l = rand() % width + 1;

            if (isValid({j, i}) && isValid({l, k})) {
                swap(list_board[i][j], list_board[k][l]);
            }
        }
    }
}