#include "BoardRenderer.h"

#include <iostream>

BoardRenderer::BoardRenderer(Board *gameBoard, int difficulty)
    : board(gameBoard) {
    height = board->getHeight();
    width = board->getWidth();

    // Setting the offset of the board (centerize)
    x_offset = 30 + (141 - (cell_width * (width + 2) + 1)) / 2;
    y_offset = 1 + (41 - (cell_height * (height + 2) + 1)) / 2;

    // Load background
    background = new string[(height + 2) * cell_height + 1];
    loadBackground(difficulty);
}

BoardRenderer::~BoardRenderer() { delete[] background; }

void BoardRenderer::loadBackground(int difficulty) {
    ifstream fin;
    if (difficulty == EASY) {
        fin.open("assets\\background\\easy.txt");
        bg_info = "Stonehenge - Art by lgbeard";
    } else if (difficulty == MEDIUM) {
        fin.open("assets\\background\\medium.txt");
        bg_info = "Tower Bridge - Art by unknown";
    } else if (difficulty == HARD) {
        fin.open("assets\\background\\hard.txt");
        bg_info = "Taj Mahal - Art by unknown";
    }

    for (int i = 0; i < (height + 2) * cell_height + 1; i++) {
        getline(fin, background[i]);
    }
    fin.close();
}

void BoardRenderer::displayBoard() {
    Console::playSFX(SFX_START_GAME);

    // Print the game board
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtCellBorder);

    // Row separator
    string row_sep;
    row_sep = ' ';
    for (int i = 0; i < width; i++) {
        row_sep += string(cell_width - 1, HORIZONTAL_EDGE) + ' ';
    }

    // Create splitter line
    string spliter_line;
    spliter_line = VERTICAL_EDGE;
    for (int i = 0; i < width; i++) {
        spliter_line += string(cell_width - 1, ' ') + VERTICAL_EDGE;
    }

    // Draw board
    int line = 0;
    int sleep_interval = 500 / (height * cell_height + 1);
    Renderer::goTo(x_offset + cell_width, y_offset + cell_height);
    cout << row_sep;
    line++;
    Sleep(sleep_interval);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < cell_height - 1; j++) {
            Renderer::goTo(x_offset + cell_width,
                           y_offset + cell_height + line++);
            cout << spliter_line;
            Sleep(sleep_interval);
        }
        Renderer::goTo(x_offset + cell_width, y_offset + cell_height + line++);
        cout << row_sep;
        Sleep(sleep_interval);
    }

    // Put letters in
    displayLetter();
}

void BoardRenderer::displayLetter() {
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtLetter);
    int sleep_interval = 500 / (height * width);
    for (int i = 1; i <= width; i++) {
        for (int j = 1; j <= height; j++) {
            Renderer::goTo(x_offset + i * cell_width + cell_width / 2,
                           y_offset + j * cell_height + cell_height / 2);
            cout << board->getLetter({i, j});
            Sleep(sleep_interval);
        }
    }
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
}

void BoardRenderer::highlightCell(Coordinate pos, string bg_color,
                                  string text_color) {
    if (board->isValid(pos)) {
        Renderer::changeTextColor(bg_color, text_color);

        // Highlight the cell
        for (int i = 1; i < cell_height; i++) {
            Renderer::goTo(x_offset + cell_width * pos.x + 1,
                           y_offset + cell_height * pos.y + i);
            cout << string(cell_width - 1, ' ');
        }

        // Print the letter
        Renderer::goTo(x_offset + cell_width * pos.x + cell_width / 2,
                       y_offset + cell_height * pos.y + cell_height / 2);
        cout << board->getLetter(pos);
    } else { // Empty cell, draw background
        Renderer::changeTextColor(bg_color, Colors::txtMainText);
        for (int i = 1; i < cell_height; i++) {
            Renderer::goTo(x_offset + cell_width * pos.x + 1,
                           y_offset + cell_height * pos.y + i);
            cout << background[cell_height * pos.y + i].substr(
                cell_width * pos.x + 1, cell_width - 1);
        }
    }
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
}

void BoardRenderer::unhighlightCell(Coordinate pos) {
    highlightCell(pos, Colors::bgMainBg, Colors::txtLetter);
}

