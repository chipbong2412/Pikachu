#include "Game.h"

#include <ctime>
#include <iomanip>
#include <queue>

#include "../Board/ArrayBoard.h"
#include "../Board/LinkedBoard.h"
#include "../BoardRenderer/ArrayBoardRenderer.h"
#include "../BoardRenderer/LinkedBoardRenderer.h"
#include "../Console/Console.h"
#include "../Console/Constants.h"
#include "Highscores.h"

using namespace std;

Game::Game(int difficulty) {
    // Determine board dimensions and type based on difficulty
    if (difficulty == EASY) {
        board_height = 6;
        board_width = 8;
        int distinct_letters = 15;
        game_board =
            new ArrayBoard(board_height, board_width, distinct_letters);
        board_render = new ArrayBoardRenderer(game_board, difficulty);
    }

    else if (difficulty == MEDIUM) {
        board_height = 8;
        board_width = 10;
        int distinct_letters = 20;
        game_board =
            new ArrayBoard(board_height, board_width, distinct_letters);
        board_render = new ArrayBoardRenderer(game_board, difficulty);
    }

    else if (difficulty == HARD) {
        board_height = 8;
        board_width = 12;
        int distinct_letters = 26;
        game_board =
            new LinkedBoard(board_height, board_width, distinct_letters);
        board_render = new LinkedBoardRenderer(game_board, difficulty);
    }
}

Game::~Game() {
    delete game_board;
    delete board_render;
}

void Game::initGame() {
    system("cls");
    score = 0;
    hint_remaining = MAX_HINT;
    hint_used = false;
    shuffled = false;

    game_board->initBoard();
    displayGameInfo();
    Renderer::drawBox(30, 1, 141, 41); // game board's box
    Sleep(500);
    board_render->displayBoard();
}

void Game::gameLoop() {
    clock_t start_time;
    int remaining_cell = board_height * board_width;
    Coordinate cur1, cur2; // cursor 1 and cursor 2
    Coordinate pos1, pos2; // position of hint
    Input inp;
    bool cur1_selected = false;

    cur1 = cur2 = {1, 1};

    board_render->highlightCursor(cur1);

    start_time = clock();

    // shuffle board if there are no valid pairs
    if (!game_board->findValidPair(pos1, pos2)) {
        board_render->unhighlightCell(cur1);
        game_board->shuffleBoard();
        board_render->animateShuffle();
        board_render->highlightCursor(cur1);
    }

    while (remaining_cell > 0) {
        inp = InputHandler::getInput();

        // invalid input
        while (inp == Input::INVALID)
            inp = InputHandler::getInput();

        // escape
        if (inp == Input::ESCAPE) {
            system("cls");
            return;
        }

        // move cursor
        if (inp == Input::UP || inp == Input::LEFT || inp == Input::DOWN ||
            inp == Input::RIGHT) {
            if (!cur1_selected) {
                board_render->unhighlightCell(cur1);
                moveCursor(cur1, inp);
                board_render->highlightCursor(cur1);
            } else {
                if (cur1 != cur2)
                    board_render->unhighlightCell(cur2);
                else
                    board_render->highlightSelected(cur1);
                moveCursor(cur2, inp);
                board_render->highlightCursor(cur2);
            }
            continue;
        }

        // select cell
        if (inp == Input::ENTER) {
            // select cell 1
            if (!cur1_selected) {
                if (!game_board->isValid(cur1))
                    continue; // if select invalid cell (removed cell), do
                              // nothing
                board_render->highlightSelected(cur1);
                cur1_selected = true;
                cur2 = cur1;
            }

            // select cell 2
            else {
                if (cur1 == cur2) {
                    // deselect
                    board_render->highlightCursor(cur1);
                    cur1_selected = false;
                    continue;
                }
                if (!game_board->isValid(cur2)) {
                    continue; // if select empty cell, do nothing
                }

                // match cells
                if (matchCell(cur1, cur2)) {
                    board_render->unhighlightCell(cur1);
                    updateScore(CORRECT_BONUS);
                    remaining_cell -= 2;

                    // shuffle board if there are no valid pairs
                    if (remaining_cell &&
                        !game_board->findValidPair(pos1, pos2)) {
                        board_render->unhighlightCell(cur2);
                        game_board->shuffleBoard();
                        board_render->animateShuffle();
                    }
                    board_render->highlightCursor(cur2);

                } else {
                    updateScore(WRONG_PENALTY);
                }
                cur1 = cur2;
                cur1_selected = false;
                hint_used = false;
            }
            continue;
        }

        // show hint
        if (inp == Input::HINT) {
            if (!hint_used && hint_remaining > 0) {
                board_render->highlightHintPair(
                    pos1, pos2); // hint pair is found after each match
                updateScore(HINT_PENALTY);
                hint_remaining--;
                updateRemainingHint();
                hint_used = true;
            }
            continue;
        }
    }

    // game ended
    play_time = Time((clock() - start_time) / CLOCKS_PER_SEC);
    board_render->unhighlightCell(cur1);

    gameResult();
}

