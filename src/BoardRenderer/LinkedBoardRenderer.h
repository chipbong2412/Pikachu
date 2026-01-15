#ifndef LINKEDBOARDRENDERER_H
#define LINKEDBOARDRENDERER_H

#include "../Board/LinkedBoard.h"
#include "BoardRenderer.h"

class LinkedBoardRenderer : public BoardRenderer {
public:
    LinkedBoardRenderer(Board *gameBoard, int difficulty);

    // Delete the path after displaying for linked list board
    void deletePath(queue<Coordinate> drawn_pixels, Coordinate pos1,
                    Coordinate pos2) override;
    // Render the removed cell for linked list board
    void renderRemovedCell(Coordinate pos) override;
};

#endif