void BoardRenderer::highlightCursor(Coordinate pos) {
    highlightCell(pos, Colors::bgCellCursor);
}

void BoardRenderer::highlightSelected(Coordinate pos) {
    highlightCell(pos, Colors::bgCellSelected);
}

void BoardRenderer::highlightCorrectPair(Coordinate pos1, Coordinate pos2) {
    highlightCell(pos1, Colors::bgCellCorrect);
    highlightCell(pos2, Colors::bgCellCorrect);
}

void BoardRenderer::highlightWrongPair(Coordinate pos1, Coordinate pos2) {
    highlightCell(pos1, Colors::bgCellWrong);
    highlightCell(pos2, Colors::bgCellWrong);
}

void BoardRenderer::highlightHintPair(Coordinate pos1, Coordinate pos2) {
    highlightCell(pos1, Colors::bgCellHint);
    highlightCell(pos2, Colors::bgCellHint);
}

queue<Coordinate> BoardRenderer::drawPath(vector<Coordinate> path) {
    queue<Coordinate> drawn_pixels;
    Coordinate prev, curr, next;
    Vector prev_curr, curr_next;

    int x, y;

    bool isStart = true, isEnd = false;
    bool left, right, up, down;

    prev = {-1, -1};
    curr = path.back();
    path.pop_back();
    next = path.back();
    path.pop_back();

    while (1) {
        left = right = up = down = false;
        prev_curr = curr - prev;
        curr_next = next - curr;

        // huong di
        if (!isEnd) {
            if (curr_next.x == 0) {
                if (curr_next.y < 0) // di len
                    up = true;
                else // di xuong
                    down = true;
            } else {
                if (curr_next.x > 0) // qua phai
                    right = true;
                else // qua trai
                    left = true;
            }
        }

        // huong den
        if (!isStart) {
            if (prev_curr.x == 0) {
                if (prev_curr.y > 0) // tu tren
                    up = true;
                else // tu duoi
                    down = true;
            } else {
                if (prev_curr.x < 0) // tu phai
                    right = true;
                else // tu trai
                    left = true;
            }
        }

        // Draw path
        Renderer::changeTextColor(Colors::bgMainBg, Colors::txtPath);
        if (left) {
            x = x_offset + cell_width * curr.x + 1;
            y = y_offset + cell_height * curr.y + cell_height / 2;
            Renderer::goTo(x, y);
            if (!isStart && !isEnd) {
                for (int i = 0; i < cell_width / 2; i++) {
                    cout << HORIZONTAL_EDGE;
                    drawn_pixels.push({x + i, y});
                }
            } else {
                cout << HORIZONTAL_EDGE;
                drawn_pixels.push({x, y});
            }
        }

        if (right) {
            if (!isStart && !isEnd) {
                x = x_offset + cell_width * curr.x + cell_width / 2;
                y = y_offset + cell_height * curr.y + cell_height / 2;
                Renderer::goTo(x, y);
                for (int i = 0; i < cell_width / 2 + 1; i++) {
                    cout << HORIZONTAL_EDGE;
                    drawn_pixels.push({x + i, y});
                }
            } else {
                x = x_offset + cell_width * curr.x + cell_width - 1;
                y = y_offset + cell_height * curr.y + cell_height / 2;
                Renderer::goTo(x, y);
                cout << HORIZONTAL_EDGE << HORIZONTAL_EDGE;
                drawn_pixels.push({x, y});
                drawn_pixels.push({x + 1, y});
            }
        }

        if (up) {
            if (!isStart && !isEnd) {
                x = x_offset + cell_width * curr.x + cell_width / 2;
                y = y_offset + cell_height * curr.y;
                for (int i = 1; i <= cell_height / 2; i++) {
                    Renderer::goTo(x, y + i);
                    cout << VERTICAL_EDGE;
                    drawn_pixels.push({x, y + i});
                }
            }
        }

        if (down) {
            x = x_offset + cell_width * curr.x + cell_width / 2;
            y = y_offset + cell_height * curr.y + cell_height;
            Renderer::goTo(x, y);
            cout << VERTICAL_EDGE;
            drawn_pixels.push({x, y});
            if (!isStart && !isEnd) {
                x = x_offset + cell_width * curr.x + cell_width / 2;
                y = y_offset + cell_height * curr.y;
                for (int i = cell_height / 2; i < cell_height; i++) {
                    Renderer::goTo(x, y + i);
                    cout << VERTICAL_EDGE;
                    drawn_pixels.push({x, y + i});
                }
            }
        }

        if (!isStart && !isEnd) {
            if (left && up) {
                Renderer::goTo(x_offset + cell_width * curr.x + cell_width / 2,
                               y_offset + cell_height * curr.y +
                                   cell_height / 2);
                cout << LEFT_UP_CORNER;
            } else if (left && down) {
                Renderer::goTo(x_offset + cell_width * curr.x + cell_width / 2,
                               y_offset + cell_height * curr.y +
                                   cell_height / 2);
                cout << LEFT_DOWN_CORNER;
            } else if (right && up) {
                Renderer::goTo(x_offset + cell_width * curr.x + cell_width / 2,
                               y_offset + cell_height * curr.y +
                                   cell_height / 2);
                cout << RIGHT_UP_CORNER;
            } else if (right && down) {
                Renderer::goTo(x_offset + cell_width * curr.x + cell_width / 2,
                               y_offset + cell_height * curr.y +
                                   cell_height / 2);
                cout << RIGHT_DOWN_CORNER;
            }
        }

        if (isStart)
            isStart = false;
        if (isEnd)
            break;
        prev = curr;
        curr = next;
        isEnd = path.empty();
        if (!isEnd) {
            next = path.back();
            path.pop_back();
        }
    }
    return drawn_pixels;
}