void Game::gameResult() {
    // show info and wait for user
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    string bg_info = board_render->getBackgroundInfo();
    Renderer::goTo(30 + (141 - bg_info.length()) / 2, 38);
    cout << bg_info;
    Renderer::goTo(89, 39);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_PINK);
    Console::playSFX(SFX_WIN);
    cout << "Press Enter to continue";
    while (InputHandler::getInput() != Input::ENTER)
        ;

    // clear screen
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    for (int i = 0; i < 39; i++) {
        Renderer::goTo(31, 2 + i);
        cout << string(139, ' ');
    }

    Renderer::goTo(93, 15);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_YELLOW);
    cout << "Congratulation";

    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    Renderer::goTo(90, 18);
    cout << "Your score is: ";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtBlue);
    cout << score;

    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    Renderer::goTo(90, 19);
    cout << "Your time is: ";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtBlue);
    cout << play_time;

    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    Renderer::goTo(68, 21);
    cout << "Please input your name (maximum 30 characters, no ',' allowed)";
    Renderer::goTo(88, 22);
    cout << "Press Enter when finished";
    inputName(84, 23);

    Highscores highscores;
    highscores.loadHighscores();
    highscores.updateHighscores({name, score, play_time});

    Renderer::goTo(73, 26);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_PINK);
    cout << "Your score is saved. Press ESC to go back to main menu";
    while (InputHandler::getInput() != Input::ESCAPE)
        ;
    system("cls");
}

// Private helper methods
void Game::displayGameInfo() {
    Renderer::drawBox(1, 1, 29, 18);
    Renderer::drawBox(1, 19, 29, 23);

    // score
    Renderer::goTo(5, 4);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << "Score: ";
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtBlue);
    cout << score;

    // hint
    Renderer::goTo(5, 7);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << "Hint: ";
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_GREEN);
    cout << hint_remaining;

    // score rules
    Renderer::goTo(10, 10);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << "Score rules";
    Renderer::goTo(4, 12);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_GREEN);
    cout << "Correct pair +" << CORRECT_BONUS << " pts";
    Renderer::goTo(4, 13);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_RED);
    cout << "Wrong pair/";
    Renderer::goTo(6, 14);
    cout << "can't match " << WRONG_PENALTY << " pts";
    Renderer::goTo(4, 15);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_PURPLE);
    cout << "Use hint " << HINT_PENALTY << " pts";

    // play instruction
    Renderer::goTo(10, 20);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << "How to play";

    Renderer::goTo(4, 22);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtBlue);
    cout << "WASD to move cursor:";
    Renderer::goTo(4, 23);
    cout << "- W: UP";
    Renderer::goTo(4, 24);
    cout << "- A: LEFT";
    Renderer::goTo(4, 25);
    cout << "- S: DOWN";
    Renderer::goTo(4, 26);
    cout << "- D: RIGHT";

    Renderer::goTo(4, 28);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_ORANGE);
    cout << "ENTER to select, ";
    Renderer::goTo(6, 29);
    cout << "select again to cancel";

    Renderer::goTo(4, 31);
    Renderer::changeTextColor(Colors::bgMainBg, TEXT_PURPLE);
    cout << "H to show hint,";
    Renderer::goTo(6, 32);
    cout << "can use hint " << MAX_HINT << " times";

    Renderer::goTo(4, 34);
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
    cout << "ESC to return";
    Renderer::goTo(6, 35);
    cout << "to main menu";
}

