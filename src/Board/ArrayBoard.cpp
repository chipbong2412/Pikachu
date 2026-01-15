#include "ArrayBoard.h"

#include <iostream>

using namespace std;

ArrayBoard::ArrayBoard(int h, int w, int distinctLetters)
    : Board(h, w, distinctLetters) {
    // Allocate array
    letter_board = new char *[height + 2];
    for (int i = 0; i < height + 2; i++)
        letter_board[i] = new char[width + 2];

    // Initialize with '#'
    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j < width + 2; j++) {
            letter_board[i][j] = '#';
        }
    }
}

ArrayBoard::~ArrayBoard() {
    for (int i = 0; i < height + 2; i++)
        delete[] letter_board[i];
    delete[] letter_board;
}

void ArrayBoard::initBoard() {
    srand(time(0) + rand());

    vector<char> selected_chars;

    // Fill first half of the board
    for (int i = 1; i <= ceil(height / 2.0); i++) {
        for (int j = 1; j <= width; j++) {
            char temp = rand() % distinct_letter + 65;
            selected_chars.push_back(temp);
            letter_board[i][j] = temp;
            if (i == ceil(height / 2.0) && j == ceil(width / 2.0) &&
                height % 2 != 0) {
                break;
            }
        }
    }

    // Fill second half with matching pairs
    for (int i = ceil(height / 2.0); i <= height; i++) {
        if (i == ceil(height / 2.0) && height % 2 == 0)
            i++;
        for (int j = 1; j <= width; j++) {
            if (i == ceil(height / 2.0) && j == 1 && height % 2 != 0)
                j = ceil(width / 2.0) + 1;

            int n = selected_chars.size();
            int index = rand() % n;
            letter_board[i][j] = selected_chars[index];
            selected_chars.erase(selected_chars.begin() + index);
        }
    }
}

char ArrayBoard::getLetter(Coordinate pos) {
    return letter_board[pos.y][pos.x];
}

void ArrayBoard::removeCell(Coordinate pos) {
    letter_board[pos.y][pos.x] = '#';
}

void ArrayBoard::shuffleBoard() {
    Coordinate pos1, pos2;
    srand(time(0) + rand());

    while (!findValidPair(pos1, pos2)) {
        for (int n = 0; n < height * width; n++) {
            int i = rand() % height + 1;
            int j = rand() % width + 1;
            int k = rand() % height + 1;
            int l = rand() % width + 1;

            if (isValid({j, i}) && isValid({l, k})) {
                swap(letter_board[i][j], letter_board[k][l]);
            }
        }
    }
}