void BoardRenderer::deletePath(queue<Coordinate> drawn_pixels, Coordinate pos1,
                               Coordinate pos2) {
    int x, y;
    Coordinate curr;
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    while (!drawn_pixels.empty()) {
        curr = drawn_pixels.front();
        drawn_pixels.pop();
        x = curr.x;
        y = curr.y;
        Renderer::goTo(x, y);
        cout << background[y - y_offset][x - x_offset];
    }
}

void BoardRenderer::animateShuffle() {
    for (int i = 1; i <= width; i++) {
        for (int j = 1; j <= height; j++) {
            highlightCell({i, j}, BG_PINK, Colors::txtHighlightLetter);
        }
        Sleep(30);
        for (int j = 1; j <= height; j++) {
            unhighlightCell({i, j});
        }
    }
}

void BoardRenderer::renderRemovedCell(Coordinate pos) {
    // Remove the letter and draw background
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    for (int i = 1; i < cell_height; i++) {
        Renderer::goTo(x_offset + pos.x * cell_width + 1,
                       y_offset + pos.y * cell_height + i);
        cout << background[pos.y * cell_height + i].substr(
            pos.x * cell_width + 1, cell_width - 1);
    }

    // Check if adjacent cells exist
    bool left, right, top, bottom;
    left = !board->isValid({pos.x - 1, pos.y});
    right = !board->isValid({pos.x + 1, pos.y});
    top = !board->isValid({pos.x, pos.y - 1});
    bottom = !board->isValid({pos.x, pos.y + 1});

    if (left) { // Check left side
        for (int i = 1; i < cell_height; i++) {
            Renderer::goTo(x_offset + cell_width * pos.x,
                           y_offset + cell_height * pos.y + i);
            cout << background[cell_height * pos.y + i][cell_width * pos.x];
        }
    }

    if (right) { // Check right side
        for (int i = 1; i < cell_height; i++) {
            Renderer::goTo(x_offset + cell_width * pos.x + cell_width,
                           y_offset + cell_height * pos.y + i);
            cout << background[cell_height * pos.y + i]
                              [cell_width * pos.x + cell_width];
        }
    }

    if (top) { // Check above
        Renderer::goTo(x_offset + cell_width * pos.x + 1,
                       y_offset + cell_height * pos.y);
        cout << background[cell_height * pos.y].substr(cell_width * pos.x + 1,
                                                       cell_width - 1);
    }

    if (bottom) { // Check below
        Renderer::goTo(x_offset + cell_width * pos.x + 1,
                       y_offset + cell_height * pos.y + cell_height);
        cout << background[cell_height * pos.y + cell_height].substr(
            cell_width * pos.x + 1, cell_width - 1);
    }
}