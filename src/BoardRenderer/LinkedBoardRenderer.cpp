#include "LinkedBoardRenderer.h"

LinkedBoardRenderer::LinkedBoardRenderer(Board *gameBoard, int difficulty)
    : BoardRenderer(gameBoard, difficulty) {}

void LinkedBoardRenderer::deletePath(queue<Coordinate> drawn_pixels,
                                     Coordinate pos1, Coordinate pos2) {
    BoardRenderer::deletePath(drawn_pixels, pos1, pos2);

    // Additional border restoration for linked list
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtCellBorder);
    Renderer::goTo(x_offset + cell_width * pos1.x + cell_width / 2,
                   y_offset + cell_height * pos1.y);
    cout << HORIZONTAL_EDGE;
    Renderer::goTo(x_offset + cell_width * pos1.x + cell_width / 2,
                   y_offset + cell_height * pos1.y + cell_height);
    cout << HORIZONTAL_EDGE;
    Renderer::goTo(x_offset + cell_width * pos1.x,
                   y_offset + cell_height * pos1.y + cell_height / 2);
    cout << VERTICAL_EDGE;
    Renderer::goTo(x_offset + cell_width * pos1.x + cell_width,
                   y_offset + cell_height * pos1.y + cell_height / 2);
    cout << VERTICAL_EDGE;

    Renderer::goTo(x_offset + cell_width * pos2.x + cell_width / 2,
                   y_offset + cell_height * pos2.y);
    cout << HORIZONTAL_EDGE;
    Renderer::goTo(x_offset + cell_width * pos2.x + cell_width / 2,
                   y_offset + cell_height * pos2.y + cell_height);
    cout << HORIZONTAL_EDGE;
    Renderer::goTo(x_offset + cell_width * pos2.x,
                   y_offset + cell_height * pos2.y + cell_height / 2);
    cout << VERTICAL_EDGE;
    Renderer::goTo(x_offset + cell_width * pos2.x + cell_width,
                   y_offset + cell_height * pos2.y + cell_height / 2);
    cout << VERTICAL_EDGE;
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtMainText);
}

void LinkedBoardRenderer::renderRemovedCell(Coordinate pos) {
    if (!board->isValid(pos)) { // last cell in the row
        BoardRenderer::renderRemovedCell(pos);
        return;
    }

    Coordinate cur = pos;
    // remove the right most cell in the row
    for (int i = cur.x + 1; i <= width; i++) {
        if (!board->isValid({i, pos.y}))
            break;
        pos.x = i;
    }

    pos.x++; // move to the position to be removed
    BoardRenderer::renderRemovedCell(pos);

    // print the row letter again
    Renderer::changeTextColor(Colors::bgMainBg, Colors::txtLetter);
    for (int i = cur.x; i <= width; i++) {
        if (!board->isValid({i, pos.y}))
            break;
        Renderer::goTo(x_offset + i * cell_width + cell_width / 2,
                       y_offset + pos.y * cell_height + cell_height / 2);
        cout << board->getLetter({i, pos.y});
    }
}