#ifndef ARRAYBOARDRENDERER_H
#define ARRAYBOARDRENDERER_H

#include "BoardRenderer.h"

class ArrayBoardRenderer : public BoardRenderer {
public:
    ArrayBoardRenderer(Board *gameBoard, int difficulty);

    // Delete the path after displaying for array board
    void deletePath(queue<Coordinate> drawn_pixels, Coordinate pos1,
                    Coordinate pos2) override;
    // Render the removed cell for array board
    void renderRemovedCell(Coordinate pos) override;
};

#endif