#include "ArrayBoardRenderer.h"

ArrayBoardRenderer::ArrayBoardRenderer(Board *gameBoard, int difficulty)
    : BoardRenderer(gameBoard, difficulty) {}

void ArrayBoardRenderer::deletePath(queue<Coordinate> drawn_pixels,
                                    Coordinate pos1, Coordinate pos2) {
    BoardRenderer::deletePath(drawn_pixels, pos1, pos2);
}

void ArrayBoardRenderer::renderRemovedCell(Coordinate pos) {
    BoardRenderer::renderRemovedCell(pos);
}