void Game::moveCursor(Coordinate &cur, Input inp) {
    if (inp == Input::UP) {
        cur.y -= 1;
        if (cur.y <= 0)
            cur.y = board_height;
    } else if (inp == Input::LEFT) {
        cur.x -= 1;
        if (cur.x <= 0)
            cur.x = board_width;
    } else if (inp == Input::DOWN) {
        cur.y += 1;
        if (cur.y > board_height)
            cur.y = 1;
    } else if (inp == Input::RIGHT) {
        cur.x += 1;
        if (cur.x > board_width)
            cur.x = 1;
    }
}

bool Game::matchCell(Coordinate cur1, Coordinate cur2) {
    vector<Coordinate> path;
    queue<Coordinate> drawn_pixels;

    // correct pair highlighting and deleting
    if (cur1 != cur2 && // check if the two coordinates are not the same
        game_board->getLetter(cur1) ==
            game_board->getLetter(
                cur2) && // check if they have the same representative letter
        game_board->bfs(
            cur1, cur2,
            path) // check if there exists a valid path between the two cells
    ) {
        // draw the path
        drawn_pixels = board_render->drawPath(path);
        board_render->highlightCorrectPair(cur1, cur2);
        Console::playSFX(SFX_CORRECT);
        Sleep(500);

        board_render->deletePath(drawn_pixels, cur1, cur2);

        // delete the cell and shifting (right most element gets deleted first)
        Coordinate first = (cur1.x < cur2.x) ? cur2 : cur1;  // right most cell
        Coordinate second = (cur1.x < cur2.x) ? cur1 : cur2; // left
        game_board->removeCell(first);
        board_render->renderRemovedCell(first);
        game_board->removeCell(second);
        board_render->renderRemovedCell(second);
        return true;
    }

    // incorrect pair highlighting
    else {
        board_render->highlightWrongPair(cur1, cur2);
        Console::playSFX(SFX_WRONG);
        Sleep(500);
        board_render->unhighlightCell(cur1);
        board_render->highlightCursor(cur2);
        return false;
    }
}

void Game::updateScore(int bonus_score) {
    // print score
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtBlue);
    Renderer::goTo(12, 4);
    cout << string(5, ' '); // clear the previous score
    score += bonus_score;
    Renderer::goTo(12, 4);
    cout << score;

    // print bonus score
    Renderer::goTo(12, 5);
    cout << string(5, ' '); // clear the previous bonus score
    Renderer::goTo(12, 5);
    if (bonus_score < 0) {
        Renderer::changeTextColor(Colors::bgMainBg, TEXT_RED);
        cout << bonus_score;
    } else {
        Renderer::changeTextColor(Colors::bgMainBg, TEXT_GREEN);
        cout << '+' << bonus_score;
    }
}

void Game::updateRemainingHint() {
    if (hint_remaining <= 0) {
        Renderer::goTo(11, 7);
        Renderer::changeTextColor(Colors::bgMainBg, TEXT_RED);
        cout << hint_remaining;
        Renderer::goTo(5, 8);
        cout << "No more hint available";
    } else {
        Renderer::goTo(11, 7);
        Renderer::changeTextColor(Colors::bgMainBg, TEXT_GREEN);
        cout << hint_remaining;
    }
}

void Game::inputName(int x, int y) {
    name = "";
    Renderer::drawBox(x, y, 32, 3);
    Renderer::goTo(x + 1, y + 1);
    Renderer::setCursorAppearance(true);
    getline(cin, name);
    Renderer::setCursorAppearance(false);
    while (name.find(',') != name.npos || name.size() > 30 ||
           name.size() == 0) {
        Renderer::goTo(x + 1, y + 1);
        cout << string(50, ' ');
        Renderer::goTo(x + 31, y + 1);
        cout << D_VERTICAL_EDGE;
        Renderer::goTo(x + (32 - 25) / 2, y + 3);
        cout << "Please input a valid name";
        Renderer::goTo(x + 1, y + 1);
        Renderer::setCursorAppearance(true);
        getline(cin, name);
        Renderer::setCursorAppearance(false);
    }
    Renderer::goTo(x + (32 - 25) / 2, y + 3);
    cout << string(25, ' ');
}